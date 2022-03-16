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

void AShadowPlayerPawn::CalculateCollision(USphereComponent* collider, FVector DeltaMove, float DeltaTime)
{
	int i = 0;

	FVector ImpactForce = DeltaMove / DeltaTime;

	
	
	while (!DeltaMove.IsNearlyZero() && i < 5)
	{
		FHitResult Hit;
		collider->AddWorldOffset(DeltaMove, true, &Hit);
 
		
		DeltaMove -= DeltaMove * Hit.Time;

		if (Hit.bBlockingHit)
		{
			
			UPrimitiveComponent* PhysicsObject =  Cast<UPrimitiveComponent>( Hit.Actor->GetRootComponent());
			
			if(PhysicsObject && PhysicsObject->IsSimulatingPhysics())
			{
				UE_LOG(LogTemp, Log, TEXT("Collided With Physics Object"))
				PhysicsObject->SetAllPhysicsLinearVelocity(ImpactForce);
			}
			
			

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

	CalculateCollision(LeftOrbCollider, MoveLeft, DeltaTime);
	CalculateCollision(RightOrbCollider, MoveRight, DeltaTime);
}

// Called to bind functionality to input
void AShadowPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

