// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterEnemyNekker.h"

AMonsterEnemyNekker::AMonsterEnemyNekker()
{
	MaxHealth = 50;
	Health = MaxHealth;
	MovementSpeed = 200; 
	Damage = 5;
}

void AMonsterEnemyNekker::BeginPlay()
{

}

void AMonsterEnemyNekker::MovementManager(float Time)
{

}