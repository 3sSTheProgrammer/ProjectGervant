// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterEnemyActor.h"
#include "MonsterEnemyFiend.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTGERVANT_API AMonsterEnemyFiend : public AMonsterEnemyActor
{
	GENERATED_BODY()
	
private:
	FVector MiddlePoint;
	bool PassedMiddlePoint;

public:
	AMonsterEnemyFiend();

protected:
	virtual void BeginPlay() override;

	virtual void MovementManager(float Time) override;

};
