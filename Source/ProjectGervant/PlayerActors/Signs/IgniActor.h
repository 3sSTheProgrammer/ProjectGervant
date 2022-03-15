// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectGervant/EnemiesActors/EnemyActorParent.h"
//#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IgniActor.generated.h"

UCLASS()
class PROJECTGERVANT_API AIgniActor : public AActor
{
	GENERATED_BODY()
protected:
	// Static mesh component saved for efficiency
	UStaticMeshComponent* StaticMeshComponent;

	float GrowthPerSecond{ 14.f };

	FVector CurrentScale;
public:	
	// Sets default values for this actor's properties
	AIgniActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Function that describes behaviour when overlap starts
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
