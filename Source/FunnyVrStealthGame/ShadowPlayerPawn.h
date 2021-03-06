// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "ShadowPlayerPawn.generated.h"

class USphereComponent;

UCLASS()
class FUNNYVRSTEALTHGAME_API AShadowPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShadowPlayerPawn();
	
    UPROPERTY(EditDefaultsOnly)
    USceneComponent* ShadowRoot;

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* LeftOrbCollider;
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* RightOrbCollider;
		
	UPROPERTY(EditDefaultsOnly)
	float VerticalMultiplicationFactor = 1;
    UPROPERTY(EditDefaultsOnly)
    float HorizontalMultiplicationFactor = 3;
	UPROPERTY(EditDefaultsOnly)
	float ShadowOrbSpeed = 500;

	
    UFUNCTION(BlueprintCallable)
    void UpdateControllerPosition(FVector RightController, FVector LeftController, FVector HMD);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector LeftShadowOrbTargetPosition;
	FVector RightShadowOrbTargetPosition;

	void CalculateCollision(USphereComponent* collider, FVector Move, float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
