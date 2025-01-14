// Copy Right ZeroSoul

#include "UTestPanel.h"
#include "BUITween.h"
#include "Components/TileView.h"

void UUTestPanel::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (IsValid(ItemWidgetClass) && ItemWidgetClass->ImplementsInterface(UUserListEntry::StaticClass()))
	{
		// TileView->SetEntryWidgetClass(ItemWidgetClass);
	}
	GenerateTestItems();
}

void UUTestPanel::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUTestPanel::NativeDestruct()
{
	Super::NativeDestruct();
	if (TileView)
	{
		TileView->ClearListItems();
	}
}

void UUTestPanel::GenerateTestItems()
{
	if (!TileView)
	{
		return;
	}

	TileView->ClearListItems();

	// Get all easing types
	UEnum* EasingEnum = StaticEnum<EBUIEasingType>();
	UEnum* TweenEnum = StaticEnum<ETweenType>();
	// this last enum is MAX, no need
	for (int32 j = 0; j < TweenEnum->NumEnums() - 1; ++j)
	{
		if (TweenEnum->HasMetaData(TEXT("Hidden"), j))
		{
			continue;
		}
		// Create test items for each easing type
		for (int32 i = 0; i < EasingEnum->NumEnums() - 1; ++i)
		{
			if (EasingEnum->HasMetaData(TEXT("Hidden"), i))
			{
				continue;
			}

			int64 Value = EasingEnum->GetValueByIndex(i);
			FString EasingName = EasingEnum->GetDisplayNameTextByIndex(i).ToString();
			EBUIEasingType EasingType = static_cast<EBUIEasingType>(Value);

			// Create an item for each tween type


			ETweenType TweenType = static_cast<ETweenType>(TweenEnum->GetValueByIndex(j));
			FString TweenName = TweenEnum->GetDisplayNameTextByIndex(j).ToString();

			UTweenTestItem* TestItem = NewObject<UTweenTestItem>(this);
			TestItem->EasingType = EasingType;
			TestItem->TweenType = TweenType;
			TestItem->DisplayName = FString::Printf(TEXT("%s - %s"), *EasingName, *TweenName);

			TileView->AddItem(TestItem);
		}
	}
}

void UUTestPanel::PlayAllTweens()
{
	if (!TileView)
	{
		return;
	}

	for (UObject* Item : TileView->GetListItems())
	{
		if (UTestItemWidget* TestWidget = Cast<UTestItemWidget>(TileView->GetEntryWidgetFromItem(Item)))
		{
			TestWidget->Play();
		}
	}
}

void UUTestPanel::StopAllTweens()
{
	if (!TileView)
	{
		return;
	}

	for (UObject* Item : TileView->GetListItems())
	{
		if (UTestItemWidget* TestWidget = Cast<UTestItemWidget>(TileView->GetEntryWidgetFromItem(Item)))
		{
			TestWidget->Stop();
		}
	}
}

void UUTestPanel::ResetAllTweens()
{
	if (!TileView)
	{
		return;
	}

	for (UObject* Item : TileView->GetListItems())
	{
		if (UTestItemWidget* TestWidget = Cast<UTestItemWidget>(TileView->GetEntryWidgetFromItem(Item)))
		{
			TestWidget->Reset();
		}
	}
}

//////----------------------------------------------TestItemWidget------------------------------------------------------

void UTestItemWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UTestItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UTestItemWidget::NativeDestruct()
{
	Super::NativeDestruct();
	if (TweenWidget)
	{
		UBUITween::Clear(TweenWidget);
	}
}


void UTestItemWidget::ApplyTweenAnimation(FBUITweenInstance* TweenInstance)
{
	if (!TweenWidget || !TweenInstance)
	{
		return;
	}

	switch (TweenType)
	{
	case ETweenType::Scale:
		TweenInstance->FromColor(FLinearColor::Blue).ToColor(FLinearColor::Blue);
		TweenInstance->FromScale(FVector2D(1.0f, 1.0f)).ToScale(FVector2D(2.0f, 2.0f));
		break;

	case ETweenType::Opacity:
		TweenInstance->FromOpacity(1.0f).ToOpacity(0.0f);
		break;

	case ETweenType::Rotation:
		TweenInstance->FromColor(FLinearColor::Yellow).ToColor(FLinearColor::Yellow);
		TweenInstance->FromRotation(0.0f).ToRotation(360.0f);
		break;

	case ETweenType::Translation:
		TweenInstance->FromColor(FLinearColor::Red).ToColor(FLinearColor::Red);

		TweenInstance->FromTranslation(FVector2D(0.0f, 0.0f)).ToTranslation(FVector2D(100.0f, 0.0f));
		break;

	case ETweenType::Color:
		TweenInstance->FromColor(FLinearColor::Green).ToColor(FLinearColor::Yellow);
		break;

	case ETweenType::All:
		TweenInstance->FromScale(FVector2D(1.0f, 1.0f)).ToScale(FVector2D(2.0f, 2.0f))
		             .FromOpacity(1.0f).ToOpacity(0.5f)
		             .FromRotation(0.0f).ToRotation(360.0f)
		             .FromTranslation(FVector2D(0.0f, 0.0f)).ToTranslation(FVector2D(120.0f, -10.0f))
		             .FromColor(FLinearColor::White).ToColor(FLinearColor::Green);
		break;
	}

	TweenInstance->Easing(EasingType);
}

void UTestItemWidget::Play()
{
	if (!TweenWidget)
	{
		return;
	}

	if (UBUITween::GetIsTweening(TweenWidget))
	{
		Reset();
		Play();
	}
	else
	{
		auto TweenInstance = &UBUITween::Create(TweenWidget, 1.5f);
		ApplyTweenAnimation(TweenInstance);
		TweenInstance->OnComplete(FBUITweenSignature::CreateLambda([this](UWidget* Owner)
		{
			UBUITween::Create(TweenWidget, 0.5f)
			.ToReset()
			.OnComplete(FBUITweenSignature::CreateLambda([this](UWidget* Owner)
				{
					Play();
				}
			)).Begin();
		}));
		TweenInstance->Begin();
	}
}

void UTestItemWidget::Stop()
{
	Reset();
}

void UTestItemWidget::Reset()
{
	if (TweenWidget)
	{
		UBUITween::Create(TweenWidget).ToReset().Apply(1.0f);
		UBUITween::Clear(TweenWidget);
	}
}

void UTestItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	if (UTweenTestItem* TestItem = Cast<UTweenTestItem>(ListItemObject))
	{
		EasingType = TestItem->EasingType;
		TweenType = TestItem->TweenType;
		DisplayName = TestItem->DisplayName;
		Reset();
		Play();
	}
}
