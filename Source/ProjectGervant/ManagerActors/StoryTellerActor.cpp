// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectGervant/EnemiesActors/EnemyActorParent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "StoryTellerActor.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectGervant/TutorialWidget.h"

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

	//HUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AKillCountHUD>();
	
	/*FirstLevelScript();
	return;*/

	LevelNameMap.Add(TEXT("UEDPIE_0_Level1"), 1);

	UWorld* TheWorld = GetWorld();
	FString CurrentLevel = TheWorld->GetMapName();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *CurrentLevel);

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
	TSubclassOf<AEnemyActorParent> SpawnEnemy = UMonsterEnemyGhoul;
	
	
		//UE_LOG(LogTemp, Warning, TEXT("Spawning enemy at %f %f %f"), SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z);
		//return;
	GetWorld()->SpawnActor<AEnemyActorParent>(SpawnEnemy, SpawnLocation, FRotator::ZeroRotator);
		/*GetWorld()->SpawnActor<AEnemyActorParent>(
			SpawnEnemy, SpawnLocation,
			FRotator::ZeroRotator);*/
	
	

	SpawnLocation.Y = -1200;

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

