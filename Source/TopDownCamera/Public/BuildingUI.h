// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingUI.generated.h"

UCLASS()
class TOPDOWNCAMERA_API UBuildingUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* BuildingName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* BuildingImage;

	UPROPERTY(BlueprintReadWrite)
	int BuildingIndex;

public:
	void InitailizeBuildingUI(UTexture2D* Sprite,FString Name,int Index);

	UFUNCTION(BlueprintCallable)
	void OnPlacmentBuildingPressed();
};
