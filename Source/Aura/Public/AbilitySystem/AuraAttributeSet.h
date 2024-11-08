// Copyright, NyuAnca 2024

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

struct FEffectProps
{
	UAbilitySystemComponent* AbilitySystemComp = nullptr;
	AActor* Avatar = nullptr;
	AController* Controller = nullptr;
	ACharacter* Character = nullptr;

	FGameplayEffectContextHandle CtxHandle;
};

UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();

	// ===== Events ===== //
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	static void SetEffectProps(const FGameplayEffectModCallbackData& Data, FEffectProps& Source, FEffectProps& Target);
	
	// ===== Vital Attributes ===== //

	/* Health */
	
	UPROPERTY(ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	ATTRIBUTE_ACCESSORS(ThisClass, Health);

	/* Mana */
	UPROPERTY(ReplicatedUsing=OnRep_Mana)
	FGameplayAttributeData Mana;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	ATTRIBUTE_ACCESSORS(ThisClass, Mana);

	// ===== Primary Attributes ===== //

	/* Strength */

	UPROPERTY(ReplicatedUsing=OnRep_Strength)
	FGameplayAttributeData Strength;

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

	ATTRIBUTE_ACCESSORS(ThisClass, Strength);

	/* Intelligence */

	UPROPERTY(ReplicatedUsing=OnRep_Intelligence)
	FGameplayAttributeData Intelligence;

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

	ATTRIBUTE_ACCESSORS(ThisClass, Intelligence);

	/* Resilience */

	UPROPERTY(ReplicatedUsing=OnRep_Resilience)
	FGameplayAttributeData Resilience;

	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;

	ATTRIBUTE_ACCESSORS(ThisClass, Resilience);

	/* Vigor */

	UPROPERTY(ReplicatedUsing=OnRep_Vigor)
	FGameplayAttributeData Vigor;

	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;

	ATTRIBUTE_ACCESSORS(ThisClass, Vigor);

	// ===== Secondary Attributes ===== //

	/* Armor */

	UPROPERTY(ReplicatedUsing=OnRep_Armor)
	FGameplayAttributeData Armor;

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

	ATTRIBUTE_ACCESSORS(ThisClass, Armor);

	/* ArmorPen */

	UPROPERTY(ReplicatedUsing=OnRep_ArmorPen)
	FGameplayAttributeData ArmorPen;

	UFUNCTION()
	void OnRep_ArmorPen(const FGameplayAttributeData& OldArmorPen) const;

	ATTRIBUTE_ACCESSORS(ThisClass, ArmorPen);

	/* BlockChance */

	UPROPERTY(ReplicatedUsing=OnRep_BlockChance)
	FGameplayAttributeData BlockChance;

	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;

	ATTRIBUTE_ACCESSORS(ThisClass, BlockChance);

	/* CritChance */

	UPROPERTY(ReplicatedUsing=OnRep_CritChance)
	FGameplayAttributeData CritChance;

	UFUNCTION()
	void OnRep_CritChance(const FGameplayAttributeData& OldCritChance) const;

	ATTRIBUTE_ACCESSORS(ThisClass, CritChance);

	/* CritDamage */

	UPROPERTY(ReplicatedUsing=OnRep_CritDamage)
	FGameplayAttributeData CritDamage;

	UFUNCTION()
	void OnRep_CritDamage(const FGameplayAttributeData& OldCritDamage) const;

	ATTRIBUTE_ACCESSORS(ThisClass, CritDamage);

	/* CritRes */

	UPROPERTY(ReplicatedUsing=OnRep_CritRes)
	FGameplayAttributeData CritRes;

	UFUNCTION()
	void OnRep_CritRes(const FGameplayAttributeData& OldCritRes) const;

	ATTRIBUTE_ACCESSORS(ThisClass, CritRes);

	/* HealthRegen */

	UPROPERTY(ReplicatedUsing=OnRep_HealthRegen)
	FGameplayAttributeData HealthRegen;

	UFUNCTION()
	void OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen) const;

	ATTRIBUTE_ACCESSORS(ThisClass, HealthRegen);

	/* ManaRegen */

	UPROPERTY(ReplicatedUsing=OnRep_ManaRegen)
	FGameplayAttributeData ManaRegen;

	UFUNCTION()
	void OnRep_ManaRegen(const FGameplayAttributeData& OldManaRegen) const;

	ATTRIBUTE_ACCESSORS(ThisClass, ManaRegen);

	/* Max Health */
	
	UPROPERTY(ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	ATTRIBUTE_ACCESSORS(ThisClass, MaxHealth);
	
	/* Max Mana */

	UPROPERTY(ReplicatedUsing=OnRep_MaxMana)
	FGameplayAttributeData MaxMana;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	ATTRIBUTE_ACCESSORS(ThisClass, MaxMana);
};
