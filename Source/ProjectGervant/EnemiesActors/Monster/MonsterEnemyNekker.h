// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MonsterEnemyActor.h"
#include "MonsterEnemyNekker.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTGERVANT_API AMonsterEnemyNekker : public AMonsterEnemyActor
{
	GENERATED_BODY()
	

protected:

	FVector FirstPoint;
	FVector SecondPoint;
	FVector ThirdPoint;

	bool PassedFirstPoint;
	bool PassedSecondPoint;
	bool PassedThirdPoint;

public:
	AMonsterEnemyNekker();

protected:

	virtual void BeginPlay() override;

	virtual void MovementManager(float Time) override;
};
