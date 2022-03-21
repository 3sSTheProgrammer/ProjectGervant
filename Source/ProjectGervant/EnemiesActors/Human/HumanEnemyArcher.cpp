// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanEnemyArcher.h"

AHumanEnemyArcher::AHumanEnemyArcher()
{
	MaxHealth = 100;
	Health = MaxHealth;
	MovementSpeed = 125;
	ReachedShootingPoint = false;
}


void AHumanEnemyArcher::MovementManager(float Time)
{
	if (!ReachedShootingPoint)
	{
		FVector CurrentLocation = GetActorLocation();

		// calculating moving coordinates
		float Angle = FGenericPlatformMath::Atan2(CurrentLocation.Y, CurrentLocation.Z);
		float MoveAmount = Time * MovementSpeed;

		CurrentLocation.Y -= MoveAmount * FGenericPlatformMath::Sin(Angle);
		CurrentLocation.Z -= MoveAmount * FGenericPlatformMath::Cos(Angle);

		// calculatig distance to destination point
		float DistanceFromCenter = GetDistanceToPoint(FVector::ZeroVector);

		// if reached shooting point shoot repeatedly, otherwise continue moving
		if (DistanceFromCenter < 500) // && !ReachedShootingPoint
		{
			ReachedShootingPoint = true;
			StartShootingTimer();
		}
		else
		{
			SetActorLocation(CurrentLocation);
		}
	}
	
}

void AHumanEnemyArcher::ShootProjectile()
{
	FVector SpawnLocation{ GetActorLocation() };
	GetWorld()->SpawnActor<AProjectileActor>(
		ProjectileActor, SpawnLocation,
		FRotator::ZeroRotator);

	StartShootingTimer();
}

void AHumanEnemyArcher::StartShootingTimer()
{
	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this,
		&AHumanEnemyArcher::ShootProjectile, 3.f);
}