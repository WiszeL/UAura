// Copyright, NyuAnca 2024

#pragma once

#include "CoreMinimal.h"
#include "BaseWidgetController.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeValueDelegate, float, NewValue);

UCLASS()
class AURA_API UOverlayWidgetController : public UBaseWidgetController
{
	GENERATED_BODY()

public:
	// ===== Events ===== //
	
	virtual void BroadcastInitData() override;
	virtual void BindCallbacksToDependencies() override;

	// ===== Values ===== //

	UPROPERTY(BlueprintAssignable, Category=VitalAttributes)
	FOnChangeValueDelegate OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category=VitalAttributes)
	FOnChangeValueDelegate OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category=VitalAttributes)
	FOnChangeValueDelegate OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category=VitalAttributes)
	FOnChangeValueDelegate OnMaxManaChanged;
};
