// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterEnemyWraith.h"

#include "Kismet/GameplayStatics.h"
#include "ProjectGervant/UW_WitcherSignsInterface.h"
#include "ProjectGervant/PlayerActors/PlayerActor.h"
#include "Sound/SoundCue.h"

AMonsterEnemyWraith::AMonsterEnemyWraith()
{
	MaxHealth = 200;
	Health = MaxHealth;
	MovementSpeed = 100;
	Damage = 20;
}

void AMonsterEnemyWraith::BeginPlay()
{
	Super::BeginPlay();

	UsedHiding = false;
}

void AMonsterEnemyWraith::MovementManager(float Time)
{
	if (GetDistanceToPoint(FVector::ZeroVector) < DistanceFromCenterDeath)
	{
		Destroy();
		PlayerActor->ReceiveDamage(Damage);
		UUW_WitcherSignsInterface* Interface = Cast<UUW_WitcherSignsInterface>(GameInterface);
		if (Interface != nullptr)
		{
			Interface->AddNotKilledEnemy(EnemyClass);
		}
	}

	if (!UsedHiding && Health <= MaxHealth / 2)
	{
		UsedHiding = true;
		SetActorEnableCollision(false);
		SetActorHiddenInGame(true);
		MovementSpeed = 0;
		GetWorld()->SpawnActor<AActor>(
				BurnedRemainsActor, GetActorLocation(),
				FRotator::ZeroRotator);
		UGameplayStatics::PlaySound2D(this, SmokeSound);
		
		FTimerHandle Timer;
		GetWorldTimerManager().SetTimer(Timer, this, &AMonsterEnemyWraith::Teleport, 2.f);
	}
	else
	{
		Super::MovementManager(Time);
	}
}

FVector AMonsterEnemyWraith::GenerateTeleportationPoint()
{
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