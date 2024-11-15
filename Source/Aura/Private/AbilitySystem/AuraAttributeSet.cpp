// Copyright, RilAnca 2024

#include "AbilitySystem/AuraAttributeSet.h"

#include "AuraGameplayTags.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	// Map the attributes to its gameplay tag
	const FAuraGameplayTags& Tags = FAuraGameplayTags::Get();

	/* Vital Attrs */
	AttributeMap.Add(Tags.Attributes_Vital_Health, GetHealthAttribute);
	AttributeMap.Add(Tags.Attributes_Vital_Mana, GetManaAttribute);

	/* Primary Attrs */
	AttributeMap.Add(Tags.Attributes_Primary_Strength, GetStrengthAttribute);
	AttributeMap.Add(Tags.Attributes_Primary_Intelligence, GetIntelligenceAttribute);
	AttributeMap.Add(Tags.Attributes_Primary_Resilience, GetResilienceAttribute);
	AttributeMap.Add(Tags.Attributes_Primary_Vigor, GetVigorAttribute);
	
	/* Secondary Attrs */
	AttributeMap.Add(Tags.Attributes_Secondary_Armor, GetArmorAttribute);
	AttributeMap.Add(Tags.Attributes_Secondary_ArmorPen, GetArmorPenAttribute);
	AttributeMap.Add(Tags.Attributes_Secondary_BlockChance, GetBlockChanceAttribute);
	AttributeMap.Add(Tags.Attributes_Secondary_CritChance, GetCritChanceAttribute);
	AttributeMap.Add(Tags.Attributes_Secondary_CritDamage, GetCritDamageAttribute);
	AttributeMap.Add(Tags.Attributes_Secondary_CritRes, GetCritResAttribute);
	AttributeMap.Add(Tags.Attributes_Secondary_HealthRegen, GetHealthRegenAttribute);
	AttributeMap.Add(Tags.Attributes_Secondary_ManaRegen, GetManaRegenAttribute);
	AttributeMap.Add(Tags.Attributes_Secondary_MaxHealth, GetMaxHealthAttribute);
	AttributeMap.Add(Tags.Attributes_Secondary_MaxMana, GetMaxManaAttribute);
}

// ===== Events ===== //

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Vigor, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ArmorPen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CritChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CritDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CritRes, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, HealthRegen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ManaRegen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetHealthAttribute()) NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	else if (Attribute == GetManaAttribute()) NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	FEffectProps Source;
	FEffectProps Target;
	SetEffectProps(Data, Source, Target);
}

void UAuraAttributeSet::SetEffectProps(const FGameplayEffectModCallbackData& Data, FEffectProps& Source,
                                       FEffectProps& Target)
{
	Source.CtxHandle = Target.CtxHandle = Data.EffectSpec.GetContext();
	
	// Getting the source data
	Source.AbilitySystemComp = Source.CtxHandle.GetOriginalInstigatorAbilitySystemComponent();
	Source.Avatar = Source.AbilitySystemComp->AbilityActorInfo->AvatarActor.Get();
	if (const APawn* SourcePawn = Cast<APawn>(Source.Avatar)) Source.Controller = SourcePawn->GetController();
	if (Source.Controller) Source.Character = Source.Controller->GetCharacter();

	// Getting the target source data
	Target.AbilitySystemComp = Data.Target.AbilityActorInfo->AbilitySystemComponent.Get();
	Target.Avatar = Target.AbilitySystemComp->AbilityActorInfo->AvatarActor.Get();
	if (const APawn* TargetPawn = Cast<APawn>(Target.Avatar)) Target.Controller = TargetPawn->GetController();
	if (Target.Controller) Target.Character = Target.Controller->GetCharacter();
}

// ===== Vital Attributes ===== //

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Mana, OldMana);
}

// ===== Primary Attributes ===== //

void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Strength, OldStrength);
}

void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Intelligence, OldIntelligence);
}

void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Resilience, OldResilience);
}

void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Vigor, OldVigor);
}

// ===== Secondary Attributes ===== //

void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Armor, OldArmor);
}

void UAuraAttributeSet::OnRep_ArmorPen(const FGameplayAttributeData& OldArmorPen) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, ArmorPen, OldArmorPen);
}

void UAuraAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, BlockChance, OldBlockChance);
}

void UAuraAttributeSet::OnRep_CritChance(const FGameplayAttributeData& OldCritChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, CritChance, OldCritChance);
}

void UAuraAttributeSet::OnRep_CritDamage(const FGameplayAttributeData& OldCritDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, CritDamage, OldCritDamage);
}

void UAuraAttributeSet::OnRep_CritRes(const FGameplayAttributeData& OldCritRes) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, CritRes, OldCritRes);
}

void UAuraAttributeSet::OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, HealthRegen, OldHealthRegen);
}

void UAuraAttributeSet::OnRep_ManaRegen(const FGameplayAttributeData& OldManaRegen) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, ManaRegen, OldManaRegen);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxMana, OldMaxMana);
}
