// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Sound/SoundCue.h"
#include "ProjectGervant/KillCountHUD.h"

#include "GameFramework/Actor.h"
#include "PlayerActor.generated.h"

UCLASS()
class PROJECTGERVANT_API APlayerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	//TODO Perenesti v actor personazha
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* HitSound;
	
	// Sets default values for this actor's properties
	APlayerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PlayHitSound();
};
