// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerActor.generated.h"

class AEnemyActorParent;
class USoundCue;
class AKvenActor;
class UUW_WitcherSignsInterface;

UCLASS()
class PROJECTGERVANT_API APlayerActor : public AActor
{
	GENERATED_BODY()
	
protected:

	float Health;

	bool IsKvenActive;

	UUW_WitcherSignsInterface* GameInterface;

	TSubclassOf<class UUserWidget> GameInterfaceClass;

public:


	//TODO: Add another sounds
	// Sound when player is hit 
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* ReceivedDamageSound;

	// Sound when level is completed 
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* WinSound;

	// Sound when level is failed 
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* LoseSound;

	// Sound when player uses Kven
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* KvenSpawnSound;

	// Sound when Kven is destroyed
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* KvenDestroyedSound;

	// Sound when player uses Igni
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* IgniSpawnSound;

	// Sound when player uses Aard
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* AardSpawnSound;

	// Sound when player uses Aksii
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* AksiiSound;

	UPROPERTY(EditAnywhere,
		Category = Actors)
		TSubclassOf<AKvenActor> KvenActorClass;

	// TODO: hz pochemu ne rabotaet AIgniActor i AAardActor
	UPROPERTY(EditAnywhere,
		Category = Actors)
		TSubclassOf<AActor> IgniActorClass;

	UPROPERTY(EditAnywhere,
		Category = Actors)
		TSubclassOf<AActor> AardActorClass;
	
	UPROPERTY(EditAnywhere,
		Category = Parameters)
		float IgniCooldown;

	UPROPERTY(EditAnywhere,
		Category = Parameters)
		float AardCooldown;

	UPROPERTY(EditAnywhere,
		Category = Parameters)
		float KvenCooldown;

	UPROPERTY(EditAnywhere,
		Category = Parameters)
		float AksiiCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> GameOverWidgetClass;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InvokeGameEnd();

	void UnstopEnemies(TArray<AEnemyActorParent*> StoppedEnemies);

	void InitHUDWidget();
public:
	// Sets default values for this actor's properties
	APlayerActor();

	void ReceiveDamage(float DamageAmount);

	void UseKven();

	void UseIgni();

	void UseAksii();

	void UseAard();

	float GetIgniCooldown();

	float GetAardCooldown();

	float GetAksiiCooldown();

	float GetKvenCooldown();

	
	
};
