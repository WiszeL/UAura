// Copyright, RilAnca 2024

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interfaces/CombatInterface.h"
#include "BaseCharacter.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UAuraAttributeSet;
class UAuraAbilitySystemComponent;

UCLASS(Abstract)
class ABaseCharacter : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	// ===== Events ===== //
	
	virtual void BeginPlay() override;

protected:
	// ===== Components ===== //

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

protected:
	// ===== Ability System ===== //

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComp;

	UPROPERTY()
	TObjectPtr<UAuraAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, Category="AbilitySystem|Attributes")
	TSoftClassPtr<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(EditAnywhere, Category="AbilitySystem|Attributes")
	TSoftClassPtr<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(EditAnywhere, Category="AbilitySystem|Attributes")
	TSoftClassPtr<UGameplayEffect> DefaultVitalAttributes;

	UPROPERTY(EditAnywhere, Category="AbilitySystem|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
	void ApplyEffectSelf(const TSubclassOf<UGameplayEffect>& EffectClass, const float Level = 1.f) const;
	void AddCharacterAbilities();
	
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	FORCEINLINE UAuraAttributeSet* GetAttributeSet() const
	{
		return AttributeSet;
	}

protected:
	// ===== Combat ===== //

	UPROPERTY(EditAnywhere, Category="Combat")
	FName CombatSocket;

public:
	virtual FVector GetCombatSocketLocation() const override
	{
		return WeaponMesh->GetSocketLocation(CombatSocket);
	}
};
