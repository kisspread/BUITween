#pragma once

#include "CoreMinimal.h"
#include "BUITweenInstance.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "UTestPanel.generated.h"

class UTileView;
enum class EBUIEasingType : uint8;

UENUM(BlueprintType)
enum class ETweenType : uint8
{
    Scale UMETA(DisplayName = "Scale"),
    Opacity UMETA(DisplayName = "Opacity"),
    Rotation UMETA(DisplayName = "Rotation"),
    Translation UMETA(DisplayName = "Translation"),
    Color UMETA(DisplayName = "Color"),
    All UMETA(DisplayName = "All Properties")
};

UCLASS()
class  UTweenTestItem : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tween")
    EBUIEasingType EasingType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tween")
    ETweenType TweenType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tween")
    FString DisplayName;
};

/**
 * 
 */
UCLASS()
class BUITWEENBP_API UUTestPanel : public UUserWidget
{
    GENERATED_BODY()

    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

protected:
    // 
    void GenerateTestItems();

public:
    UPROPERTY(EditAnywhere, Category="UI | Tween")
    TSubclassOf<UUserWidget> ItemWidgetClass;
    
    UPROPERTY(BlueprintReadWrite, Category="UI | Tween", meta=(BindWidget))
    TObjectPtr<UTileView> TileView;

    UFUNCTION(BlueprintCallable, Category="UI | Tween")
    void PlayAllTweens();

    UFUNCTION(BlueprintCallable, Category="UI | Tween")
    void StopAllTweens();

    UFUNCTION(BlueprintCallable, Category="UI | Tween")
    void ResetAllTweens();
};

/**
 * 
 */
UCLASS()
class UTestItemWidget : public UUserWidget, public IUserObjectListEntry
{
    GENERATED_BODY()
    
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    
    virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

protected:
    void ApplyTweenAnimation(FBUITweenInstance* InTweenInstance);
    
public:

    UPROPERTY(BlueprintReadWrite, Category="Tween")
    EBUIEasingType EasingType;

    UPROPERTY(BlueprintReadWrite, Category="Tween")
    ETweenType TweenType;

    UPROPERTY(BlueprintReadWrite, Category="Tween")
    FString DisplayName;
    
    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    TObjectPtr<UWidget> TweenWidget;
    
    UFUNCTION(BlueprintCallable, Category="Tween")
    void Play();

    UFUNCTION(BlueprintCallable, Category="Tween")
    void Stop();

    UFUNCTION(BlueprintCallable, Category="Tween")
    void Reset();
};
