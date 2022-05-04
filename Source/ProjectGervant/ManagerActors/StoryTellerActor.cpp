// Fill out your copyright notice in the Description page of Project Settings.

#include "StoryTellerActor.h"
#include "ProjectGervant/EnemiesActors/EnemyActorParent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectGervant/TutorialWidget.h"
//#include "Kismet/KismetArrayLibrary.h"

// Sets default values
AStoryTellerActor::AStoryTellerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	for (SIZE_T i = 0; i < MaxEnemiesOnOneSide; ++i)
	{
		float ZCoord = MinZSpawnCoordinate + (MaxZSpawnCoordinate - MinZSpawnCoordinate) / (MaxEnemiesOnOneSide - 1) * i;
		//UE_LOG
		//SpawnPointZs.Add(100 + i * 300);
		SpawnPointZs.Add(ZCoord);
	}
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

	UWorld* TheWorld = GetWorld();
	FString CurrentLevel = TheWorld->GetMapName();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *CurrentLevel);

	switch (LevelNameMap[CurrentLevel])
	{
	case 1:
		FirstLevelScript();
		break;

	case 2:
		SecondLevelScript();
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
	
	/*TutorialWidget = CreateWidget<UTutorialWidget>(GetWorld(), UTutorialWidget::StaticClass());
	if (TutorialWidget == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("widget is null"));
	}
	TutorialWidget->AddToViewport();*/
	//TutorialWidget->ShowHint("gfg");
	//TArray<UUserWidget*> Widgets;
	//if (->GetClass() != nullptr)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Class is not null"));
	//	//UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), Widgets, TutorialWidget->GetClass());
	//}
	
	/*if (Widgets.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found %d Tutorial widgets"), Widgets.Num());
	}*/

	FVector SpawnLocation{ 0 };
	SpawnLocation.Z = 400;

	SpawnLocation.Y = 1200;
	
	//TSubclassOf<AEnemyActorParent> SpawnEnemy = UMonsterDrowner;
	TSubclassOf<AEnemyActorParent> SpawnEnemyType = UMonsterEnemyGhoul;
	SpawnEnemyGroup(SpawnEnemyType, SpawnEnemiesNumberTest, ScreenSideTest);
	
		//UE_LOG(LogTemp, Warning, TEXT("Spawning enemy at %f %f %f"), SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z);
		//return;
	//GetWorld()->SpawnActor<AEnemyActorParent>(SpawnEnemy, SpawnLocation, FRotator::ZeroRotator);
		/*GetWorld()->SpawnActor<AEnemyActorParent>(
			SpawnEnemy, SpawnLocation,
			FRotator::ZeroRotator);*/
	
	//SpawnEnemy(SpawnEnemyType, SpawnLocation);

	//SpawnLocation.Y = -1200;

	//SpawnEnemy(SpawnEnemyType, SpawnLocation);
	/*GetWorld()->SpawnActor<AEnemyActorParent>(
		SpawnEnemy, SpawnLocation,
		FRotator::ZeroRotator);*/
	


	//FTimerHandle Timer;
	/*GetWorldTimerManager().SetTimer(Timer, this,
		&AEnemyManagerActor::SpawnEnemy, 1.5f);*/
	
}

void AStoryTellerActor::SecondLevelScript()
{
	UE_LOG(LogTemp, Warning, TEXT("2 level"));
	TSubclassOf<AEnemyActorParent> SpawnEnemyType = UMonsterEnemyGhoul;
	SpawnEnemyGroup(SpawnEnemyType, SpawnEnemiesNumberTest, ScreenSideTest);
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

void AStoryTellerActor::SpawnEnemyGroup(TSubclassOf<AEnemyActorParent> EnemyType, SIZE_T NumberOfEnemies, SIZE_T SpawnSide)
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
		SIZE_T RemainEnemies = NumberOfEnemies;
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

