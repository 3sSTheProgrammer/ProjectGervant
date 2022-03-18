// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterEnemyWraith.h"

AMonsterEnemyWraith::AMonsterEnemyWraith()
{
	MaxHealth = 200;
	Health = MaxHealth;
	MovementSpeed = 100;
	Damage = 20;

	//Status = "Moving to player";
}

void AMonsterEnemyWraith::BeginPlay()
{
	Super::BeginPlay();

	UsedHiding = false;
	//SetActorEnableCollision(false);
	//SetActorHiddenInGame(true);
}

void AMonsterEnemyWraith::MovementManager(float Time)
{
	if (GetDistanceToPoint(FVector::ZeroVector) < 100)
	{
		PlayerActor->ReceiveDamage(Damage);
		Destroy();
	}

	if (!UsedHiding && Health <= MaxHealth / 2)
	{
		UE_LOG(LogTemp, Warning, TEXT("Teleporting"));
		UsedHiding = true;
		SetActorEnableCollision(false);
		SetActorHiddenInGame(true);
		MovementSpeed = 0;

		FTimerHandle Timer;
		GetWorldTimerManager().SetTimer(Timer, this, &AMonsterEnemyWraith::Teleport, 2.f);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Health %d"), MaxHealth);
		Super::MovementManager(Time);
	}
		
	//	if (!UsedHiding && Health <= MaxHealth / 2)
	//{
	//	UsedHiding = true;
	//	FTimerHandle Timer;
	//	GetWorldTimerManager().SetTimer(Timer, this, AMonsterEnemyWraith::Teleport, 2.f);
	//	//MoveToPoint(GenerateTeleportationPoint(), Time);
	//}
	//else if (UsedHiding && !PassedTeleportationPoint)
	//{
	//	MoveToPoint(TeleportationPoint, Time);
	//	if (GetDistanceToPoint(TeleportationPoint) < 20)
	//	{
	//		PassedTeleportationPoint = true;
	//	}
	//}
	//else if (PassedTeleportationPoint)
	//{
	//	MoveToPoint(FVector::ZeroVector, Time);
	//}
		
	
}

FVector AMonsterEnemyWraith::GenerateTeleportationPoint()
{
	//TODO: implement
	float DistanceToCenter = GetDistanceToPoint(FVector::ZeroVector);
	float Angle = FMath::RandRange(-85.0f * (float)3.141592 / 180, 85.0f * (float)3.141592 / 180);
	FVector GeneratedPoint = FVector::ZeroVector;
	GeneratedPoint.Y = FMath::Sin(Angle) * DistanceToCenter;
	GeneratedPoint.Z = FMath::Cos(Angle) * DistanceToCenter;

	return GeneratedPoint;
}


void AMonsterEnemyWraith::Teleport()
{
	float DistanceToCenter = GetDistanceToPoint(FVector::ZeroVector);
	float Angle = FMath::RandRange(-85.0f * (float)3.141592 / 180, 85.0f * (float)3.141592 / 180);
	FVector GeneratedPoint = FVector::ZeroVector;
	GeneratedPoint.Y = FMath::Sin(Angle) * DistanceToCenter;
	GeneratedPoint.Z = FMath::Cos(Angle) * DistanceToCenter;

	SetActorLocation(GeneratedPoint);
	SetActorEnableCollision(true);
	SetActorHiddenInGame(false);
	MovementSpeed = 100;
}