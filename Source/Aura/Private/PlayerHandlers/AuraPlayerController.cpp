// Copyright, NyuAnca 2024

#include "PlayerHandlers/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Helpers/AssetHelper.h"
#include "Interfaces/HighlightInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	
	InitAssets();
}

void AAuraPlayerController::InitAssets()
{
	// Input
	INIT_LOAD_ASSET(DefaultInput, "/Game/Inputs/IMC_DefaultInput.IMC_DefaultInput");
}

// ===== Events ===== //

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetupInput();
}

void AAuraPlayerController::PlayerTick(const float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

// ===== Input ===== //

void AAuraPlayerController::SetupInput()
{
	checkf(DefaultInput, TEXT("Default Input is not set yet!"));

	// Subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->AddMappingContext(DefaultInput.Get(), 0);

	// Mouse
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);

	SetInputMode(InputMode);
}

// ===== Interaction ===== //

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;

	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	if (!CursorHit.IsValidBlockingHit()) return;

	LastHighlighting = CurrentHighlighting;
	CurrentHighlighting = CursorHit.GetActor();

	if (LastHighlighting != CurrentHighlighting)
	{
		if (LastHighlighting) LastHighlighting->UnHighlight();
		if (CurrentHighlighting) CurrentHighlighting->Highlight();
	}
}
