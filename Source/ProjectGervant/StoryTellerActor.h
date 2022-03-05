// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KillCountHUD.h"
//#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StoryTellerActor.generated.h"

UCLASS()
class PROJECTGERVANT_API AStoryTellerActor : public AActor
{
	GENERATED_BODY()
	
private:
	AKillCountHUD* HUD;

public:	
	// Sets default values for this actor's properties
	AStoryTellerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
