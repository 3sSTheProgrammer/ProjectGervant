// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterEnemyNekker.h"

AMonsterEnemyNekker::AMonsterEnemyNekker()
{
	MaxHealth = 50;
	Health = MaxHealth;
	MovementSpeed = 200; 
	Damage = 5;
}

void AMonsterEnemyNekker::BeginPlay()
{

	Super::BeginPlay();

	FirstPoint.X = 0;
	FirstPoint.Y = FMath::RandRange(-400, 400);
	FirstPoint.Z = FMath::RandRange(300, 500);

	SecondPoint.X = 0;
	SecondPoint.Y = FMath::RandRange(-400, 400);
	SecondPoint.Z = FMath::RandRange(300, 500);

	ThirdPoint.X = 0;
	ThirdPoint.Y = FMath::RandRange(-400, 400);
	ThirdPoint.Z = FMath::RandRange(300, 500);

	PassedThirdPoint = false;
	PassedSecondPoint = false;
	PassedFirstPoint = false;
}

void AMonsterEnemyNekker::MovementManager(float Time)
{
	//UE_LOG(LogTemp, Warning, TEXT("0"));
	if (GetDistanceToPoint(FVector::ZeroVector) < 100)
	{
		PlayerActor->ReceiveDamage(Damage);
		Destroy();
	}

	if (PassedThirdPoint)
	{
		MoveToPoint(FVector::ZeroVector, Time);
	}
	else if (PassedSecondPoint)
	{
		if (GetDistanceToPoint(ThirdPoint) < 20) PassedThirdPoint = true;
		MoveToPoint(ThirdPoint, Time);
	}
	else if (PassedFirstPoint)
	{
		if (GetDistanceToPoint(SecondPoint) < 20) PassedSecondPoint = true;
		MoveToPoint(SecondPoint, Time);
	}
	else
	{
		if (GetDistanceToPoint(FirstPoint) < 20) PassedFirstPoint = true;
		MoveToPoint(FirstPoint, Time);
	}
		
}