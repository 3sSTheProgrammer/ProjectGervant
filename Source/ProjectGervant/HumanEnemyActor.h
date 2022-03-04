// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "EnemyActorParent.h"
#include "HumanEnemyActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTGERVANT_API AHumanEnemyActor : public AEnemyActorParent
{
	GENERATED_BODY()

public:
	//FString EnemyClass{ "Human" };

	AHumanEnemyActor();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};