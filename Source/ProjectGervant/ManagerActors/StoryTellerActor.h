// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectGervant/UW_WitcherSignsInterface.h"
#include "ProjectGervant/EnemiesActors/EnemyActorParent.h"
#include "ProjectGervant/KillCountHUD.h"

#include "GameFramework/Actor.h"
#include "StoryTellerActor.generated.h"

UCLASS()
class PROJECTGERVANT_API AStoryTellerActor : public AActor
{
	GENERATED_BODY()
	
public:
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

protected:
	// Dynamic reference to the blueprint class
	TSubclassOf<class UUserWidget> GameInterfaceClass;

	// Internal reference to the blueprint for gameplay logic
	UPROPERTY(BlueprintReadWrite, Category = "UI")
		class UUW_WitcherSignsInterface* GameInterface;

private:
	AKillCountHUD* HUD;

	TMap<FString, int> LevelNameMap;

public:	
	// Sets default values for this actor's properties
	AStoryTellerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void FirstLevelScript();

	void SecondLevelScript();
};
