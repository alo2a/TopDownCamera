#include "Building.h"
#include "Components/BoxComponent.h"

ABuilding::ABuilding()
{
	PrimaryActorTick.bCanEverTick = true;

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	RootComponent = BuildingMesh;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	BoxComponent->SetGenerateOverlapEvents(true);

}

void ABuilding::OnBuildingSelection()
{
	if (BuildingDefaultMaterial == nullptr)
		return;

	BuildingDefaultMaterial->SetVectorParameterValue("BaseColor",SelectionColor);
}

void ABuilding::OnBuildingDeselection()
{
	if (BuildingDefaultMaterial == nullptr)
		return;

	BuildingDefaultMaterial->SetVectorParameterValue("BaseColor", DefaultColor);
}

void ABuilding::BeginPlay()
{
	Super::BeginPlay();
}

void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuilding::OnConstruction(const FTransform& Transform)
{
	if (BuildingMaterial)
	{
		BuildingDefaultMaterial = UMaterialInstanceDynamic::Create(BuildingMaterial, this);
		BuildingMesh->SetMaterial(0, BuildingDefaultMaterial);

		FName ColorParamName = "BaseColor";
		BuildingDefaultMaterial->GetVectorParameterValue(ColorParamName,DefaultColor);
	}
}

