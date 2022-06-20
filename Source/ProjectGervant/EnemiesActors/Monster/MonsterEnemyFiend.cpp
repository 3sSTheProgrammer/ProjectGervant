// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterEnemyFiend.h"
#include "ProjectGervant/PlayerActors/PlayerActor.h"

AMonsterEnemyFiend::AMonsterEnemyFiend()
{
	
	MaxHealth = 200;
	Health = MaxHealth;
	MovementSpeed = 200;
	Damage = 50;
}

void AMonsterEnemyFiend::BeginPlay()
{
	Super::BeginPlay();

	MiddlePoint.X = 0;
	MiddlePoint.Y = FMath::RandRange(-400, 400);
	MiddlePoint.Z = FMath::RandRange(300, 500);
	PassedMiddlePoint = false;

}

void AMonsterEnemyFiend::MovementManager(float Time)
{
	FVector CurrentLocation = GetActorLocation();
	float DistanceFromPoint = GetDistanceToPoint(FVector::ZeroVector);
	
		if (DistanceFromPoint < 100)
		{
			Destroy();
			PlayerActor->ReceiveDamage(Damage);
		}

	if (!PassedMiddlePoint)
	{
		MoveToPoint(MiddlePoint, Time);
		CurrentLocation = GetActorLocation();
		DistanceFromPoint = GetDistanceToPoint(MiddlePoint);
		if (DistanceFromPoint <= 20)
		{
			PassedMiddlePoint = true;
		}
	}
	else
	{
		FTimerHandle Timer;
		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, 
			&AMonsterEnemyFiend::MoveToPoint, FVector::ZeroVector, Time);
	GetWorldTimerManager().SetTimer(Timer, TimerDelegate, 3.f, false);
	}

}
