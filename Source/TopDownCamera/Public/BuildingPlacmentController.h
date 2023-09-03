// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingPlacmentController.generated.h"

USTRUCT(BlueprintType)
struct FBuildingData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
    TSubclassOf<AActor> BuildingRefrence;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
    UStaticMesh* BuildingMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Visual")
    UTexture2D* BuildingTexture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Visual")
    FString BuildingName;
};

UCLASS()
class TOPDOWNCAMERA_API ABuildingPlacmentController : public AActor
{
	GENERATED_BODY()
	
public:	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buildings")
    TArray<FBuildingData> BuildingData;

    UPROPERTY(EditAnywhere)
    int CurrentBuildingIndex = -1;
	
protected:
	virtual void BeginPlay() override;
   void SnapToGround(AActor* SpawnedBuilding);

public:	
    ABuildingPlacmentController();

	virtual void Tick(float DeltaTime) override;

    void PlaceBuilding(FVector position);
    void CashBuildingIndex(int index);

};
	