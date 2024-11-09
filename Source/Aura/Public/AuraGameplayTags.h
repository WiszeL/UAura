// Copyright, NyuAnca 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

struct FAuraGameplayTags
{
private:
	static FAuraGameplayTags GameplayTags;
	
public:
	// ===== Vital Attributes ===== //

	FGameplayTag Attributes_Vital_Health;
	FGameplayTag Attributes_Vital_Mana;

	// ===== Primary Attributes ===== //

	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;
	
	// ===== Secondary Attributes ===== //

	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPen;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CritChance;
	FGameplayTag Attributes_Secondary_CritDamage;
	FGameplayTag Attributes_Secondary_CritRes;
	FGameplayTag Attributes_Secondary_HealthRegen;
	FGameplayTag Attributes_Secondary_ManaRegen;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;

	// ===== Effects ===== //

	FGameplayTag Effect_HealthPotion;
	FGameplayTag Effect_ManaPotion;
	FGameplayTag Effect_HealthCrystal;
	FGameplayTag Effect_ManaCrystal;

	// ===== Singleton ===== //
	
	static const FAuraGameplayTags& Get()
	{
		return GameplayTags;
	}

	static void InitNativeGameplayTags();
};
