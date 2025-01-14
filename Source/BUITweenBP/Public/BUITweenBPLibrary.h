#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BUITweenTypes.h"
#include "BUITween.h"
#include "BUITweenBPLibrary.generated.h"

UCLASS()
class BUITWEENBP_API UBUITweenBPLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    DECLARE_DYNAMIC_DELEGATE_OneParam(FOnAnimationCompleteWithOwner, UWidget* ,Owner);
    DECLARE_DYNAMIC_DELEGATE(FOnAnimationComplete);
 
    UFUNCTION(BlueprintCallable, Category = "UI|Tween", meta = (DisplayName = "Play UI Tween", DefaultToSelf="TargetWidget"))
    static UWidget* PlayTween(
        UWidget* TargetWidget,
        const FBUITweenValues& FromValues,   
        const FBUITweenValues& ToValues,
        float Duration = 0.3f,
        float Delay = 0.0f,
        bool bRestoreInitialValues = false,
        bool bPlayFromStart = false,
        EBUIEasingType EasingType = EBUIEasingType::InOutQuad

    );

    UFUNCTION(BlueprintCallable, Category = "UI|Tween", meta = (DisplayName = "Play UI Tween And Watch", DefaultToSelf="TargetWidget"))
    static UWidget* PlayTweenAndWatch(
        UWidget* TargetWidget,
        const FBUITweenValues& FromValues,   
        const FBUITweenValues& ToValues,
        FOnAnimationComplete OnComplete,
        float Duration = 0.3f,
        float Delay = 0.0f,
        bool bRestoreInitialValues = false,
        bool bPlayFromStart = false,
        EBUIEasingType EasingType = EBUIEasingType::InOutQuad
    );

    // Helper function to get initial values from widget
    UFUNCTION(BlueprintCallable, Category = "UI|Tween", meta = (DisplayName = "Get UI Initial Values", DefaultToSelf="TargetWidget"))
    static FBUITweenValues GetInitialValues(UWidget* TargetWidget);

    // Helper function to restore initial values
    UFUNCTION(BlueprintCallable, Category = "UI|Tween", meta = (DisplayName = "Restore UI Initial Values", DefaultToSelf="TargetWidget"))
    static void RestoreInitialValues(UWidget* TargetWidget, const FBUITweenValues& InitialValues);
    
};


