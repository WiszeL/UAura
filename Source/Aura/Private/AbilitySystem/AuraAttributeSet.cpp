// Copyright, NyuAnca 2024

#include "AbilitySystem/AuraAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(10.f);
	InitMaxHealth(100.f);
	InitMana(5.f);
	InitMaxMana(50.f);
}

// ===== Events ===== //

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxMana, COND_None, REPNOTIFY_Always);
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

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxMana, OldMaxMana);
}
