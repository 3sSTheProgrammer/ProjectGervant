// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectGervant/EnemiesActors/ProjectileActor.h"
#include "HumanEnemyActor.h"
#include "HumanEnemyArcher.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTGERVANT_API AHumanEnemyArcher : public AHumanEnemyActor
{
	GENERATED_BODY()
	

public:

	UPROPERTY(EditAnywhere, Category = Projectile)
		TSubclassOf<AProjectileActor> ProjectileActor;

protected:
	bool ReachedShootingPoint;

public:
	AHumanEnemyArcher();

protected:

	virtual void MovementManager(float Time) override;

	void ShootProjectile();

	void StartShootingTimer();
};
