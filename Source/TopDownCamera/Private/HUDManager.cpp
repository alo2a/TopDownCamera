// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDManager.h"
#include "UMG/Public/Components/Overlay.h"
#include "PlacmentUI.h"


void UHUDManager::OnCreateBuildingPressed()
{
	if (CreateButtonOverLay)
	{
		CreateButtonOverLay->SetVisibility(ESlateVisibility::Hidden);
	}
	if (PlacmentUIOverlay)
	{
		PlacmentUIOverlay->SetVisibility(ESlateVisibility::Visible);
	}
	
}

void UHUDManager::OnPlacmentUIClosed()
{
	if (CreateButtonOverLay)
	{
		CreateButtonOverLay->SetVisibility(ESlateVisibility::Visible);
	}
	if (PlacmentUIOverlay)
	{
		PlacmentUIOverlay->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UHUDManager::InitializeBuildingPlacmentHUD(TArray<FBuildingData>& BuildingData)
{
	if (PlacmentUIPanel)
	{
		PlacmentUIPanel->InitailizePlacmentBuildingUI(BuildingData);
	}
}
