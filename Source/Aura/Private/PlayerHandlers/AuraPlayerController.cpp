// Copyright, RilAnca 2024

#include "PlayerHandlers/AuraPlayerController.h"

#include "AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "NiagaraFunctionLibrary.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/AuraInputComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Helpers/AssetHelper.h"
#include "Interfaces/HighlightInterface.h"
#include "PlayerHandlers/AuraPlayerState.h"
#include "UI/AuraHUD.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	
	InitAssets();

	// Interaction
	SplinePath = CreateDefaultSubobject<USplineComponent>("Spline Path");
}

void AAuraPlayerController::InitAssets()
{
	// Input
	INIT_LOAD_ASSET(DefaultInput, "/Game/Inputs/IMC_DefaultInput.IMC_DefaultInput");
	INIT_LOAD_ASSET(InputConfig, "/Game/Data/DataAssets/DA_InputConfig.DA_InputConfig");
}

// ===== Events ===== //

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetupInput();
}

void AAuraPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	// Client-Only, References
	SpringArm = P->GetComponentByClass<USpringArmComponent>();
	SpringArm->SetWorldLocation(P->GetActorLocation());
	
	// HUD
	if (AAuraHUD* AuraHUD = GetHUD<AAuraHUD>())
		AuraHUD->PrepareHUD();
}

void AAuraPlayerController::PlayerTick(const float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
	AutoMove();
	MoveCamera(DeltaTime);
}

// ===== Input ===== //

void AAuraPlayerController::SetupInput()
{
	checkf(DefaultInput, TEXT("Default Input is not set yet!"));

	// Subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		Subsystem->AddMappingContext(DefaultInput.Get(), 0);

	// Mouse
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);

	SetInputMode(InputMode);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UAuraInputComponent* AuraInput = CastChecked<UAuraInputComponent>(InputComponent);
	AuraInput->BindAbilityAction(InputConfig.Get(), this, &ThisClass::AbilityActionPressed,
		&ThisClass::AbilityActionReleased, &ThisClass::AbilityActionHeld);
}

void AAuraPlayerController::AbilityActionPressed(const FGameplayTag InputTag)
{
	GetAsc()->AbilityInputPressed(InputTag);
}

void AAuraPlayerController::AbilityActionHeld(const FGameplayTag InputTag)
{
	// Move to cursor
	if (InputTag.MatchesTagExact(FAuraGameplayTags::Get().Input_Goto)) MoveToCursor();
	// Gameplay Ability
	else GetAsc()->AbilityInputPressed(InputTag);
}

void AAuraPlayerController::AbilityActionReleased(const FGameplayTag InputTag)
{
	// Auto Run
	if (InputTag.MatchesTagExact(FAuraGameplayTags::Get().Input_Goto) && FollowTime <= AutoMoveThreshold) PrepareAutoMove();
	// Gameplay Ability
	else GetAsc()->AbilityInputReleased(InputTag);

	// Reset
	FollowTime = 0.f;
}

// ===== Ability System ===== //

UAuraAbilitySystemComponent* AAuraPlayerController::GetAsc()
{
	if (!AuraAbilitySystemComp.IsValid())
		AuraAbilitySystemComp = Cast<UAuraAbilitySystemComponent>(
			GetPlayerState<AAuraPlayerState>()->GetAbilitySystemComponent()
		);

	return AuraAbilitySystemComp.Get();
}

// ===== Highlighting ===== //

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;

	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	CursorLocation = CursorHit.ImpactPoint;
	
	if (!CursorHit.IsValidBlockingHit()) return;

	LastHighlighting = CurrentHighlighting;
	CurrentHighlighting = CursorHit.GetActor();

	if (LastHighlighting != CurrentHighlighting)
	{
		if (LastHighlighting) LastHighlighting->UnHighlight();
		if (CurrentHighlighting) CurrentHighlighting->Highlight();
	}
}

// ===== Move to Cursor ===== //

void AAuraPlayerController::MoveToCursor()
{
	FollowTime += GetWorld()->GetDeltaSeconds();

	if (CursorLocation.IsNearlyZero()) return;

	Destination = CursorLocation;
	const FVector CursorDirection = (Destination - GetPawn()->GetActorLocation()).GetSafeNormal();
	GetPawn()->AddMovementInput(CursorDirection);
}

void AAuraPlayerController::PrepareAutoMove()
{
	const UNavigationPath* Path = UNavigationSystemV1::FindPathToLocationSynchronously(
		this, GetPawn()->GetActorLocation(), CursorLocation
	);

	if (!Path || Path->PathPoints.IsEmpty()) return;

	// Add the path to the spline
	SplinePath->ClearSplinePoints();
	
	for (const auto& Location : Path->PathPoints)
		SplinePath->AddSplineWorldPoint(Location);

	Destination = Path->PathPoints[Path->PathPoints.Num() - 1];
	bAutoMove = true;

	// Spawn mouse click FX
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, MouseClickFX.LoadSynchronous(), CursorLocation);
}

void AAuraPlayerController::AutoMove()
{
	if (!bAutoMove) return;

	const FVector SplineLocation = SplinePath->FindLocationClosestToWorldLocation(GetPawn()->GetActorLocation(), ESplineCoordinateSpace::World);
	const FVector Direction = SplinePath->FindDirectionClosestToWorldLocation(SplineLocation, ESplineCoordinateSpace::World);

	GetPawn()->AddMovementInput(Direction);

	// Stop if character has arrived
	if ((SplineLocation - Destination).Size() <= 5.f) bAutoMove = false;
}

// ===== Camera Moving ===== //

void AAuraPlayerController::MoveCamera(const float DeltaTime) const
{
	if (!IsLocalController() || !SpringArm.IsValid()) return;

	// Get mouse position relative to the viewport
	FVector2D MousePosition;
	int32 ViewportX, ViewportY;
	GetMousePosition(MousePosition.X, MousePosition.Y);
	GetViewportSize(ViewportX, ViewportY);

	// Safe divide to normalize mouse position
	MousePosition = {
		ViewportX != 0 ? MousePosition.X / ViewportX : MousePosition.X,
		ViewportY != 0 ? MousePosition.Y / ViewportY : MousePosition.Y
	};

	// Check, is the mouse on edge?
	const float OffsetX = FMath::Abs(MousePosition.Y - 0.5f);
	const float OffsetY = FMath::Abs(MousePosition.X - 0.5f);
	
	float DirX = 0.f, DirY = 0.f, SpeedX = 0.f, SpeedY = 0.f; 
	
	// Find the direction based on adjustable edge offset
	if (OffsetX >= 0.5f - EdgeOffset)
	{
		DirX = MousePosition.Y <= EdgeOffset ? 1.f : -1.f;
		SpeedX = (OffsetX - (0.5f - EdgeOffset)) / EdgeOffset * CameraSpeed * CamMaxMultiplier;
	}
	if (OffsetY >= 0.5f - EdgeOffset)
	{
		DirY = MousePosition.X <= EdgeOffset ? -1.f : 1.f;
		SpeedY = (OffsetY - (0.5f - EdgeOffset)) / EdgeOffset * CameraSpeed * CamMaxMultiplier;
	}

	if (SpeedX > 0.f || SpeedY > 0.f) SpringArm->AddWorldOffset(
		{ DirX * SpeedX * DeltaTime, DirY * SpeedY * DeltaTime, 0.f }
		);
}
