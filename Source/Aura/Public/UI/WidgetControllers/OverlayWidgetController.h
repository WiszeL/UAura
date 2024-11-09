// Copyright, NyuAnca 2024

#pragma once

#include "CoreMinimal.h"
#include "BaseWidgetController.h"
#include "GameplayTagContainer.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeValueDelegate, float, NewValue);

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag EffectTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D> Image = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDynamicEffectAppliedDelagate, const FUIWidgetRow&, Row);

UCLASS()
class AURA_API UOverlayWidgetController : public UBaseWidgetController
{
	GENERATED_BODY()

public:
	UOverlayWidgetController();
	
	// ===== Events ===== //

	UPROPERTY(BlueprintAssignable, Category=Events)
	FDynamicEffectAppliedDelagate DynamicEffectAppliedDelegate;

	UPROPERTY(BlueprintCallable, Category=Events)
	FOnBtnPressedDelegate OnAttributeBtnPressed;
	
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitData() override;

	// ===== Data ===== //

	UPROPERTY(EditAnywhere, Category=Data)
	TSoftObjectPtr<UDataTable> EffectData;

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
