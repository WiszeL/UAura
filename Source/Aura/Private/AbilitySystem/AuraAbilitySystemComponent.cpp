// Copyright, NyuAnca 2024

#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::OnPlayerControllerSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ThisClass::EffectApplied);	
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent*,
	const FGameplayEffectSpec& Spec, FActiveGameplayEffectHandle) const
{
	FGameplayTagContainer TagContainer;
	Spec.GetAllAssetTags(TagContainer);

	EffectAppliedDelegate.Broadcast(TagContainer);
}
