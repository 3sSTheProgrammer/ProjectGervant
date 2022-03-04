// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "PlayerActor.h"

// Sets default values
APlayerActor::APlayerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void APlayerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerActor::PlayHitSound()
{
	if (this != nullptr)
	{
		UGameplayStatics::PlaySound2D(this, HitSound);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WTF?????"));
	}
	//UGameplayStatics::PlaySound2D(this, HitSound);
}
