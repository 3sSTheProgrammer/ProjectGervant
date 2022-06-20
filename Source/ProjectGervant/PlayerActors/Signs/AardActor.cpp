// Fill out your copyright notice in the Description page of Project Settings.

#include "AardActor.h"
#include "Components/SphereComponent.h"
#include "ProjectGervant/EnemiesActors/EnemyActorParent.h"

// Sets default values
AAardActor::AAardActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAardActor::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent = FindComponentByClass<USphereComponent>();
	if (SphereComponent != nullptr)
	{
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AAardActor::OnOverlapBegin);
	}
}

void AAardActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		AEnemyActorParent* EnemyActor = Cast<AEnemyActorParent>(OtherActor);
		if (EnemyActor != nullptr)
		{
			EnemyActor->SetIsAarded(true);
			FTimerHandle Timer;
			FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(EnemyActor,
				&AEnemyActorParent::SetIsAarded, false);
			GetWorld()->GetTimerManager().SetTimer(Timer, TimerDelegate, 1.f, false);
		}
	}
}

// Called every frame
void AAardActor::Tick(float DeltaTime)
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

