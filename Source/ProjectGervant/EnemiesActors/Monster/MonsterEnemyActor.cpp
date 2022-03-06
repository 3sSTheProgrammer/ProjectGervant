// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterEnemyActor.h"

AMonsterEnemyActor::AMonsterEnemyActor() :
	AEnemyActorParent{}
{
	EnemyClass = "Monster";
}

void AMonsterEnemyActor::BeginPlay()
{
	Super::BeginPlay();

	AEnemyActorParent::FindBeamActor("MonsterBeam");
	
	AMonsterEnemyActor::DamageFromBeam = AMonsterEnemyActor::BeamActor->GetDamagePerSecond();

	//UE_LOG(LogTemp, Warning, TEXT("ya rodilsya! %s"), *this->EnemyClass);
}