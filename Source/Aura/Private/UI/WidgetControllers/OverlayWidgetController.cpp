// Copyright, NyuAnca 2024

#include "UI/WidgetControllers/OverlayWidgetController.h"

void UOverlayWidgetController::BroadcastInitData()
{
	// Broadcast vital attributes
	OnHealthChanged.Broadcast(AttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
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
}
