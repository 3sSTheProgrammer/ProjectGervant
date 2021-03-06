// Fill out your copyright notice in the Description page of Project Settings.

#include "HumanEnemyPeasant.h"
#include "ProjectGervant/PlayerActors/PlayerActor.h"


AHumanEnemyPeasant::AHumanEnemyPeasant()
{
	SetActorEnableCollision(false);
	MaxHealth = 100;
	Health = MaxHealth;
	MovementSpeed = 100;
	Damage = 100;
}

void AHumanEnemyPeasant::MovementManager(float Time)
{
	FVector CurrentLocation = GetActorLocation();

	// calculating moving coordinates
	float Angle = FGenericPlatformMath::Atan2(CurrentLocation.Y, CurrentLocation.Z);
	float MoveAmount = Time * MovementSpeed;

	CurrentLocation.Y -= MoveAmount * FGenericPlatformMath::Sin(Angle);
	CurrentLocation.Z -= MoveAmount * FGenericPlatformMath::Cos(Angle);

	// calculating distance to destination point
	float DistanceFromCenter = GetDistanceToPoint(FVector::ZeroVector);

	// if enemy reached player it destroys itself, otherwise continue moving
	if (DistanceFromCenter < 100)
	{
		Destroy();
		// Hitting twice in case player has kven
		PlayerActor->ReceiveDamage(Damage);
		PlayerActor->ReceiveDamage(Damage);
	}
	else
	{
		SetActorLocation(CurrentLocation);
	}
}