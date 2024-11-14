// Copyright, NyuAnca 2024

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAuraAttributeSet;
class UAuraAbilitySystemComponent;

UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraPlayerState();

	// ===== Events ===== //

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
private:
	// ===== Ability System ===== //

	UPROPERTY(ReplicatedUsing=OnRep_CombatLevel)
	uint16 CombatLevel = 1;
	
	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComp;

	UPROPERTY()
	TObjectPtr<UAuraAttributeSet> AttributeSet;

	UFUNCTION()
	void OnRep_CombatLevel(uint16 OldCombatLevel);
	
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	FORCEINLINE UAuraAttributeSet* GetAttributeSet() const
	{
		return AttributeSet;
	}

	FORCEINLINE virtual uint16 GetCombatLevel() const
	{
		return CombatLevel;
	}
};
