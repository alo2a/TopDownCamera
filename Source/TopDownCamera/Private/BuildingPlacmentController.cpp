// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingPlacmentController.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "Building.h"

ABuildingPlacmentController::ABuildingPlacmentController()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABuildingPlacmentController::BeginPlay()
{
	Super::BeginPlay();

}

void ABuildingPlacmentController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuildingPlacmentController::PlaceBuilding(FVector position)
{
	if (CurrentBuildingIndex != -1)
	{
		UWorld* const World = GetWorld();

		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			ABuilding* SpawnedBuilding = Cast<ABuilding>(World->SpawnActor<AActor>(BuildingData[CurrentBuildingIndex].BuildingRefrence, position, FRotator(0.0f, 0.0f, 0.0f), SpawnParams));

			if (SpawnedBuilding)
			{
				if (SpawnedBuilding->BuildingMesh && BuildingData[CurrentBuildingIndex].BuildingMesh)
				{
					SpawnedBuilding->BuildingMesh->SetStaticMesh(BuildingData[CurrentBuildingIndex].BuildingMesh);
				}

				SnapToGround(SpawnedBuilding);
			}

			CurrentBuildingIndex = -1;
		}
	}
}

void ABuildingPlacmentController::SnapToGround(AActor* SpawnedBuilding)
{
	FVector StartLocation = SpawnedBuilding->GetActorLocation() + FVector(0.0f, 0.0f, 500.0f);
	FVector EndLocation = StartLocation - FVector(0.0f, 0.0f, 1000.0f);

	FHitResult HitResult;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility))
	{
		SpawnedBuilding->SetActorLocation(HitResult.ImpactPoint);
	}
}

void ABuildingPlacmentController::CashBuildingIndex(int index)
{
	CurrentBuildingIndex = index;
}


