// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownCameraPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Building.h"
#include "BuildingPlacmentController.h"
#include "Kismet/GameplayStatics.h"
#include "UMG/Public/Blueprint/UserWidget.h"
#include "HUDManager.h"

ATopDownCameraPawn::ATopDownCameraPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 1400;
	CameraBoom->SetRelativeRotation(FRotator(-50.0, 0.0, 0.0));
	CameraBoom->CameraLagSpeed = 5.0f;
	CameraBoom->CameraRotationLagSpeed = 5.0f;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bEnableCameraRotationLag = true;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom);
	TopDownCameraComponent->bUsePawnControlRotation = false;
}

void ATopDownCameraPawn::BeginPlay()
{
	Super::BeginPlay();

	if (GetController())
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if (PlayerController)
		{
			PlayerController->bShowMouseCursor = true;
		}
	}
	
	if (GetBildingPlacmentManager()) 
	{
		if (HUDManagerRefrence)
			HUDManagerRefrence->InitializeBuildingPlacmentHUD(GetBildingPlacmentManager()->BuildingData);
	}

}

void ATopDownCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATopDownCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveUp", this, &ATopDownCameraPawn::MoveUp);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATopDownCameraPawn::MoveRight);
	PlayerInputComponent->BindAxis("ZoomCamera", this, &ATopDownCameraPawn::ZoomCamera);
	PlayerInputComponent->BindAxis("Zoom", this, &ATopDownCameraPawn::ZoomCamera);
	PlayerInputComponent->BindAxis("RotateCameraY", this, &ATopDownCameraPawn::RotateCameraY);
	PlayerInputComponent->BindAction("StartRotation",IE_Pressed, this, &ATopDownCameraPawn::StartRotation);
	PlayerInputComponent->BindAction("StartRotation",IE_Released, this, &ATopDownCameraPawn::EndRotation);
	PlayerInputComponent->BindAction("SelectBuilding", IE_Pressed, this, &ATopDownCameraPawn::SelectBuilding);
	PlayerInputComponent->BindAction("PlaceBuilding", IE_Pressed, this, &ATopDownCameraPawn::PlaceBuilding);
	PlayerInputComponent->BindAction("CloseUI", IE_Pressed, this, &ATopDownCameraPawn::CloseUI);
}

void ATopDownCameraPawn::SetHUD(UUserWidget* HudWidget)
{
	if (HudWidget)
	{
		HUDManagerRefrence = Cast<UHUDManager>(HudWidget);
	}
}

void ATopDownCameraPawn::MoveUp(float Val)
{
	if (Val == 0.0f) { return; }

	FVector ForwardVector = GetActorRotation().Vector();
	ForwardVector.Z = 0.0f;
	ForwardVector.Normalize();

	FVector NewCameraLocation = GetActorLocation() + ForwardVector * Val * CameraMovementSpeed * GetWorld()->DeltaTimeSeconds;
	SetActorLocation(NewCameraLocation);
}

void ATopDownCameraPawn::MoveRight(float Val)
{
	if (Val == 0.0f) { return; }

	FVector RightVector = FRotationMatrix(GetActorRotation()).GetScaledAxis(EAxis::Y);
	RightVector.Z = 0.0f;
	RightVector.Normalize();

	FVector NewCameraLocation = GetActorLocation() + RightVector * Val * CameraMovementSpeed * GetWorld()->DeltaTimeSeconds;
	SetActorLocation(NewCameraLocation);
}

void ATopDownCameraPawn::ZoomCamera(float Val)
{
	if (Val == 0.0f) { return; }

	if (CameraBoom == nullptr) { return; }

	CameraBoom->TargetArmLength += Val * CameraZoomingSpeed * GetWorld()->DeltaTimeSeconds;
	CameraBoom->TargetArmLength = FMath::Clamp(CameraBoom->TargetArmLength, CameraMinZoom, CameraMaxZoom);

}

void ATopDownCameraPawn::RotateCameraY(float val)
{
	if (bCanRotate)
	{
		FRotator RotationInput(0.0f, val * CameraRotationSpeed * GetWorld()->DeltaTimeSeconds, 0.0f);
		FQuat RotationQuaternion(RotationInput);

		FRotator NewCameraRotation = GetActorRotation() + RotationInput;
		SetActorRotation(NewCameraRotation);
	}
}

void ATopDownCameraPawn::StartRotation()
{
	bCanRotate = true;
	FHitResult HitResult;
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	}
	RotationPoint = HitResult.Location;
}

void ATopDownCameraPawn::EndRotation()
{
	bCanRotate = false;
}

void ATopDownCameraPawn::SelectBuilding()
{
	FHitResult HitResult;
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	}
	if (HitResult.GetActor())
	{
		if (CurentSelected !=nullptr)
		{
			CurentSelected->OnBuildingDeselection();
		}

		 CurentSelected = Cast<ABuilding>(HitResult.GetActor());
		if (CurentSelected)
		{
			CurentSelected->OnBuildingSelection();
		}
	}
}

void ATopDownCameraPawn::PlaceBuilding()
{
	FHitResult HitResult;
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	}
	FVector ClickLocation = HitResult.Location;
	if (BuildingPlacmentController)
		BuildingPlacmentController->PlaceBuilding(ClickLocation);
}

void ATopDownCameraPawn::CloseUI()
{
	if (HUDManagerRefrence)
		HUDManagerRefrence->OnPlacmentUIClosed();
}

ABuildingPlacmentController* ATopDownCameraPawn::GetBildingPlacmentManager()
{
	if (BuildingPlacmentController)
		return BuildingPlacmentController;

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABuildingPlacmentController::StaticClass(), FoundActors);
	if (FoundActors.Num() > 0)
	{
		BuildingPlacmentController =Cast<ABuildingPlacmentController>(FoundActors[0]);
	}
	return BuildingPlacmentController;
}


