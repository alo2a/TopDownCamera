// Fill out your copyright notice in the Description page of Project Settings.


#include "PlacmentUI.h"
#include "Blueprint/UserWidget.h"
#include "BuildingUI.h"
#include "UMG/Public/Components/HorizontalBox.h"

void UPlacmentUI::InitailizePlacmentBuildingUI(TArray<FBuildingData>& BuildingData)
{
    if (BuildingButtonUI == nullptr || BuildingPlacmentUI == nullptr)
        return;
    for(int i = 0; i < BuildingData.Num(); i++)
    {
        UBuildingUI* Item = Cast<UBuildingUI>(CreateWidget(GetOwningPlayer()->GetWorld(), BuildingButtonUI));
        if (Item != nullptr)
        {
            Item->InitailizeBuildingUI(BuildingData[i].BuildingTexture, BuildingData[i].BuildingName,i);
            BuildingPlacmentUI->AddChild(Item);
        }
    }
}
