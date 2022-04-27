// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//TODO: PODUMAT KAK SDELAT TAK, CHTOBY LUCH NE OSTANAVLIVALSYA PRI KONTAKTE SO STRELOY
#include "CoreMinimal.h"
#include "EnemyActorParent.h"
#include "ProjectileActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTGERVANT_API AProjectileActor : public AEnemyActorParent
{
	GENERATED_BODY()
	
public:
	AProjectileActor();

protected:
	virtual void Tick(float DeltaTime) override;
};
