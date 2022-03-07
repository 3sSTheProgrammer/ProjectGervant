// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "ProjectGervant/EnemiesActors/EnemyActorParent.h"
#include "MonsterEnemyActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTGERVANT_API AMonsterEnemyActor : public AEnemyActorParent
{
	GENERATED_BODY()

public:
	//FString EnemyClass{ "Monster" };

	AMonsterEnemyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//// Called every frame
	//virtual void Tick(float DeltaTime) override;

//protected:
//	virtual void MoveToPoint(FVector Point, float MoveAmount) override;
};
