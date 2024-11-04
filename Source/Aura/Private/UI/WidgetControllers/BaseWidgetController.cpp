// Copyright, NyuAnca 2024

#include "UI/WidgetControllers/BaseWidgetController.h"

#include "PlayerHandlers/AuraPlayerController.h"

void UBaseWidgetController::PrepareController(const FWidgetControllerParams& Params)
{
	PlayerController = Params.PC;
	PlayerState = Params.PS;
	AttributeSet = Params.AS;
	AbilitySystemComp = Params.ASC;
}
