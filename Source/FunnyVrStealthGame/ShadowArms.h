// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShadowArms.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FUNNYVRSTEALTHGAME_API UShadowArms : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShadowArms();

	UPROPERTY(EditDefaultsOnly)
	float VerticalMultiplicationFactor = 1;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* LeftShadowOrb;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* LeftShadowOrbMesh;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* RightShadowOrbMesh;
	
	UPROPERTY(EditDefaultsOnly)
	float HorizontalMultiplicationFactor = 3;
	UFUNCTION(BlueprintCallable)
	FVector GetShadowArmLocation(FVector Controller, FVector HMD);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
