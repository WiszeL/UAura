// Copyright, NyuAnca 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAttrMenuWidgetController;
class UAuraUserWidget;
class UBaseWidgetController;
struct FWidgetControllerParams;
class UOverlayWidgetController;

UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	AAuraHUD();
	
	void PrepareHUD();
	
private:
	template <typename T>
	T* CreateController(const FWidgetControllerParams& Params, const TSubclassOf<T>& ControllerClass = T::StaticClass())
	{
		T* WidgetController = NewObject<T>(ControllerClass);
		WidgetController->PrepareController(Params);
		WidgetController->BindCallbacksToDependencies();

		return WidgetController;
	}

	UAuraUserWidget* CreateAuraWidget(const TSubclassOf<UAuraUserWidget>& WidgetClass, UBaseWidgetController* WidgetController = nullptr) const;
	
	/** A place where we can bind an event from widget controller */
	void BindToControllerDelegate();
	
	// ===== Overlay ===== //

	UPROPERTY(EditAnywhere, Category=Overlay)
	TSoftClassPtr<UOverlayWidgetController> OverlayWidgetControllerClass;
	
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY(EditAnywhere, Category=Overlay)
	TSoftClassPtr<UAuraUserWidget> OverlayClass;

	UPROPERTY()
	TObjectPtr<UAuraUserWidget> Overlay;

	// ===== Attribute Menu ===== //

	bool bShowAttributeMenu = false;

	UPROPERTY()
	TObjectPtr<UAttrMenuWidgetController> AttrMenuWidgetController;
	
	UPROPERTY(EditAnywhere, Category=AttributeMenu)
	TSoftClassPtr<UAuraUserWidget> AttributeMenuClass;
	
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> AttributeMenu;

	UFUNCTION()
	void ShowAttributeMenu();
};
