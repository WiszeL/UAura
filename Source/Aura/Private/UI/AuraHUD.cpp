// Copyright, NyuAnca 2024

#include "UI/AuraHUD.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "PlayerHandlers/AuraPlayerController.h"
#include "PlayerHandlers/AuraPlayerState.h"
#include "UI/WidgetControllers/OverlayWidgetController.h"

void AAuraHUD::PrepareHUD()
{
	// For Controller Params
	AAuraPlayerController* AuraPC = Cast<AAuraPlayerController>(GetOwningPlayerController());
	AAuraPlayerState* AuraPS = AuraPC->GetPlayerState<AAuraPlayerState>();
	UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AuraPS->GetAbilitySystemComponent());
	UAuraAttributeSet* AuraAS = AuraPS->GetAttributeSet();

	check(AuraPC);
	check(AuraPS);
	check(AuraASC);
	check(AuraPS);

	const FWidgetControllerParams Params { AuraPC, AuraPS, AuraAS, AuraASC };

	// Overlay
	OverlayWidgetController = CreateController<UOverlayWidgetController>(Params);
	Overlay = CreateAuraWidget<UAuraUserWidget, UOverlayWidgetController>(OverlayClass, OverlayWidgetController);
}
