// Copyright, NyuAnca 2024

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

void UAttrMenuWidgetController::BroadcastAttribute(const FGameplayTag& Tag) const
{
	FAuraAttributeInfo Info = AttributeData->FindByTag(Tag);
	const FGameplayAttribute& Attribute = AttributeSet->AttributeMap[Tag]();
	Info.Value = Attribute.GetNumericValue(AttributeSet.Get());
	OnAttributeChanged.Broadcast(Info);
}
