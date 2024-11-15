// Copyright, RilAnca 2024

#include "GameplayEffector/BaseEffector.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

ABaseEffector::ABaseEffector()
{
	PrimaryActorTick.bCanEverTick = false;
}

// ===== Gameplay Effects ===== //

void ABaseEffector::ApplyGameplayEffect(UAbilitySystemComponent* TargetAbility, const FGameplayEffectData& Effect, bool& bApplied)
{
	if (TargetAbility->GetAvatarActor()->ActorHasTag("Enemy") && !bAppliesToEnemy) return;
	
	FGameplayEffectContextHandle CtxHandle = TargetAbility->MakeEffectContext();
	CtxHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle EffectSpec = TargetAbility->MakeOutgoingSpec(Effect.FXClass, EffectLevel, CtxHandle);
	FActiveGameplayEffectHandle ActiveEffectHandle = TargetAbility->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data);

	// Handle infinite removal 
	const bool bInfinite = EffectSpec.Data->Def->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bInfinite && Effect.RemovalPolicy != ERemovalPolicy::DoNotRemove)
	{
		ActivesEffect.Add(TargetAbility, { Effect, ActiveEffectHandle });
	}

	// Inform that it's been applied
	bApplied = true;
}

void ABaseEffector::OnEffectBeginOverlap(AActor* OtherActor)
{
	const IAbilitySystemInterface* AbilityInterface = Cast<IAbilitySystemInterface>(OtherActor);

	if (!AbilityInterface) return;

	UAbilitySystemComponent* TargetAbility = AbilityInterface->GetAbilitySystemComponent();

	// Handle Applying
	bool bApplied = false;
	
	for (const auto& Effect : AppliesGameplayEffects)
	{
		if (Effect.ApplyPolicy != EApplyPolicy::ApplyOnBeginOverlap) continue;
		
		ApplyGameplayEffect(TargetAbility, Effect, bApplied);
	}

	// Auto destroy
	if (bDestroyAfterApplyingEffect && bApplied) Destroy();
}

void ABaseEffector::OnEffectEndOverlap(AActor* OtherActor)
{
	const IAbilitySystemInterface* AbilityInterface = Cast<IAbilitySystemInterface>(OtherActor);

	if (!AbilityInterface) return;

	UAbilitySystemComponent* TargetAbility = AbilityInterface->GetAbilitySystemComponent();
	
	// Handle Applying
	bool bApplied = false;
	
	for (const auto& Effect : AppliesGameplayEffects)
	{
		if (Effect.ApplyPolicy != EApplyPolicy::ApplyOnEndOverlap) continue;
		
		ApplyGameplayEffect(TargetAbility, Effect, bApplied);
	}
	
	// Handle removal
	TArray<FActiveEffectHandle> ToRemove;
	
	ActivesEffect.MultiFind(TargetAbility, ToRemove);
	
	for (const auto& ActiveToRemove : ToRemove)
	{
		if (ActiveToRemove.AppliedEffect.RemovalPolicy != ERemovalPolicy::RemoveOnEndOverlap) continue;
		
		TargetAbility->RemoveActiveGameplayEffect(ActiveToRemove.Handle, 1);
		ActivesEffect.Remove(TargetAbility, ActiveToRemove);
	}

	// Auto destroy
 	if (bDestroyAfterApplyingEffect && bApplied) Destroy();
}