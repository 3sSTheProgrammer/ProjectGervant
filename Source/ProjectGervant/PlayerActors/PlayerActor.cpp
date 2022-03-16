// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "PlayerActor.h"

// Sets default values
APlayerActor::APlayerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
		
	Health = 100.f;
	IsKvenActive = false;
}

// Called when the game starts or when spawned
void APlayerActor::BeginPlay()
{
	Super::BeginPlay();

	UStaticMeshComponent* StaticMeshComponent;
	TArray<UStaticMeshComponent*> StaticMeshComponents;
	GetComponents(StaticMeshComponents);

	if (StaticMeshComponents.Num() > 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("NUMOFCOMPONENTS: %d"), StaticMeshComponents.Num());
		StaticMeshComponent = StaticMeshComponents[0];
		
		//StaticMeshComponent->SetRenderCustomDepth(true);
		//StaticMeshComponent->SetCustomDepthStencilValue(155); //STENCIL_DAMAGING_OUTLINE
	//	// set up delegate for collisions with something else
	//	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActorParent::OnOverlapBegin);
	//	StaticMeshComponent->OnComponentEndOverlap.AddDynamic(this, &AEnemyActorParent::OnOverlapEnd);
	}
}

// Called every frame
void APlayerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void APlayerActor::PlayHitSound()
{
	UGameplayStatics::PlaySound2D(this, HitSound);
	
	//UGameplayStatics::PlaySound2D(this, HitSound);
}

void APlayerActor::ReceiveDamage(float DamageAmount)
{
	
	if (IsKvenActive)
	{
		IsKvenActive = false;
		
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), KvenActorClass, FoundActors);
		if (FoundActors.Num() > 0)
		{
			FoundActors[0]->Destroy();
		}
			
		//TODO: Sound here
	}
	else
	{
		Health -= DamageAmount;
		//TODO: Sound here
	}
}

void APlayerActor::TurnKvenOn()
{
	FVector KvenSpawnLocation = FVector(-10.f, 0.f, 0.f);
	IsKvenActive = true; // 
	GetWorld()->SpawnActor<AKvenActor>(KvenActorClass,
		KvenSpawnLocation, FRotator::ZeroRotator);
	//TODO: Sound here
}
