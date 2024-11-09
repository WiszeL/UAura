// Copyright, NyuAnca 2024

#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitNativeGameplayTags()
{
	UGameplayTagsManager& TagsManager = UGameplayTagsManager::Get();

	// Vital Attributes
	GameplayTags.Attributes_Vital_Health = TagsManager.AddNativeGameplayTag("Attributes.Vital.Health");
	GameplayTags.Attributes_Vital_Mana = TagsManager.AddNativeGameplayTag("Attributes.Vital.Mana");

	// Primary Attributes
	GameplayTags.Attributes_Primary_Strength = TagsManager.AddNativeGameplayTag("Attributes.Primary.Strength");
	GameplayTags.Attributes_Primary_Intelligence = TagsManager.AddNativeGameplayTag("Attributes.Primary.Intelligence");
	GameplayTags.Attributes_Primary_Resilience = TagsManager.AddNativeGameplayTag("Attributes.Primary.Resilience");
	GameplayTags.Attributes_Primary_Vigor = TagsManager.AddNativeGameplayTag("Attributes.Primary.Vigor");
	
	// Secondary Attributes
	GameplayTags.Attributes_Secondary_Armor = TagsManager.AddNativeGameplayTag("Attributes.Secondary.Armor");
	GameplayTags.Attributes_Secondary_ArmorPen = TagsManager.AddNativeGameplayTag("Attributes.Secondary.ArmorPen");
	GameplayTags.Attributes_Secondary_BlockChance = TagsManager.AddNativeGameplayTag("Attributes.Secondary.BlockChance");
	GameplayTags.Attributes_Secondary_CritChance = TagsManager.AddNativeGameplayTag("Attributes.Secondary.CritChance");
	GameplayTags.Attributes_Secondary_CritDamage = TagsManager.AddNativeGameplayTag("Attributes.Secondary.CritDamage");
	GameplayTags.Attributes_Secondary_CritRes = TagsManager.AddNativeGameplayTag("Attributes.Secondary.CritRes");
	GameplayTags.Attributes_Secondary_HealthRegen = TagsManager.AddNativeGameplayTag("Attributes.Secondary.HealthRegen");
	GameplayTags.Attributes_Secondary_ManaRegen = TagsManager.AddNativeGameplayTag("Attributes.Secondary.ManaRegen");
	GameplayTags.Attributes_Secondary_MaxHealth = TagsManager.AddNativeGameplayTag("Attributes.Secondary.MaxHealth");
	GameplayTags.Attributes_Secondary_MaxMana = TagsManager.AddNativeGameplayTag("Attributes.Secondary.MaxMana");

	// Effect
	GameplayTags.Effect_HealthPotion = TagsManager.AddNativeGameplayTag("Effect.HealthPotion");
	GameplayTags.Effect_ManaPotion = TagsManager.AddNativeGameplayTag("Effect.ManaPotion");
	GameplayTags.Effect_HealthCrystal = TagsManager.AddNativeGameplayTag("Effect.HealthCrystal");
	GameplayTags.Effect_ManaCrystal = TagsManager.AddNativeGameplayTag("Effect.ManaCrystal");
}
