// Copyright, NyuAnca 2024

#include "PlayerHandlers/AuraPlayerState.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"

AAuraPlayerState::AAuraPlayerState()
{
	SetNetUpdateFrequency(100.f);

	// Ability System
	AbilitySystemComp = CreateDefaultSubobject<UAuraAbilitySystemComponent>("Ability System");
	AbilitySystemComp->SetIsReplicated(true);
	AbilitySystemComp->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("Attribute Set");
}

// ===== Events ==== //

void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAuraPlayerState, CombatLevel);
}

// ===== Ability System ===== //

void AAuraPlayerState::OnRep_CombatLevel(uint16 OldCombatLevel)
{
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}
