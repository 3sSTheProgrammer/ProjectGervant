// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanEnemyActor.h"

AHumanEnemyActor::AHumanEnemyActor() :
	AEnemyActorParent{}
{
	EnemyClass = "Human";
}

void AHumanEnemyActor::BeginPlay()
{
	Super::BeginPlay();

	AEnemyActorParent::FindBeamActor("HumanBeam");

	AHumanEnemyActor::DamageFromBeam = AHumanEnemyActor::BeamActor->GetDamagePerSecond();
}
