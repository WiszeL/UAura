// Copyright, NyuAnca 2024

#include "AbilitySystem/ModMagCalc/MaxHealthCalc.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interfaces/CombatInterface.h"

UMaxHealthCalc::UMaxHealthCalc()
{
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	VigorDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(VigorDef);
}

float UMaxHealthCalc::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	FAggregatorEvaluateParameters Params;
	Params.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	Params.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	// Getting the Vigor
	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, Params, Vigor);

	// Getting the combat level
	const ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const float CombatLevel = CombatInterface->GetCombatLevel();

	return 80.f + 2.5f * Vigor + 10.f * CombatLevel;
}
