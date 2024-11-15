// Copyright, RilAnca 2024

#include "UI/WidgetControllers/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "PlayerHandlers/AuraPlayerController.h"

UOverlayWidgetController::UOverlayWidgetController()
{
	EffectData = FSoftObjectPath { TEXT("/Game/Data/DataTables/DT_EffectData.DT_EffectData") };
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	// Vital Attributes Changes
	AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnHealthChanged.Broadcast(Data.NewValue);
	});
	
	AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHealthAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnMaxHealthChanged.Broadcast(Data.NewValue);
	});

	AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetManaAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnManaChanged.Broadcast(Data.NewValue);
	});

	AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxManaAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnMaxManaChanged.Broadcast(Data.NewValue);
	});

	// Effect Applied
	AbilitySystemComp->EffectAppliedDelegate.AddLambda([this](const FGameplayTagContainer& TagContainer)
	{
		for (const auto& Tag : TagContainer)
		{
			if (!Tag.MatchesTag(FGameplayTag::RequestGameplayTag("Effect"))) continue;
			
			const FUIWidgetRow* Row = EffectData.LoadSynchronous()->FindRow<FUIWidgetRow>(Tag.GetTagName(), "");
			DynamicEffectAppliedDelegate.Broadcast(*Row);
		}
	});
}

void UOverlayWidgetController::BroadcastInitData()
{
	// Broadcast vital attributes
	OnHealthChanged.Broadcast(AttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AttributeSet->GetMaxMana());
}
