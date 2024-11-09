// Copyright, NyuAnca 2024

#include "UI/AuraHUD.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "PlayerHandlers/AuraPlayerController.h"
#include "PlayerHandlers/AuraPlayerState.h"
#include "UI/WidgetControllers/AttrMenuWidgetController.h"
#include "UI/WidgetControllers/OverlayWidgetController.h"
#include "UI/Widgets/AuraUserWidget.h"

AAuraHUD::AAuraHUD()
{
	// Init Asset
	OverlayWidgetControllerClass = FSoftClassPath { TEXT("/Game/Blueprints/UI/WidgetControllers/BP_OverlayWidgetController.BP_OverlayWidgetController_C") };
	OverlayClass = FSoftClassPath { TEXT("/Game/Blueprints/UI/Overlay/WBP_Overlay.WBP_Overlay_C") };

	AttributeMenuClass = FSoftClassPath { TEXT("/Game/Blueprints/UI/AttributeMenu/WBP_AttributeMenu.WBP_AttributeMenu_C") };
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
	Overlay = CreateAuraWidget(OverlayClass.LoadSynchronous(), OverlayWidgetController);

	// Attribute Menu
	AttrMenuWidgetController = CreateController<UAttrMenuWidgetController>(Params);
	AttributeMenu = CreateAuraWidget(AttributeMenuClass.LoadSynchronous(), AttrMenuWidgetController);
	AttributeMenu->SetVisibility(ESlateVisibility::Collapsed);

	/* Set the menu position */
	const FVector2D AttrMenuPosition {
		AttributeMenu->GetViewportOffsetByPercentage(EAxis::X, 1.f),
		AttributeMenu->GetViewportOffsetByPercentage(EAxis::Y, 6.5f),
	};
	AttributeMenu->SetPositionInViewport(AttrMenuPosition);
	
	// ...
	BindToControllerDelegate();
}

UAuraUserWidget* AAuraHUD::CreateAuraWidget(const TSubclassOf<UAuraUserWidget>& WidgetClass,
	UBaseWidgetController* WidgetController) const
{
	UAuraUserWidget* Widget = CreateWidget<UAuraUserWidget>(GetOwningPlayerController(), WidgetClass);
	Widget->SetWidgetController(WidgetController);
	if (WidgetController) WidgetController->BroadcastInitData();
	Widget->AddToViewport();

	return Widget;
}

void AAuraHUD::BindToControllerDelegate()
{
	// Bind to show/hide attribute menu
	OverlayWidgetController->OnAttributeBtnPressed.AddDynamic(this, &ThisClass::ShowAttributeMenu);
	AttrMenuWidgetController->OnCloseBtnPressed.AddDynamic(this, &ThisClass::ShowAttributeMenu);
}

// ===== Attribute Menu ===== //

void AAuraHUD::ShowAttributeMenu()
{
	bShowAttributeMenu = !bShowAttributeMenu;
	AttributeMenu->SetVisibility(bShowAttributeMenu ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}
