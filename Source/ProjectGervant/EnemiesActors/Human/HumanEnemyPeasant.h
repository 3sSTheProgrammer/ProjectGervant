// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "HumanEnemyActor.h"
#include "HumanEnemyPeasant.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTGERVANT_API AHumanEnemyPeasant : public AHumanEnemyActor
{
	GENERATED_BODY()
	
public:
	AHumanEnemyPeasant();

protected:

	virtual void MovementManager(float Time) override;

};
