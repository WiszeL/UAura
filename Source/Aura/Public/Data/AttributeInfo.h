// Copyright, RilAnca 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"

USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag AttributeTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText AttributeName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;

	UPROPERTY(BlueprintReadOnly)
	float Value = 0.f;
};

UCLASS()
class AURA_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TArray<FAuraAttributeInfo> AttributeInfo;

public:
	FAuraAttributeInfo FindByTag(const FGameplayTag& Tag, const bool bWarnNotFound = false) const;
};
