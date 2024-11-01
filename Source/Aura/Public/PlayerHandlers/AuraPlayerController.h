// Copyright, NyuAnca 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class IHighlightInterface;
class UInputMappingContext;

UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();

	// ===== Events ===== //

	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	
private:
	void InitAssets();
	
	// ===== Input ===== //
	
	UPROPERTY(EditAnywhere, Category=Input)
	TSoftObjectPtr<UInputMappingContext> DefaultInput;

	void SetupInput();

private:
	// ===== Interaction ===== //

	TScriptInterface<IHighlightInterface> CurrentHighlighting;
	TScriptInterface<IHighlightInterface> LastHighlighting;
	
	void CursorTrace();
};
