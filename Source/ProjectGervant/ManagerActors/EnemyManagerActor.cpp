// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectGervant/EnemiesActors/EnemyActorParent.h"
#include "EnemyManagerActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyManagerActor::AEnemyManagerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyManagerActor::BeginPlay()
{
	Super::BeginPlay();

	StartSpawnTimer();
}

// Called every frame
void AEnemyManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AEnemyManagerActor::SpawnEnemy()
{
	// generate random spawn location
	FVector SpawnLocation = GenerateSpawnLocation();
	/*SpawnLocation.SetComponentForAxis(EAxis::Y,
		FMath::RandRange(MinSpawnY, MaxSpawnY));
	SpawnLocation.SetComponentForAxis(EAxis::Z,
		FMath::RandRange(MinSpawnZ, MaxSpawnZ));*/

	TSubclassOf<AEnemyActorParent> SpawnEnemy;
	int EnemyNumber = FMath::RandRange(0, 3);
	switch (EnemyNumber)
	{
	case 0:
		SpawnEnemy = UMonsterEnemy1;
		break;

	case 1:
		SpawnEnemy = UMonsterEnemy2;
		break;
	
	case 2:
		SpawnEnemy = UHumanEnemy1;
		break;
	
	case 3:
		SpawnEnemy = UHumanEnemy2;
		break;

	default:
		SpawnEnemy = nullptr;
		break;
	}

	// spawn the enemy
	GetWorld()->SpawnActor<AEnemyActorParent>(
		SpawnEnemy, SpawnLocation,
		FRotator::ZeroRotator);

	StartSpawnTimer();
}

void AEnemyManagerActor::StartSpawnTimer()
{
	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this,
		&AEnemyManagerActor::SpawnEnemy, 1.5f);
}

FVector AEnemyManagerActor::GenerateSpawnLocation()
{
	FVector SpawnLocation{ 0 };
	float Angle = FMath::RandRange(-85.0f * (float)3.141592 / 180, 85.0f * (float)3.141592 / 180);

	SpawnLocation.SetComponentForAxis(EAxis::Y,
		FMath::Sin(Angle) * SpawnRange);
	SpawnLocation.SetComponentForAxis(EAxis::Z,
		FMath::Cos(Angle) * SpawnRange);

	//UE_LOG(LogTemp, Warning, TEXT("Spawn: %f %f %f"), SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z);
	//UE_LOG(LogTemp, Warning, TEXT("Angle: %f"), Angle);
	return SpawnLocation;
}

