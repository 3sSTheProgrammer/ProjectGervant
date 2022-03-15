// Fill out your copyright notice in the Description page of Project Settings.

//Refactor enemies classes to optimise used methods

#include "MonsterEnemyFiend.h"

AMonsterEnemyFiend::AMonsterEnemyFiend()
{
	UE_LOG(LogTemp, Warning, TEXT("I'm fiend"));
	
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
	UE_LOG(LogTemp, Warning, TEXT("MiddlePoint: %f %f"), MiddlePoint.Y, MiddlePoint.Z);

}

//void AMonsterEnemyFiend::Tick(float DeltaTime)
//{
//	UE_LOG(LogTemp, Warning, TEXT("I'm fiend"));
//	Super::Tick(DeltaTime);
//
//	if (IsAttacked)
//	{
//		this->ReceiveDamage(DamageFromBeam, DeltaTime);
//	}
//
//	//MoveToCenter(MovementSpeed * DeltaTime);
//	
//	MoveToPoint(FVector::ZeroVector, MovementSpeed * DeltaTime);
//}
//void AMonsterEnemyFiend::MoveToPoint(FVector Point, float MoveAmount)
//{
//}

void AMonsterEnemyFiend::MovementManager(float Time)
{

	//return;
	//UE_LOG(LogTemp, Warning, TEXT("I'm fiend"));
	FVector CurrentLocation = GetActorLocation();
	float DistanceFromPoint = FGenericPlatformMath::Sqrt(FGenericPlatformMath::Pow(CurrentLocation.Y, 2)
		+ FGenericPlatformMath::Pow(CurrentLocation.Z, 2));

		if (DistanceFromPoint < 100)
		{
			Destroy();
			PlayerActor->ReceiveDamage(Damage);
		}

	if (!PassedMiddlePoint)
	{
		MoveToPoint(MiddlePoint, Time);
		CurrentLocation = GetActorLocation();
		DistanceFromPoint = FGenericPlatformMath::Sqrt(FGenericPlatformMath::Pow(CurrentLocation.Y - MiddlePoint.Y, 2)
			+ FGenericPlatformMath::Pow(CurrentLocation.Z - MiddlePoint.Z, 2));
		if (DistanceFromPoint <= 20)
		{
			UE_LOG(LogTemp, Warning, TEXT("passed middle point"));
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
