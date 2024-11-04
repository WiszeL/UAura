// Copyright, NyuAnca 2024

#include "UI/Widgets/AuraUserWidget.h"

#include "Blueprint/WidgetTree.h"
#include "UI/WidgetControllers/BaseWidgetController.h"

void UAuraUserWidget::SetWidgetController(UBaseWidgetController* InController)
{
	// Set the controller
	WidgetController = InController;
	OnWidgetControllerSet();

	// Set to the children if they have "Inherit" controller interface.
	TArray<UWidget*> Children;
	WidgetTree->GetAllWidgets(Children);

	for (const auto Child : Children)
		if (UAuraUserWidget* AuraWidget = Cast<UAuraUserWidget>(Child))
			if (AuraWidget->bInheritController) AuraWidget->SetWidgetController(InController);
}
