// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MonsterEnemyActor.h"
#include "MonsterEnemyWraith.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTGERVANT_API AMonsterEnemyWraith : public AMonsterEnemyActor
{
	GENERATED_BODY()

protected:
	bool UsedHiding;

	bool PassedTeleportationPoint{ false };

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	Category = "Sound")
	USoundCue* SmokeSound;

	UPROPERTY(EditAnywhere, Category = Materials)
	TSubclassOf<AActor> SmokeActor;
	
	FVector TeleportationPoint;
public:
	AMonsterEnemyWraith();

protected:
	virtual void BeginPlay() override;

	virtual void MovementManager(float Time) override;

	FVector GenerateTeleportationPoint();

	void Teleport();
};
