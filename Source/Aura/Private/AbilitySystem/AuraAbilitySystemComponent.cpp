// Copyright, NyuAnca 2024

#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AbilitySystem/Abilities/AuraAbility.h"

// ===== Events ===== //

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

// ===== Abilities ===== //

void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const auto& Ability : StartupAbilities)
	{
		FGameplayAbilitySpec Spec { Ability, 1 };
		if (const UAuraAbility* AuraAbility = Cast<UAuraAbility>(Spec.Ability))
		{
			Spec.GetDynamicSpecSourceTags().AddTag(AuraAbility->StartupInputTag);
			GiveAbility(Spec);
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (auto& Spec : GetActivatableAbilities())
		if (Spec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(Spec);
			if (!Spec.IsActive()) TryActivateAbility(Spec.Handle);
		}
}

void UAuraAbilitySystemComponent::AbilityInputReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (auto& Spec : GetActivatableAbilities())
		if (Spec.GetDynamicSpecSourceTags().HasTagExact(InputTag)) AbilitySpecInputReleased(Spec);
}
