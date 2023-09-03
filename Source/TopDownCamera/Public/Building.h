// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building.generated.h"

UCLASS()
class TOPDOWNCAMERA_API ABuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	ABuilding();
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditAnywhere, Category="Visual")
	UMaterialInterface* BuildingMaterial;
	
	UPROPERTY(EditAnywhere, Category = "Components")
    UStaticMeshComponent* BuildingMesh;

	UPROPERTY(EditAnywhere, Category="Visual")
	FLinearColor SelectionColor;

	UFUNCTION()
	void OnBuildingSelection();
	UFUNCTION()
	void OnBuildingDeselection();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class  UBoxComponent* BoxComponent;
	
	UPROPERTY()
	UMaterialInstanceDynamic * BuildingDefaultMaterial;
	
	UPROPERTY()
	FLinearColor DefaultColor;
};
