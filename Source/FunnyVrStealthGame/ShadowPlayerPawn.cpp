// Fill out your copyright notice in the Description page of Project Settings.


#include "ShadowPlayerPawn.h"

// Sets default values
AShadowPlayerPawn::AShadowPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LeftShadowOrbMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftShadowOrb"));
	RightShadowOrbMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightShadowOrb"));

	ShadowRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ShadowRoot"));

	SetRootComponent(ShadowRoot);

}

void AShadowPlayerPawn::UpdateControllerPosition(FVector RightController, FVector LeftController, FVector HMD)
{
	
}

// Called when the game starts or when spawned
void AShadowPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShadowPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShadowPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

