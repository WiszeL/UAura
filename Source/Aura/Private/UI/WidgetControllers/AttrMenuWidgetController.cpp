// Copyright, RilAnca 2024

#include "UI/WidgetControllers/AttrMenuWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Data/AttributeInfo.h"
#include "Helpers/AssetHelper.h"

UAttrMenuWidgetController::UAttrMenuWidgetController()
{
	// Init Asset
	INIT_LOAD_ASSET(AttributeData, "/Game/Data/DataAssets/DA_AttributeInfo.DA_AttributeInfo")
}

// ===== Events ===== //

void UAttrMenuWidgetController::BindCallbacksToDependencies()
{
	check(AttributeData)
	
	for (const auto& Attr : AttributeSet->AttributeMap)
	{
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(Attr.Value())
			.AddLambda([this, Attr](const FOnAttributeChangeData&)
		{
			BroadcastAttribute(Attr.Key);
		});
	}
}

void UAttrMenuWidgetController::BroadcastInitData()
{
	for (const auto& Attr : AttributeSet->AttributeMap)
		BroadcastAttribute(Attr.Key);
}

// ===== Data ===== //

void UAttrMenuWidgetController::BroadcastAttribute(const FGameplayTag& Tag) const
{
	// Get the info from data asset
	FAuraAttributeInfo Info = AttributeData->FindByTag(Tag);

	// Fill the value from the actual data
	const FGameplayAttribute& Attribute = AttributeSet->AttributeMap[Tag]();
	Info.Value = Attribute.GetNumericValue(AttributeSet.Get());

	// Broadcast
	OnAttributeChanged.Broadcast(Info);
}
