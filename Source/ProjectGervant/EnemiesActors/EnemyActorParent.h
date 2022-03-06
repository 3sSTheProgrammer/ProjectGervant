// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Containers/UnrealString.h"
#include "ProjectGervant/PlayerActors/BeamActor.h"
#include "ProjectGervant/PlayerActors/PlayerActor.h"

#include "GameFramework/Actor.h"
#include "EnemyActorParent.generated.h"

UCLASS()
class PROJECTGERVANT_API AEnemyActorParent : public AActor
{
	GENERATED_BODY()

protected:
	float Health{ 100 };
	bool IsAttacked{ false };
	ABeamActor* BeamActor;
	FString EnemyClass;
	float DamageFromBeam;
	
	float MovementSpeed{ 100 };

public:

	//potom ubrat'
	APlayerActor* PlayerActor;



	// Sets default values for this actor's properties
	AEnemyActorParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	void FindBeamActor(FName Tag);

	FString GetEnemyClass();


private:
	virtual void ReceiveDamage(float DPS, float time);

	virtual void MoveToCenter(float MoveAmount);
};
