#include "BUITweenBPLibrary.h"


UWidget* UBUITweenBPLibrary::PlayTween(UWidget* TargetWidget, const FBUITweenValues& FromValues, const FBUITweenValues& ToValues, float Duration, float Delay,
	bool bRestoreInitialValues, bool bPlayFromStart, EBUIEasingType EasingType)
{
	return PlayTweenAndWatch(TargetWidget, FromValues, ToValues, FOnAnimationComplete(),Duration, Delay, bRestoreInitialValues, bPlayFromStart, EasingType);
}

UWidget* UBUITweenBPLibrary::PlayTweenAndWatch(UWidget* TargetWidget, const FBUITweenValues& FromValues, const FBUITweenValues& ToValues, FOnAnimationComplete OnComplete,
                                               float Duration, float Delay, bool bRestoreInitialValues, bool bPlayFromStart, EBUIEasingType EasingType)
{
	if (!TargetWidget)
	{
		return nullptr;
	}

	// Get initial values from the widget
	const FBUITweenValues InitialValues;// = GetInitialValues(TargetWidget);
	auto& TweenInstance = UBUITween::Create(TargetWidget, Duration, Delay);

	if (bPlayFromStart)
	{
		TweenInstance.ToReset().Apply(1.0f);
	}
	TweenInstance.ApplyChangedValues(FromValues, ToValues, InitialValues);

	TweenInstance.OnComplete(FBUITweenSignature::CreateLambda([OnComplete, bRestoreInitialValues, InitialValues](UWidget* Owner)
	{
		if (bRestoreInitialValues)
		{
			InitialValues.RestoreToWidget(Owner);
		}
		OnComplete.ExecuteIfBound();
	}));

	// Set easing and begin
	TweenInstance.Easing(EasingType).Begin();
	return TargetWidget;
}

FBUITweenValues UBUITweenBPLibrary::GetInitialValues(UWidget* TargetWidget)
{
	FBUITweenValues Values;
	if (!TargetWidget)
	{
		return Values;
	}

	// Get basic transform values
	Values.Translation = TargetWidget->GetRenderTransform().Translation;
	Values.Rotation = TargetWidget->GetRenderTransform().Angle;
	Values.Scale = TargetWidget->GetRenderTransform().Scale;
	Values.Opacity = TargetWidget->GetRenderOpacity();
	Values.Visibility = TargetWidget->GetVisibility();

	// Get color from different widget types
	if (UUserWidget* UW = Cast<UUserWidget>(TargetWidget))
	{
		Values.Color = UW->GetColorAndOpacity();
	}
	else if (UImage* UI = Cast<UImage>(TargetWidget))
	{
		Values.Color = UI->GetColorAndOpacity();
	}
	else if (UBorder* Border = Cast<UBorder>(TargetWidget))
	{
		Values.Color = Border->GetContentColorAndOpacity();
	}

	// Get canvas position
	if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(TargetWidget->Slot))
	{
		Values.CanvasPosition = CanvasSlot->GetPosition();
	}

	// Get max desired height
	if (USizeBox* SizeBox = Cast<USizeBox>(TargetWidget))
	{
		Values.MaxDesiredHeight = SizeBox->GetMaxDesiredHeight();
	}

	// Get padding from different slot types
	if (UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(TargetWidget->Slot))
	{
		Values.Padding = OverlaySlot->GetPadding();
	}
	else if (UHorizontalBoxSlot* HorizontalBoxSlot = Cast<UHorizontalBoxSlot>(TargetWidget->Slot))
	{
		Values.Padding = HorizontalBoxSlot->GetPadding();
	}
	else if (UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(TargetWidget->Slot))
	{
		Values.Padding = VerticalBoxSlot->GetPadding();
	}

	return Values;
}

void UBUITweenBPLibrary::RestoreInitialValues(UWidget* TargetWidget, const FBUITweenValues& InitialValues)
{
	if (!TargetWidget)
	{
		return;
	}
	InitialValues.RestoreToWidget(TargetWidget);
}
