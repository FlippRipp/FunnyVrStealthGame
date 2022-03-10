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

	FVector LocalLeftControllerPos = LeftController - HMD;
	FVector LocalRightControllerPos = RightController - HMD;
	
	LeftShadowOrbTargetPosition = FVector(HMD.X + LocalLeftControllerPos.X * HorizontalMultiplicationFactor,
							HMD.Y + LocalLeftControllerPos.Y * HorizontalMultiplicationFactor,
							HMD.Z + LocalLeftControllerPos.Z * VerticalMultiplicationFactor);
	
	RightShadowOrbTargetPosition = FVector(HMD.X + LocalRightControllerPos.X * HorizontalMultiplicationFactor,
							HMD.Y + LocalRightControllerPos.Y * HorizontalMultiplicationFactor,
							HMD.Z + LocalRightControllerPos.Z * VerticalMultiplicationFactor);
}

// Called when the game starts or when spawned
void AShadowPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShadowPlayerPawn::CalculateCollision(UStaticMeshComponent* collider, FVector DeltaMove)
{
	FHitResult Hit;
	collider->AddWorldOffset(DeltaMove, true, &Hit);

	while (Hit.bBlockingHit)
	{
		if(Hit.bStartPenetrating)
		{
			FVector DepenVector = Hit.Normal * Hit.PenetrationDepth;
			collider->AddWorldOffset(DepenVector, false);
		}

		DeltaMove -= FVector::DotProduct(DeltaMove, Hit.Normal) * Hit.Normal;
	}
	collider->AddWorldOffset(DeltaMove, true, &Hit);
}

// Called every frame
void AShadowPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector MoveLeft = (LeftShadowOrbTargetPosition - LeftShadowOrbMesh->GetComponentLocation()).GetSafeNormal()
	* ShadowOrbSpeed * DeltaTime;
	FVector MoveRight = (RightShadowOrbTargetPosition - RightShadowOrbMesh->GetComponentLocation()).GetSafeNormal()
	* ShadowOrbSpeed * DeltaTime;
	CalculateCollision(LeftShadowOrbMesh, MoveLeft);
}

// Called to bind functionality to input
void AShadowPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

