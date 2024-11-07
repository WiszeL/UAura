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

	// Secondary Attributes
	GameplayTags.Attributes_Secondary_MaxHealth = TagsManager.AddNativeGameplayTag("Attributes.Secondary.MaxHealth");
	GameplayTags.Attributes_Secondary_MaxMana = TagsManager.AddNativeGameplayTag("Attributes.Secondary.MaxMana");

	// Effect
	GameplayTags.Effect_HealthPotion = TagsManager.AddNativeGameplayTag("Effect.HealthPotion");
	GameplayTags.Effect_ManaPotion = TagsManager.AddNativeGameplayTag("Effect.ManaPotion");
	GameplayTags.Effect_HealthCrystal = TagsManager.AddNativeGameplayTag("Effect.HealthCrystal");
	GameplayTags.Effect_ManaCrystal = TagsManager.AddNativeGameplayTag("Effect.ManaCrystal");
}
