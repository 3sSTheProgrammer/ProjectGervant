// Fill out your copyright notice in the Description page of Project Settings.
// TODO make the beam damage only one enemy at a time
#pragma once



#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BeamActor.generated.h"

class AEnemyActorParent;

UCLASS()
class PROJECTGERVANT_API ABeamActor : public AActor
{
	GENERATED_BODY()
	
private:
	const float RotationVelocityPerSecond{ 90.f };
	FRotator CurrentRotationVelocity{ 0 };
	float DamagePerSecond{ 100 };

	FString BeamType;
	
	TArray<AEnemyActorParent*> OverlapingEnemies;

	AEnemyActorParent* InteractiveEnemy;

	// Beams heals slower than damages with speed described by this coefficient
	float HealingEfficiency{ 0.5f };

public:	
	// Sets default values for this actor's properties
	ABeamActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Function that describes behaviour when overlap starts
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Function that describes behaviour when overlap ends
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	AEnemyActorParent* FindClosestEnemy();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Rotate(float moveScale);

	float GetDamagePerSecond();
};
