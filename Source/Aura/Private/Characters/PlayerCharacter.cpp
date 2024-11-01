// Copyright, NyuAnca 2024

#include "Characters/PlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Helpers/AssetHelper.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	InitAssets();
	
	// Camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bInheritPitch = SpringArm->bInheritRoll = SpringArm->bInheritYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	bUseControllerRotationPitch = bUseControllerRotationYaw = bUseControllerRotationRoll = false;
	
	// Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = {0.f, 400.f, 0.f};
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
}

void APlayerCharacter::InitAssets()
{
	INIT_LOAD_ASSET(MoveAction, "/Game/Inputs/IA_Move.IA_Move");
}

// ===== Events ===== //

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInput->BindAction(MoveAction.Get(), ETriggerEvent::Triggered, this, &ThisClass::Move);
}

// ===== Input ===== //

void APlayerCharacter::Move(const FInputActionValue& InputValue)
{
	const FVector2D Value = InputValue.Get<FVector2D>();

	const FRotationMatrix ControlMatrix { { 0.f, GetControlRotation().Yaw, 0.f } };
	const FVector Forward = ControlMatrix.GetUnitAxis(EAxis::X);
	const FVector Right = ControlMatrix.GetUnitAxis(EAxis::Y);

	AddMovementInput(Forward, Value.Y);
	AddMovementInput(Right, Value.X);
}
