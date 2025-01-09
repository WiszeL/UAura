// Copyright, RilAnca 2024

#include "AbilitySystem/Abilities/ProjectileAbility.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameplayEffector/BaseProjectile.h"
#include "Interfaces/CombatInterface.h"

void UProjectileAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	CombatInterface = GetAvatarActorFromActorInfo();
	if (!HasAuthority(&ActivationInfo) || !CombatInterface) return;

	const auto FireMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this, NAME_None, FireMontage.LoadSynchronous()
	);
	FireMontageTask->ReadyForActivation();
	// FTransform SpawnTransform;
	//
	// // Getting the location of combat socket
	// SpawnTransform.SetLocation(CombatInterface->GetCombatSocketLocation());
	//
	// // Spawn
	// AActor* Projectile = GetWorld()->SpawnActorDeferred<ABaseProjectile>(ProjectileClass, SpawnTransform,
	// 	GetOwningActorFromActorInfo(),
	// 	Cast<APawn>(GetAvatarActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	// Projectile->FinishSpawning(SpawnTransform);
}
