// Copyright, NyuAnca 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MaxManaCalc.generated.h"

UCLASS()
class AURA_API UMaxManaCalc : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMaxManaCalc();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
private:
	FGameplayEffectAttributeCaptureDefinition IntelligenceDef;
};
