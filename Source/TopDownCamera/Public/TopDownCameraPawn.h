// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TopDownCameraPawn.generated.h"

UCLASS()
class TOPDOWNCAMERA_API ATopDownCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	ATopDownCameraPawn();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void SetHUD(class UUserWidget* HudWidget);

	class ABuildingPlacmentController* GetBildingPlacmentManager();

protected:

	void MoveUp(float Val);
	void MoveRight(float Val);
	void ZoomCamera(float Val);
	void RotateCameraY(float val);
	void StartRotation();
	void EndRotation();
	void SelectBuilding();
	void PlaceBuilding();
	void CloseUI();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(EditDefaultsOnly, Category = "CameraMovementVariables")
	float CameraMovementSpeed = 1000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "CameraMovementVariables")
	float CameraRotationSpeed = 500.0f;

	UPROPERTY(EditDefaultsOnly, Category = "CameraMovementVariables")
	float CameraZoomingSpeed = 5000.0f;
	
	//value can't be less than default spring arm value
	UPROPERTY(EditDefaultsOnly, Category = "CameraMovementVariables")
	float CameraMaxZoom = 5000.0f;

	//value can't be more than default spring arm value
	UPROPERTY(EditDefaultsOnly, Category = "CameraMovementVariables")
	float CameraMinZoom=100.0f;

	UPROPERTY()
	class ABuildingPlacmentController* BuildingPlacmentController=nullptr;

	UPROPERTY()
	class UHUDManager* HUDManagerRefrence;

private:
	bool bCanRotate;
	FVector RotationPoint;
	class ABuilding* CurentSelected;
	FVector InitialCameraOffset;
};
