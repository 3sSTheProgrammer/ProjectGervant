// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamActor.h"

// Sets default values
ABeamActor::ABeamActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABeamActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABeamActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentRotationVelocity.Roll != 0)
	{
		FRotator CurrentRotation = GetActorRotation();
		//CurrentRotation.Roll += CurrentRotationVelocity.Roll * RotationVelocityPerSecond * DeltaTime;
		CurrentRotation.Roll -= CurrentRotationVelocity.Roll * RotationVelocityPerSecond * DeltaTime;
		CurrentRotation.Roll = FMath::Clamp(CurrentRotation.Roll, -85.f, 85.f);
		SetActorRotation(CurrentRotation);
		CurrentRotationVelocity = FRotator(0);
	}
}

void ABeamActor::Rotate(float moveScale)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s rotating"), *GetName());
	CurrentRotationVelocity.Roll = moveScale;
}

float ABeamActor::GetDamagePerSecond()
{
	return DamagePerSecond;
}