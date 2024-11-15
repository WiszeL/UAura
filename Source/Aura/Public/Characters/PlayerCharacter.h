// Copyright, RilAnca 2024

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class AAuraPlayerState;
class UCameraComponent;
class USpringArmComponent;
struct FInputActionValue;
class UInputAction;

UCLASS()
class AURA_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	
	// ===== Events ===== //
	
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	void InitAssets();

	// ===== References ===== //

	TWeakObjectPtr<AAuraPlayerState> AuraPlayerState;

	virtual void OnRep_PlayerState() override;

private:
	// ===== Ability System ===== //

	void InitAbilityInfo();

public:
	virtual uint16 GetCombatLevel() const override;
	
private:
	// ===== Camera ===== //

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> Camera;

private:
	// ===== Input ===== //

	UPROPERTY(EditAnywhere, Category=Input)
	TSoftObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputValue);
};
