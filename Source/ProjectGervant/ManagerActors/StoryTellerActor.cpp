// Fill out your copyright notice in the Description page of Project Settings.

#include "StoryTellerActor.h"
#include "ProjectGervant/EnemiesActors/EnemyActorParent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectGervant/TutorialWidget.h"
//#include "ProjectGervant/PlayerActors/PlayerActor.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"


// Sets default values
AStoryTellerActor::AStoryTellerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	for (SIZE_T i = 0; i < MaxEnemiesOnOneSide; ++i)
	{
		float ZCoord = MinZSpawnCoordinate + (MaxZSpawnCoordinate - MinZSpawnCoordinate) / (MaxEnemiesOnOneSide - 1) * i;
		SpawnPointZs.Add(ZCoord);
	}
}

int AStoryTellerActor::GetAmountOfKillsNeeded() const
{
	return EnemiesAmountOnLevel;
}

// Called when the game starts or when spawned
void AStoryTellerActor::BeginPlay()
{
	Super::BeginPlay();

	//HUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AKillCountHUD>();
	
	/*FirstLevelScript();
	return;*/	

	LevelNameMap.Add(TEXT("UEDPIE_0_Level1"), 1);
	LevelNameMap.Add(TEXT("UEDPIE_0_Level2"), 2);
	LevelNameMap.Add(TEXT("UEDPIE_0_Level3"), 3);
	
	const UWorld* TheWorld = GetWorld();
	const FString CurrentLevel = TheWorld->GetMapName();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *CurrentLevel);

	switch (LevelNameMap[CurrentLevel])
	{
	case 1:
		FirstLevelScript();
		break;

	case 2:
		SecondLevelScript();
		break;

	case 3:
		ThirdLevelScript();
		break;
		
	default:
		UE_LOG(LogTemp, Warning, TEXT("unknown level"));
		break;
	}
}


//TODO: guess this should be overriden in child classes
void AStoryTellerActor::FirstLevelScript()
{
	UE_LOG(LogTemp, Warning, TEXT("1 level"));


	EnemiesAmountOnLevel = 25;
	CurrentLevelBackgroundSound = UGameplayStatics::SpawnSound2D(this, Level1BackgroundSound);
	//PlayerActor->SetBackgroundSound(BackgroundSound);

	float WaveDelay = 1.f;
	SetSpawnTimer(UHumanEnemyBrigand1, 1, -1, WaveDelay);
	WaveDelay += 8;
	SetSpawnTimer(UHumanEnemyBrigand1, 4, 0, WaveDelay);
	WaveDelay += 8;
	SetSpawnTimer(UHumanEnemyBrigand1, 14, 0, WaveDelay);
	WaveDelay += 10;
	SetSpawnTimer(UMonsterEnemyGhoul, 6, 0, WaveDelay);

}

void AStoryTellerActor::SecondLevelScript()
{
	UE_LOG(LogTemp, Warning, TEXT("2 level"));

	EnemiesAmountOnLevel = 76;
	CurrentLevelBackgroundSound = UGameplayStatics::SpawnSound2D(this, Level2BackgroundSound);

	TSubclassOf<AEnemyActorParent> SpawnEnemyType = UMonsterEnemyGhoul;
	//SpawnEnemyGroup(SpawnEnemyType, EnemiesAmountOnLevel, ScreenSideTest);
	float WaveDelay = 1.f;
	SetSpawnTimer(UMonsterEnemyNekker, 14, 0, WaveDelay);
	WaveDelay += 8;
	SetSpawnTimer(UHumanEnemyBrigand1, 6, -1, WaveDelay);
	SetSpawnTimer(UMonsterEnemyDrowner, 6, 1, WaveDelay);
	WaveDelay += 6;
	SetSpawnTimer(UHumanEnemyBrigand1, 6, 1, WaveDelay);
	SetSpawnTimer(UMonsterEnemyDrowner, 6, -1, WaveDelay);
	
	WaveDelay += 12;
	SetSpawnTimer(UHumanEnemyBrigand1, 6, 1, WaveDelay);
	SetSpawnTimer(UMonsterEnemyDrowner, 6, -1, WaveDelay);
	WaveDelay += 6;
	SetSpawnTimer(UHumanEnemyBrigand1, 6, -1, WaveDelay);
	SetSpawnTimer(UMonsterEnemyDrowner, 6, 1, WaveDelay);
	WaveDelay += 6;
	SetSpawnTimer(UMonsterEnemyNekker, 14, 0, WaveDelay);
	
}

void AStoryTellerActor::ThirdLevelScript()
{
	UE_LOG(LogTemp, Warning, TEXT("3 level"));

	EnemiesAmountOnLevel = 6;
	CurrentLevelBackgroundSound = UGameplayStatics::SpawnSound2D(this, Level3BackgroundSound);

	TSubclassOf<AEnemyActorParent> SpawnEnemyType = UMonsterEnemyGhoul;
	float WaveDelay = 1.f;
	SetSpawnTimer(UMonsterEnemyNightwraith, 6, 0, WaveDelay);
	
}

void AStoryTellerActor::SpawnEnemy(TSubclassOf<AEnemyActorParent> EnemyType, 
	FVector SpawnPoint)
{
	if (EnemyType == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tried to spawn unexisting enemy"));
		return;
	}
	else
	{
		FRotator SpawnRotation = FRotator::ZeroRotator;
		if (SpawnPoint.Y < 0)
		{
			SpawnRotation.Yaw = 180;
		}
		
		GetWorld()->SpawnActor<AEnemyActorParent>(
			EnemyType, SpawnPoint, SpawnRotation);
	}
}

void AStoryTellerActor::SpawnEnemyGroup(TSubclassOf<AEnemyActorParent> EnemyType, int NumberOfEnemies, int SpawnSide)
{
	if (NumberOfEnemies < 0) return;
	if (EnemyType == nullptr) return;
	if (SpawnSide != -1 && SpawnSide != 0 && SpawnSide != 1) return;

	if (SpawnSide == 0)
	{
		SpawnEnemyGroup(EnemyType, NumberOfEnemies / 2, -1);
		SpawnEnemyGroup(EnemyType, NumberOfEnemies - NumberOfEnemies / 2, 1);
		return;
	}
	if (NumberOfEnemies > MaxEnemiesOnOneSide)
	{
		int RemainEnemies = NumberOfEnemies;
		//while (RemainEnemies > MaxEnemiesOnOneSide)
		//{
		//	//TODO: implement timer here
		//	SpawnEnemyGroup(EnemyType, MaxEnemiesOnOneSide, SpawnSide);
		//	RemainEnemies -= MaxEnemiesOnOneSide;
		//}
		//if (RemainEnemies > 0)
		//{
		//	SpawnEnemyGroup(EnemyType, RemainEnemies, SpawnSide);
		//}
		if (RemainEnemies > 0)
		{
			SpawnEnemyGroup(EnemyType, MaxEnemiesOnOneSide, SpawnSide);
			RemainEnemies -= MaxEnemiesOnOneSide;
			
			FTimerHandle TimerHandle;
			FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this,
				&AStoryTellerActor::SpawnEnemyGroup, EnemyType, RemainEnemies, SpawnSide);
			GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 4.f, false);
		}
		
	}
	else
	{
		TArray<FVector> SpawnPoints = GenerateSpawnPoints(NumberOfEnemies, SpawnSide);
		for (SIZE_T i = 0; i < SpawnPoints.Num(); ++i)
		{
			SpawnEnemy(EnemyType, SpawnPoints[i]);
		}		
	}

}

TArray<FVector> AStoryTellerActor::GenerateSpawnPoints(SIZE_T NumberOfPoints, SIZE_T ScreenSide)
{
	TArray<FVector> Points;
	// Positions in which enemies will be spawned
	TArray<SIZE_T> Heights = SpawnPointZs;
	
	// If need less enemies than 4, remove random positions 
	if (NumberOfPoints < MaxEnemiesOnOneSide)
	{
		for (SIZE_T i = 0; i < MaxEnemiesOnOneSide - NumberOfPoints; ++i)
		{
			//UE_LOG(LogTemp, Warning, TEXT("i %d"), i);
			SIZE_T RandomIndex = FMath::RandRange(0, Heights.Num() - 1);
			Heights.RemoveAt(RandomIndex);
		}
		 
	}
	
	for (SIZE_T i = 0; i < Heights.Num(); ++i)
	{
		FVector Point = FVector(0, 0, Heights[i]);
		if (ScreenSide == -1) Point.Y = -SpawnPointY;
		else if (ScreenSide == 1) Point.Y = SpawnPointY;
		Points.Add(Point);
	}
	//UE_LOG(LogTemp, Warning, TEXT("Points generated %d"), Points.Num());
	return Points;
}

void AStoryTellerActor::SetSpawnTimer(TSubclassOf<AEnemyActorParent> EnemyType,
	int NumberOfEnemies, int SpawnSide, float Delay)
{
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this,
		&AStoryTellerActor::SpawnEnemyGroup, EnemyType, NumberOfEnemies, SpawnSide);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, Delay, false);
}

void AStoryTellerActor::StopBackgroundSound()
{
	if (CurrentLevelBackgroundSound != nullptr)
	{
		CurrentLevelBackgroundSound->SetActive(false);
	}
	
}