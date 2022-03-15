// Fill out your copyright notice in the Description page of Project Settings.


#include "ShadowPlayerPawn.h"
#include "Components/SphereComponent.h"


// Sets default values
AShadowPlayerPawn::AShadowPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	LeftOrbCollider = CreateDefaultSubobject<USphereComponent>(TEXT("LeftOrbRoot"));
	RightOrbCollider = CreateDefaultSubobject<USphereComponent>(TEXT("RightOrbRoot"));


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

void AShadowPlayerPawn::CalculateCollision(USphereComponent* collider, FVector DeltaMove)
{
	

	int i = 0;
	
	while (!DeltaMove.IsNearlyZero() && i < 5)
	{
		FHitResult Hit;
		collider->AddWorldOffset(DeltaMove, true, &Hit);
		
		DeltaMove -= DeltaMove * Hit.Time;

		if (Hit.bBlockingHit)
		{

			
			UE_LOG(LogTemp, Log, TEXT("COll"))

			if(Hit.bStartPenetrating)
			{
				FVector DepenVector = Hit.Normal * Hit.PenetrationDepth;
				collider->AddWorldOffset(DepenVector, false);
			}
	
			DeltaMove -= FVector::DotProduct(DeltaMove, Hit.Normal) * Hit.Normal;
			collider->AddWorldOffset(DeltaMove, true, &Hit);
			i++;
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("non COLL"))
			break;
		}
	}
	
}

// Called every frame
void AShadowPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector LeftDifference = LeftShadowOrbTargetPosition - LeftOrbCollider->GetComponentLocation();
	FVector MoveLeft = LeftDifference.GetSafeNormal()* ShadowOrbSpeed * DeltaTime;
	MoveLeft = MoveLeft.GetClampedToMaxSize(LeftDifference.Size());


	FVector RightDiffrence = RightShadowOrbTargetPosition - RightOrbCollider->GetComponentLocation();
	FVector MoveRight = RightDiffrence.GetSafeNormal() * ShadowOrbSpeed * DeltaTime;
	MoveRight = MoveRight.GetClampedToMaxSize(RightDiffrence.Size());

	CalculateCollision(LeftOrbCollider, MoveLeft);
	CalculateCollision(RightOrbCollider, MoveRight);
}

// Called to bind functionality to input
void AShadowPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

