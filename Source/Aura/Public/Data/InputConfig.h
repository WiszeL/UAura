// Copyright, RilAnca 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "InputConfig.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FAuraInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FGameplayTag InputTag;

	UPROPERTY(EditAnywhere)
	UInputAction* InputAction = nullptr;
};

UCLASS()
class AURA_API UInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FAuraInputAction> Configs;

	UInputAction* FindInputByTag(const FGameplayTag& Tag, bool bWarnNotFound = false);
};
