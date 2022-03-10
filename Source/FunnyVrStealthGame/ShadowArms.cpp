// Fill out your copyright notice in the Description page of Project Settings.


#include "ShadowArms.h"

// Sets default values for this component's properties
UShadowArms::UShadowArms()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	LeftShadowOrbMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftShadowOrb"));
	RightShadowOrbMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightShadowOrb"));
	// ...
}


FVector UShadowArms::GetShadowArmLocation(FVector Controller, FVector HMD)
{
	FVector ControllerHMDDifference = Controller - HMD;

	return FVector(HMD.X + ControllerHMDDifference.X * HorizontalMultiplicationFactor,
                            HMD.Y + ControllerHMDDifference.Y * HorizontalMultiplicationFactor,
                            HMD.Z + ControllerHMDDifference.Z * VerticalMultiplicationFactor);

}

// Called when the game starts
void UShadowArms::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void UShadowArms::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

