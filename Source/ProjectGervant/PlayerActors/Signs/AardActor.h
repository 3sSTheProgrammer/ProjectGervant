// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectGervant/EnemiesActors/EnemyActorParent.h"
//#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AardActor.generated.h"

UCLASS()
class PROJECTGERVANT_API AAardActor : public AActor
{
	GENERATED_BODY()
	
protected:
	UStaticMeshComponent* StaticMeshComponent;

	float GrowthPerSecond{ 20.f };

	FVector CurrentScale;

	//FTimerHandle AardTimer;
public:	
	// Sets default values for this actor's properties
	AAardActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Function that describes behaviour when overlap starts
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//void ImpactEnemy(AEnemyActorParent* Enemy, bool ReverseStatus);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
