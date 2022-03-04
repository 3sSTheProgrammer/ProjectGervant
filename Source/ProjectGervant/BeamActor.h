// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BeamActor.generated.h"

UCLASS()
class PROJECTGERVANT_API ABeamActor : public AActor
{
	GENERATED_BODY()
	
private:
	const float RotationVelocityPerSecond{ 90.f };
	FRotator CurrentRotationVelocity{ 0 };
	float DamagePerSecond{ 100 };

public:	
	// Sets default values for this actor's properties
	ABeamActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Rotate(float moveScale);

	float GetDamagePerSecond();
};
