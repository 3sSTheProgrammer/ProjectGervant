// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KvenActor.generated.h"

UCLASS()
class PROJECTGERVANT_API AKvenActor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AKvenActor();

	void DestroySelf();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
