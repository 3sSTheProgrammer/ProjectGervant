// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "ProjectGervant/PlayerActors/Signs/IgniActor.h"
//#include "ProjectGervant/UW_WitcherSignsInterface.h"
#include "ProjectGervant/PlayerActors/Signs/KvenActor.h"
#include "Sound/SoundCue.h"
#include "ProjectGervant/KillCountHUD.h"

#include "GameFramework/Actor.h"
#include "PlayerActor.generated.h"

UCLASS()
class PROJECTGERVANT_API APlayerActor : public AActor
{
	GENERATED_BODY()
	
protected:

	float Health;

	bool IsKvenActive;

public:

	

	//TODO: Add another sounds
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* KvenSpawnSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* KvenDestroyedSound;

	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "KvenActor"),
		Category = Actors)
		TSubclassOf<AKvenActor> KvenActorClass;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InvokeGameEnd();

public:
	// Sets default values for this actor's properties
	APlayerActor();

	void PlayHitSound();

	void ReceiveDamage(float DamageAmount);

	void TurnKvenOn();

	void UseIgni();

};
