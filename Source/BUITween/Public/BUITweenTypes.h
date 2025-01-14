#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "Components/SizeBox.h"
#include "Components/OverlaySlot.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/VerticalBoxSlot.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "BUITweenTypes.generated.h"

USTRUCT(BlueprintType)
struct BUITWEEN_API FBUITweenValues
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tween")
    FVector2D Translation = FVector2D::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tween")
    FVector2D Scale = FVector2D(1.f, 1.f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tween")
    float Opacity = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tween")
    FLinearColor Color = FLinearColor::White;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tween")
    float Rotation = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tween")
    FVector2D CanvasPosition = FVector2D::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tween")
    FMargin Padding = FMargin(0.0f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tween")
    ESlateVisibility Visibility = ESlateVisibility::Visible;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tween")
    float MaxDesiredHeight = 0.0f;
    
    
    // Helper function to restore widget to these values
    void RestoreToWidget(UWidget* TargetWidget) const
    {
        if (!TargetWidget)
        {
            return;
        }

        // Restore basic transform values
        FWidgetTransform Transform = TargetWidget->GetRenderTransform();
        Transform.Translation = Translation;
        Transform.Scale = Scale;
        Transform.Angle = Rotation;
        TargetWidget->SetRenderTransform(Transform);
        
        TargetWidget->SetRenderOpacity(Opacity);
        TargetWidget->SetVisibility(Visibility);

        // Restore color for different widget types
        if (UUserWidget* UW = Cast<UUserWidget>(TargetWidget))
        {
            UW->SetColorAndOpacity(Color);
        }
        else if (UImage* UI = Cast<UImage>(TargetWidget))
        {
            UI->SetColorAndOpacity(Color);
        }
        else if (UBorder* Border = Cast<UBorder>(TargetWidget))
        {
            Border->SetContentColorAndOpacity(Color);
        }

        // Restore canvas position
        if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(TargetWidget->Slot))
        {
            CanvasSlot->SetPosition(CanvasPosition);
        }

        // Restore max desired height
        if (USizeBox* SizeBox = Cast<USizeBox>(TargetWidget))
        {
            SizeBox->SetMaxDesiredHeight(MaxDesiredHeight);
        }

        // Restore padding for different slot types
        if (UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(TargetWidget->Slot))
        {
            OverlaySlot->SetPadding(Padding);
        }
        else if (UHorizontalBoxSlot* HorizontalBoxSlot = Cast<UHorizontalBoxSlot>(TargetWidget->Slot))
        {
            HorizontalBoxSlot->SetPadding(Padding);
        }
        else if (UVerticalBoxSlot* VerticalBoxSlot = Cast<UVerticalBoxSlot>(TargetWidget->Slot))
        {
            VerticalBoxSlot->SetPadding(Padding);
        }
    }

    

    // Helper functions to check if a value is different from the initial value
    bool HasTranslationChange(const FBUITweenValues& InitialValues) const { return Translation != InitialValues.Translation; }
    bool HasScaleChange(const FBUITweenValues& InitialValues) const { return Scale != InitialValues.Scale; }
    bool HasOpacityChange(const FBUITweenValues& InitialValues) const { return !FMath::IsNearlyEqual(Opacity, InitialValues.Opacity); }
    bool HasColorChange(const FBUITweenValues& InitialValues) const { return Color != InitialValues.Color; }
    bool HasRotationChange(const FBUITweenValues& InitialValues) const { return !FMath::IsNearlyEqual(Rotation, InitialValues.Rotation); }
    bool HasCanvasPositionChange(const FBUITweenValues& InitialValues) const { return CanvasPosition != InitialValues.CanvasPosition; }
    bool HasPaddingChange(const FBUITweenValues& InitialValues) const { return Padding != InitialValues.Padding; }
    bool HasVisibilityChange(const FBUITweenValues& InitialValues) const { return Visibility != InitialValues.Visibility; }
    bool HasMaxDesiredHeightChange(const FBUITweenValues& InitialValues) const { return !FMath::IsNearlyEqual(MaxDesiredHeight, InitialValues.MaxDesiredHeight); }
};