// Copyright, RilAnca 2024

#include "UI/WidgetControllers/BaseWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "PlayerHandlers/AuraPlayerController.h"
#include "PlayerHandlers/AuraPlayerState.h"

void UBaseWidgetController::PrepareController(const FWidgetControllerParams& Params)
{
	PlayerController = Params.PC;
	PlayerState = Params.PS;
	AttributeSet = Params.AS;
	AbilitySystemComp = Params.ASC;
}
