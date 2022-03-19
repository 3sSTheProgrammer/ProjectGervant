// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MonsterEnemyActor.h"
#include "MonsterEnemyWerewolf.generated.h"

//TODO: implement form change system
/**
 * 
 */
UCLASS()
class PROJECTGERVANT_API AMonsterEnemyWerewolf : public AMonsterEnemyActor
{
	GENERATED_BODY()

protected:

	// true - wolf form, false - human form
	bool IsInWolfForm;

	bool IsTransforming;

	// Regenerates health while in human form
	float RegenPerSecond;

public:

	UPROPERTY(EditAnywhere, Category = Materials)
		UTexture* UHumanFormTexture;

	UPROPERTY(EditAnywhere, Category = Materials)
		UTexture* UMonsterFormTexture;

public:
	AMonsterEnemyWerewolf();

protected:
	virtual void BeginPlay() override;

	virtual void MovementManager(float Time) override;

	void ChangeForm();
};
