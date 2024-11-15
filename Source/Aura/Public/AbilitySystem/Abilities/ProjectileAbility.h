// Copyright, RilAnca 2024

#pragma once

#include "CoreMinimal.h"
#include "AuraAbility.h"
#include "ProjectileAbility.generated.h"

class ABaseProjectile;

UCLASS()
class AURA_API UProjectileAbility : public UAuraAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	// ===== Properties ===== //

	UPROPERTY(EditDefaultsOnly, Category=Properties)
	TSubclassOf<ABaseProjectile> ProjectileClass;
};
