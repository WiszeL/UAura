// Copyright, NyuAnca 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class USpringArmComponent;
class USplineComponent;
class UAuraAbilitySystemComponent;
class UInputConfig;
class UNiagaraSystem;
class IHighlightInterface;
class UInputMappingContext;

UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();

private:
	void InitAssets();

public:
	// ===== Events ===== //

	virtual void BeginPlay() override;
	virtual void AcknowledgePossession(APawn* P) override;
	virtual void PlayerTick(float DeltaTime) override;

private:
	// ===== Input ===== //
	
	UPROPERTY(EditAnywhere, Category=Input)
	TSoftObjectPtr<UInputMappingContext> DefaultInput;

	UPROPERTY(EditAnywhere, Category=Input)
	TSoftObjectPtr<UInputConfig> InputConfig;
	
	void SetupInput();
	
	virtual void SetupInputComponent() override;

	void AbilityActionPressed(FGameplayTag InputTag);
	void AbilityActionHeld(FGameplayTag InputTag);
	void AbilityActionReleased(FGameplayTag InputTag);

private:
	// ===== Ability System ===== //

	TWeakObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComp;
	
	UAuraAbilitySystemComponent* GetAsc();
	
private:
	// ===== Highlighting ===== //
	
	TScriptInterface<IHighlightInterface> CurrentHighlighting;
	TScriptInterface<IHighlightInterface> LastHighlighting;
	
	void CursorTrace();

private:
	// ===== Move to Cursor ===== //

	/** Used for the cursor's auto run path */
	UPROPERTY()
	TObjectPtr<USplineComponent> SplinePath;

	UPROPERTY(EditAnywhere, Category=Interaction)
	TSoftObjectPtr<UNiagaraSystem> MouseClickFX;
	
	FVector CursorLocation;
	FVector Destination;

	bool bAutoMove = false;
	float FollowTime = 0.f;

	/** if FollowTime < this threshold, we should auto run */
	UPROPERTY(EditAnywhere, Category=Interaction)
	float AutoMoveThreshold = .4f;

	/** Called when "Goto" gameplay tag input is HELD down */
	void MoveToCursor();

	/** Called when "Goto" gameplay tag input is RELEASED */
	void PrepareAutoMove();
	void AutoMove();

private:
	// ===== Camera Moving ===== //

	/**
	 * This only available on the client, as the server doesn't need any info about it.
	 * Can be NULL too! So make sure to check before accessing it.
	 */
	TWeakObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditAnywhere, Category=CameraMoving)
	float CameraSpeed = 1500.f;

	UPROPERTY(EditAnywhere, Category=CameraMoving)
	float EdgeOffset = .3f;

	/** The edger the mouse is, the camera will move faster by this */
	UPROPERTY(EditAnywhere, Category=CameraMoving)
	float CamMaxMultiplier = 2.5f;
	
	void MoveCamera(float DeltaTime) const;
};
