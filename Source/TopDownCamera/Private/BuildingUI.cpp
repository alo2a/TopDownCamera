// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingUI.h"
#include "UMG/Public/Components/TextBlock.h"
#include "UMG/Public/Components/Image.h"
#include "Styling/SlateBrush.h"
#include "TopDownCameraPawn.h"
#include "BuildingPlacmentController.h"
#include "UMG/Public/Components/Button.h"
#include "Styling/SlateTypes.h"

void UBuildingUI::InitailizeBuildingUI(UTexture2D* Sprite, FString Name, int Indexs)
{
	if (BuildingImage != nullptr)
	{
		BuildingImage->SetBrushFromTexture(Sprite);
	}

	if (BuildingName != nullptr)
	{
		BuildingName->SetText(FText::FromString(Name));
	}
	BuildingIndex = Indexs;
}

void UBuildingUI::OnPlacmentBuildingPressed()
{
	if (GetOwningPlayer() == nullptr || GetOwningPlayer()->GetPawn() == nullptr)
		return;

	ATopDownCameraPawn* OwnerPawn= Cast<ATopDownCameraPawn>(GetOwningPlayer()->GetPawn());
	if (OwnerPawn)
	{
		ABuildingPlacmentController* buildingplacmentController = OwnerPawn->GetBildingPlacmentManager();

		if (buildingplacmentController)
		{
			buildingplacmentController->CashBuildingIndex(BuildingIndex);
		}
	}
}
