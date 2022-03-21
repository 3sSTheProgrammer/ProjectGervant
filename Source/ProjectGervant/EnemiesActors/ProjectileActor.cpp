// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileActor.h"

AProjectileActor::AProjectileActor()
{
	MovementSpeed = 100;
	Damage = 10;
}

void AProjectileActor::Tick(float DeltaTime)
{
	//TODO: Mb add mechanic to destroy the projectile
	// 
	if (IsAarded)
	{
		Destroy();
	}
	else
	{
		MovementManager(DeltaTime);
	}
	
	//FVector CurrentLocation = GetActorLocation();

	//// calculating moving coordinates
	//float Angle = FGenericPlatformMath::Atan2(CurrentLocation.Y, CurrentLocation.Z);
	//float MoveAmount = DeltaTime * MovementSpeed;

	//CurrentLocation.Y -= MoveAmount * FGenericPlatformMath::Sin(Angle);
	//CurrentLocation.Z -= MoveAmount * FGenericPlatformMath::Cos(Angle);

	//// calculatig distance to destination point
	//float DistanceFromCenter = GetDistanceToPoint(FVector::ZeroVector);

	//// if enemy reached player it destroys itself, otherwise continue moving
	//if (DistanceFromCenter < 100)
	//{
	//	Destroy();
	//	PlayerActor->ReceiveDamage(Damage);
	//}
	//else
	//{
	//	SetActorLocation(CurrentLocation);
	//}
}