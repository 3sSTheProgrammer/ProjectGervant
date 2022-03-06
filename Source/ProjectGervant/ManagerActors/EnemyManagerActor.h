// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectGervant/EnemiesActors/EnemyActorParent.h"

#include "GameFramework/Actor.h"
#include "EnemyManagerActor.generated.h"

UCLASS()
class PROJECTGERVANT_API AEnemyManagerActor : public AActor
{
	GENERATED_BODY()
	
private:
	const float SpawnRange{ 750 };

public:
	

	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "HumanEnemy"),
		Category = Enemies)
		TSubclassOf<AEnemyActorParent> UHumanEnemy1;
	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "HumanEnemy"),
		Category = Enemies)
		TSubclassOf<AEnemyActorParent> UHumanEnemy2;
	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "MonsterEnemy"),
		Category = Enemies)
		TSubclassOf<AEnemyActorParent> UMonsterEnemy1;
	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "MonsterEnemy"),
		Category = Enemies)
		TSubclassOf<AEnemyActorParent> UMonsterEnemy2;

public:	
	// Sets default values for this actor's properties
	AEnemyManagerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	FVector GenerateSpawnLocation();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnEnemy();

	void StartSpawnTimer();


};
