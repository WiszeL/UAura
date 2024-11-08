// Copyright, NyuAnca 2024

#include "UI/AuraHUD.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "PlayerHandlers/AuraPlayerController.h"
#include "PlayerHandlers/AuraPlayerState.h"
#include "UI/WidgetControllers/OverlayWidgetController.h"

AAuraHUD::AAuraHUD()
{
	// Init Asset
	OverlayWidgetControllerClass = FSoftClassPath { TEXT("/Game/Blueprints/UI/WidgetControllers/BP_OverlayWidgetController.BP_OverlayWidgetController_C") };
	OverlayClass = FSoftClassPath { TEXT("/Game/Blueprints/UI/Overlay/WBP_Overlay.WBP_Overlay_C") };
}

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
	OverlayWidgetController = CreateController<UOverlayWidgetController>(Params, OverlayWidgetControllerClass.LoadSynchronous());
	Overlay = CreateAuraWidget<UAuraUserWidget, UOverlayWidgetController>(OverlayClass.LoadSynchronous(), OverlayWidgetController);
}
