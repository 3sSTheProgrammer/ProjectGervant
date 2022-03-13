// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "StoryTellerActor.h"

// Sets default values
AStoryTellerActor::AStoryTellerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AStoryTellerActor::BeginPlay()
{
	Super::BeginPlay();

	HUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AKillCountHUD>();
	
	LevelNameMap.Add(TEXT("UEDPIE_0_Level1"), 1);

	UWorld* TheWorld = GetWorld();
	FString CurrentLevel = TheWorld->GetMapName();
	switch (LevelNameMap[CurrentLevel])
	{
	case 1:
		FirstLevelScript();
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("unknown level"));
		break;
	}
}

// Called every frame
void AStoryTellerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//in perspective this should be a reaction on an event, not an every tick check
	//TODO: refactor this functionality to be a reaction on an event

	/*if (HUD != nullptr && HUD->GetKillsAmount() > 5)
	{
		UWorld* TheWorld = GetWorld();
		FString CurrentLevel = TheWorld->GetMapName();
		UE_LOG(LogTemp, Warning, TEXT("%s"), *CurrentLevel);
		if (CurrentLevel == "UEDPIE_0_Map0")
		{
			UGameplayStatics::OpenLevel(GetWorld(), "Map1");
		}
		else
		{
			UGameplayStatics::OpenLevel(GetWorld(), "Map0");
		}
		
		
	}*/

}

//TODO: guess this should be overriden in child classes
void AStoryTellerActor::FirstLevelScript()
{
	UE_LOG(LogTemp, Warning, TEXT("1 level"));


	FVector SpawnLocation{ 0 };
	SpawnLocation.Z = 500;

	SpawnLocation.Y = 300;

	//TSubclassOf<AEnemyActorParent> SpawnEnemy = UMonsterDrowner;
	TSubclassOf<AEnemyActorParent> SpawnEnemy = UMonsterEnemyFiend;

	GetWorld()->SpawnActor<AEnemyActorParent>(
		SpawnEnemy, SpawnLocation,
		FRotator::ZeroRotator);

	SpawnLocation.Z = 300;

	GetWorld()->SpawnActor<AEnemyActorParent>(
		SpawnEnemy, SpawnLocation,
		FRotator::ZeroRotator);
	//FTimerHandle Timer;
	/*GetWorldTimerManager().SetTimer(Timer, this,
		&AEnemyManagerActor::SpawnEnemy, 1.5f);*/
	
}

void AStoryTellerActor::SecondLevelScript()
{
	UE_LOG(LogTemp, Warning, TEXT("2 level"));
}

