// Copyright, NyuAnca 2024

#include "UI/Widgets/AuraUserWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
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

float UAuraUserWidget::GetViewportOffsetByPercentage(const TEnumAsByte<EAxis::Type> Axis, const float Percentage)
{
	const FVector2D Size = UWidgetLayoutLibrary::GetViewportSize(this);
	
	return Axis == EAxis::X ? Size.X * Percentage / 100.f : Size.Y * Percentage / 100.f;
}
