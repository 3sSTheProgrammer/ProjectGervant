// Fill out your copyright notice in the Description page of Project Settings.

#include "IgniActor.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ProjectGervant/EnemiesActors/EnemyActorParent.h"

// Sets default values
AIgniActor::AIgniActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AIgniActor::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent = FindComponentByClass<USphereComponent>();

	if (SphereComponent != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("sphere is not null"));
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AIgniActor::OnOverlapBegin);
	}
}

void AIgniActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		AEnemyActorParent* EnemyActor = Cast<AEnemyActorParent>(OtherActor);
		if (EnemyActor != nullptr)
		{
			EnemyActor->SetKilledByIgni(true);
			EnemyActor->ReceiveDamage(500);
		}
	}
}

// Called every frame
void AIgniActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentScale = GetActorScale3D();
	float CurrentCollisionSphereSize = SphereComponent->GetScaledSphereRadius();
	if (CurrentCollisionSphereSize > MaximumCollisionSphereSize)
	{
		Destroy();
	}
	else
	{
		CurrentScale.Z += GrowthPerSecond * DeltaTime;
		CurrentScale.Y += GrowthPerSecond * DeltaTime;
		CurrentScale.X += GrowthPerSecond * DeltaTime;

		SetActorScale3D(CurrentScale);
	}
	

}

