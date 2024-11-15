// Copyright, RilAnca 2024

#include "AbilitySystem/Abilities/ProjectileAbility.h"

#include "GameplayEffector/BaseProjectile.h"
#include "Interfaces/CombatInterface.h"

void UProjectileAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	if (!HasAuthority(&ActivationInfo)) return;

	FTransform SpawnTransform;
	
	// Getting the location of combat socket
	const ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	SpawnTransform.SetLocation(CombatInterface->GetCombatSocketLocation());
	
	// Spawn
	AActor* Projectile = GetWorld()->SpawnActorDeferred<ABaseProjectile>(ProjectileClass, SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetAvatarActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	Projectile->FinishSpawning(SpawnTransform);
}
