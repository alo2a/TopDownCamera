// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingPlacmentController.h"
#include "PlacmentUI.generated.h"

UCLASS()
class TOPDOWNCAMERA_API UPlacmentUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UHorizontalBox* BuildingPlacmentUI;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UBuildingUI>  BuildingButtonUI;
	
public:
	void InitailizePlacmentBuildingUI(TArray<FBuildingData>& BuildingData);
};
