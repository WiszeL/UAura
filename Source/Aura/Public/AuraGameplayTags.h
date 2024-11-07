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

	// ===== Secondary Attributes ===== //
	
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
