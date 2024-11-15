// Copyright, RilAnca 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MaxHealthCalc.generated.h"

UCLASS()
class AURA_API UMaxHealthCalc : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMaxHealthCalc();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	// ===== Attributes to Capture ===== //

	FGameplayEffectAttributeCaptureDefinition VigorDef;
};
