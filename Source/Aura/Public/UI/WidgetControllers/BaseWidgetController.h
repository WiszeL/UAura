// Copyright, NyuAnca 2024

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "PlayerHandlers/AuraPlayerState.h"
#include "UObject/Object.h"
#include "BaseWidgetController.generated.h"

class UAuraAttributeSet;
class UAuraAbilitySystemComponent;
class AAuraPlayerState;
class AAuraPlayerController;

struct FWidgetControllerParams
{
	AAuraPlayerController* PC;
	AAuraPlayerState* PS;
	UAuraAttributeSet* AS;
	UAuraAbilitySystemComponent* ASC;
	
	FWidgetControllerParams(AAuraPlayerController* InPC, AAuraPlayerState* InPS, UAuraAttributeSet* InAS, UAuraAbilitySystemComponent* InASC):
		PC(InPC),
		PS(InPS),
		AS(InAS),
		ASC(InASC)
	{
	}
};

UCLASS(BlueprintType)
class AURA_API UBaseWidgetController : public UObject
{
	GENERATED_BODY()

public:
	void PrepareController(const FWidgetControllerParams& Params);
	virtual void BroadcastInitData() {}
	virtual void BindCallbacksToDependencies() {}
	
protected:
	TWeakObjectPtr<AAuraPlayerController> PlayerController;
	TWeakObjectPtr<AAuraPlayerState> PlayerState;
	TWeakObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComp;
	TWeakObjectPtr<UAuraAttributeSet> AttributeSet;
};
