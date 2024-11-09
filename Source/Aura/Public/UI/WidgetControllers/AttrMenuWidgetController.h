// Copyright, NyuAnca 2024

#pragma once

#include "CoreMinimal.h"
#include "BaseWidgetController.h"
#include "GameplayTagContainer.h"
#include "AttrMenuWidgetController.generated.h"

struct FAuraAttributeInfo;
class UAttributeInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedDelegate, const FAuraAttributeInfo&, Info);

UCLASS()
class AURA_API UAttrMenuWidgetController : public UBaseWidgetController
{
	GENERATED_BODY()

public:
	UAttrMenuWidgetController();
	
	// ===== Events ===== //
	
	UPROPERTY(BlueprintCallable, Category=Events)
	FOnBtnPressedDelegate OnCloseBtnPressed;

	UPROPERTY(BlueprintAssignable, Category=Events)
	FOnAttributeChangedDelegate OnAttributeChanged;

	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitData() override;

private:
	// ===== Data ===== //

	UPROPERTY(EditDefaultsOnly, Category=Data)
	TSoftObjectPtr<UAttributeInfo> AttributeData;

	void BroadcastAttribute(const FGameplayTag& Tag) const;
};
