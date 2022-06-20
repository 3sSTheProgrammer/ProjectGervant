// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileActor.h"

AProjectileActor::AProjectileActor()
{
	MovementSpeed = 100;
	Damage = 10;
}

void AProjectileActor::Tick(float DeltaTime)
{
	if (IsAarded)
	{
		Destroy();
	}
	else
	{
		MovementManager(DeltaTime);
	}
}