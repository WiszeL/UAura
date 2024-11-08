// Copyright, NyuAnca 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Widgets/AuraUserWidget.h"
#include "AuraHUD.generated.h"

class UBaseWidgetController;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UAuraUserWidget;

UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	AAuraHUD();
	
	void PrepareHUD();
	
private:
	template <typename T>
	T* CreateController(const FWidgetControllerParams& Params, TSubclassOf<T> ControllerClass = T::StaticClass())
	{
		T* WidgetController = NewObject<T>(ControllerClass);
		WidgetController->PrepareController(Params);
		WidgetController->BindCallbacksToDependencies();

		return WidgetController;
	}

	template <typename T, typename Controller>
	T* CreateAuraWidget(TSubclassOf<T> WidgetClass, Controller* WidgetController)
	{
		T* Widget = CreateWidget<T>(GetOwningPlayerController(), WidgetClass);
		Widget->SetWidgetController(WidgetController);
		WidgetController->BroadcastInitData();
		Widget->AddToViewport();

		return Widget;
	}
	
	// ===== Overlay ===== //

	UPROPERTY(EditAnywhere, Category=Overlay)
	TSoftClassPtr<UOverlayWidgetController> OverlayWidgetControllerClass;
	
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY(EditAnywhere, Category=Overlay)
	TSoftClassPtr<UAuraUserWidget> OverlayClass;

	UPROPERTY()
	TObjectPtr<UAuraUserWidget> Overlay;
};
