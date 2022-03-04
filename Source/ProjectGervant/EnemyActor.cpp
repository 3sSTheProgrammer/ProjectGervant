// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	
	
	/*FVector Origin;
	FVector BoxExtent;
	GetActorBounds(true, Origin, BoxExtent);
	HalfCollisionHeight = BoxExtent.Z;*/

	// find static mesh component
	UStaticMeshComponent* StaticMeshComponent;
	TArray<UStaticMeshComponent*> StaticMeshComponents;
	GetComponents(StaticMeshComponents);

	// make sure we found the static mesh
	if (StaticMeshComponents.Num() > 0)
	{
		// the mesh we want is at location 0 because there's only 1 mesh
		StaticMeshComponent = StaticMeshComponents[0];

		// set up delegate for collisions with something else
		//StaticMeshComponent->bGenerateOverlapEvents = true;
		StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnOverlapBegin);
		StaticMeshComponent->OnComponentEndOverlap.AddDynamic(this, &AEnemyActor::OnOverlapEnd);
	}

	
	/*TArray<AActor*> AnotherActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), Tag, AnotherActors);*/
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//TODO move DPS to beam constants and add a getter 
	float DPS = 100; 

	ReceiveDamage(DPS, DeltaTime);
}

void AEnemyActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	//TODO refactor project so that enemyactor class has children monster 
	//and human which have own children as HumanEnemy1 etc. enemyactor should have a 
	//property "EnemyClass"
	if (((EnemyClass == "Monster") && (OtherActor->ActorHasTag("MonsterBeam")))
		|| ((EnemyClass == "Human") && (OtherActor->ActorHasTag("HumanBeam"))))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Overlap started"));
		IsAttacked = true;
	}
	
}

void AEnemyActor::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	
	if (((EnemyClass == "Monster") && (OtherActor->ActorHasTag("MonsterBeam")))
		|| ((EnemyClass == "Human") && (OtherActor->ActorHasTag("HumanBeam"))))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Overlap ended"));
		IsAttacked = false;
	}
}

void AEnemyActor::ReceiveDamage(float DPS, float time)
{
	if (IsAttacked)
	{
		Health -= DPS * time;
	}
	//UE_LOG(LogTemp, Warning, TEXT("Health is %f"), Health);
	if (Health <= 0)
	{
		Destroy();
	}
}
