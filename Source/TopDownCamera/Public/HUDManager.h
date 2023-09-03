// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingPlacmentController.h"
#include "HUDManager.generated.h"


UCLASS()
class TOPDOWNCAMERA_API UHUDManager : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void OnCreateBuildingPressed();

	void OnPlacmentUIClosed();

	void InitializeBuildingPlacmentHUD(TArray<FBuildingData>& BuildingData);

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UOverlay* CreateButtonOverLay;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UOverlay* PlacmentUIOverlay;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UPlacmentUI* PlacmentUIPanel;
};
