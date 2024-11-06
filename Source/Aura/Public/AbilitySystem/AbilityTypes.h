// Copyright, NyuAnca 2024

#pragma once

#include "GameplayEffect.h"
#include "AbilityTypes.generated.h"

UENUM(BlueprintType)
enum class EApplyPolicy : uint8
{
	DoNotApply,
	ApplyOnBeginOverlap,
	ApplyOnEndOverlap
};

UENUM(BlueprintType)
enum class ERemovalPolicy : uint8
{
	DoNotRemove,
	RemoveOnEndOverlap
};

USTRUCT(BlueprintType)
struct FGameplayEffectData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category=FXData)
	EApplyPolicy ApplyPolicy = EApplyPolicy::ApplyOnBeginOverlap;

	UPROPERTY(EditAnywhere, Category=FXData)
	ERemovalPolicy RemovalPolicy = ERemovalPolicy::RemoveOnEndOverlap;

	UPROPERTY(EditAnywhere, Category=FXData)
	TSubclassOf<UGameplayEffect> FXClass = UGameplayEffect::StaticClass();

	bool operator==(const FGameplayEffectData& Other) const
	{
		return ApplyPolicy == Other.ApplyPolicy && RemovalPolicy == Other.RemovalPolicy && FXClass == Other.FXClass;
	}
};

struct FActiveEffectHandle
{
	FActiveEffectHandle(const FGameplayEffectData& InEffect, const FActiveGameplayEffectHandle InHandle):
		AppliedEffect(InEffect),
		Handle(InHandle)
	{
		
	}
	
	const FGameplayEffectData& AppliedEffect;
	
	FActiveGameplayEffectHandle Handle;

	bool operator==(const FActiveEffectHandle& Other) const
	{
		return Handle == Other.Handle && AppliedEffect == Other.AppliedEffect;
	}
};

