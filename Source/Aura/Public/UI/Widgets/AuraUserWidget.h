// Copyright, NyuAnca 2024

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

class UBaseWidgetController;

UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	// ===== Widget Controller ===== //
	
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<UBaseWidgetController> WidgetController;

	/** Called right after the widget controller is set */
	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetControllerSet();

public:
	UPROPERTY(EditAnywhere, Category=Properties)
	bool bInheritController = false;
	
	void SetWidgetController(UBaseWidgetController* InController);
};
