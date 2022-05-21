// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "ProjectGervant/UW_WitcherSignsInterface.h"
//#include "ProjectGervant/EnemiesActors/EnemyActorParent.h"
//#include "ProjectGervant/KillCountHUD.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StoryTellerActor.generated.h"

class AEnemyActorParent;
class USoundCue;
class UAudioComponent;

UCLASS()
class PROJECTGERVANT_API AStoryTellerActor : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = Parameters)
		float SpawnEnemiesNumberTest;

	UPROPERTY(EditAnywhere, Category = Parameters)
		float ScreenSideTest;
	
	UPROPERTY(EditAnywhere, Category = Parameters)
		float MinZSpawnCoordinate{ 100.f };

	UPROPERTY(EditAnywhere, Category = Parameters)
		float MaxZSpawnCoordinate{ 1000.f };
	//UTutorialWidget* TutorialWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* Level1BackgroundSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* Level2BackgroundSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* Level3BackgroundSound;

	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "HumanEnemy"),
		Category = Enemies)
		TSubclassOf<AEnemyActorParent> UHumanEnemyBrigand1;
	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "HumanEnemy"),
		Category = Enemies)
		TSubclassOf<AEnemyActorParent> UHumanEnemyBrigand2;
	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "HumanEnemy"),
		Category = Enemies)
		TSubclassOf<AEnemyActorParent> UHumanEnemyNilfSoldier;
	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "HumanEnemy"),
		Category = Enemies)
		TSubclassOf<AEnemyActorParent> UHumanEnemyRedanianSoldier;
	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "HumanEnemy"),
		Category = Enemies)
		TSubclassOf<AEnemyActorParent> UHumanEnemyNilfArcher;
	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "HumanEnemy"),
		Category = Enemies)
		TSubclassOf<AEnemyActorParent> UHumanEnemyRedanianArcher;
	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "HumanEnemy"),
		Category = Enemies)
		TSubclassOf<AEnemyActorParent> UHumanEnemyBrigandArcher;
	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "HumanEnemy"),
		Category = Enemies)
		TSubclassOf<AEnemyActorParent> UHumanEnemyPeasant;
	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "HumanEnemy"),
		Category = Enemies)
		TSubclassOf<AEnemyActorParent> UMonsterEnemyWerewolfHumanForm;

	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "MonsterEnemy"),
		Category = Enemies)
		//TSubclassOf<AEnemyActorParent> UMonsterEnemyDrowner;
		TSubclassOf<AEnemyActorParent> UMonsterEnemyDrowner;
	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "MonsterEnemy"),
		Category = Enemies)
		TSubclassOf<AEnemyActorParent> UMonsterEnemyGhoul;
	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "MonsterEnemy"),
		Category = Enemies)
		TSubclassOf<AEnemyActorParent> UMonsterEnemyNekker;
	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "MonsterEnemy"),
		Category = Enemies)
		TSubclassOf<AEnemyActorParent> UMonsterEnemyNightwraith;
	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "MonsterEnemy"),
		Category = Enemies)
		TSubclassOf<AEnemyActorParent> UMonsterEnemyNoonwraith;
	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "MonsterEnemy"),
		Category = Enemies)
		TSubclassOf<AEnemyActorParent> UMonsterEnemyFiend;
	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "MonsterEnemy"),
		Category = Enemies)
		TSubclassOf<AEnemyActorParent> UMonsterEnemyWerewolfWolfForm;



private:
	//AKillCountHUD* HUD;

	TMap<FString, int> LevelNameMap;

	SIZE_T MaxEnemiesOnOneSide{ 3 };

	int SpawnPointY = 1200;

	TArray<SIZE_T> SpawnPointZs;

	int EnemiesAmountOnLevel{ 0 };

	UAudioComponent* CurrentLevelBackgroundSound;
public:	
	// Sets default values for this actor's properties
	AStoryTellerActor();

	int GetAmountOfKillsNeeded() const;

	void StopBackgroundSound();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void FirstLevelScript();

	void SecondLevelScript();

	/**
	 * @brief Spawns a single enemy of EnemyType in specified coordinates
	 * @param EnemyType Type of spawning enemy
	 * @param SpawnPoint FVector with spawn coordinates
	*/
	void SpawnEnemy(TSubclassOf<AEnemyActorParent> EnemyType, FVector SpawnPoint);

	/**
	 * @brief Spawns a group of enemies
	 * @param EnemyType Type of spawning enemy
	 * @param NumberOfEnemies Number of spawning enemies 
	 * @param SpawnSide -1 - left, 1 - right, 0 - both
	*/
	void SpawnEnemyGroup(TSubclassOf<AEnemyActorParent> EnemyType, int NumberOfEnemies, int SpawnSide);

	TArray<FVector> GenerateSpawnPoints(SIZE_T NumberOfPoints, SIZE_T ScreenSide);

	void SetSpawnTimer(TSubclassOf<AEnemyActorParent> EnemyType, int NumberOfEnemies, int SpawnSide, float Delay);
};
