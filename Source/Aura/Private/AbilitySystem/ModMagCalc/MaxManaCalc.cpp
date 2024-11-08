// Copyright, NyuAnca 2024

#include "AbilitySystem/ModMagCalc/MaxManaCalc.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interfaces/CombatInterface.h"

UMaxManaCalc::UMaxManaCalc()
{
	IntelligenceDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	IntelligenceDef.bSnapshot = false;
}

float UMaxManaCalc::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	FAggregatorEvaluateParameters Params;
	Params.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	Params.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	// Get Intelligence
	float Intelligence = 0.f;
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, Params, Intelligence);

	// Get Combat Level
	const ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const float CombatLevel = CombatInterface->GetCombatLevel();

	return 40.f + 2.f * Intelligence + CombatLevel * 6.f; 
}
