// Copyright, NyuAnca 2024

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAppliedDelegate, const FGameplayTagContainer&)

UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// ===== Events ===== //

	FEffectAppliedDelegate EffectAppliedDelegate;
	
	virtual void OnPlayerControllerSet() override;

private:
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComp, const FGameplayEffectSpec& Spec, FActiveGameplayEffectHandle ActiveHandle) const;

public:
	// ===== Abilities ===== //

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);

	void AbilityInputPressed(const FGameplayTag& InputTag);
	void AbilityInputReleased(const FGameplayTag& InputTag);
};
