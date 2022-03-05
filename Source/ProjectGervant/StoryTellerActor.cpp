// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "StoryTellerActor.h"

// Sets default values
AStoryTellerActor::AStoryTellerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStoryTellerActor::BeginPlay()
{
	Super::BeginPlay();
	
	HUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AKillCountHUD>();
	
}

// Called every frame
void AStoryTellerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//in perspective this should be a reaction on an event, not an every tick check
	//TODO: refactor this functionality to be a reaction on an event

	if (Hud != nullptr && HUD->GetKillsAmount() > 5)
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
	}
	}
}

