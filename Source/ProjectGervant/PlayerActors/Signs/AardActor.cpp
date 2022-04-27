// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SphereComponent.h"
#include "ProjectGervant/EnemiesActors/EnemyActorParent.h"
#include "AardActor.h"

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

	//CurrentScale = GetActorScale3D();

	/*TArray<UStaticMeshComponent*> StaticMeshComponents;
	GetComponents(StaticMeshComponents);

	if (StaticMeshComponents.Num() > 0)
	{
		StaticMeshComponent = StaticMeshComponents[0];
		StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AAardActor::OnOverlapBegin);
	}*/

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
		//UE_LOG(LogTemp, Warning, TEXT("IGNI:Began overlap with %s"), *OtherActor->GetName());
		AEnemyActorParent* EnemyActor = Cast<AEnemyActorParent>(OtherActor);
		if (EnemyActor != nullptr)
		{
			//UE_LOG(LogTemp, Warning, TEXT("IGNI: Damaging an enemy"));
			EnemyActor->SetIsAarded(true);
			//ImpactEnemy(EnemyActor, true);
			FTimerHandle Timer;
			FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(EnemyActor,
				&AEnemyActorParent::SetIsAarded, false);
			GetWorld()->GetTimerManager().SetTimer(Timer, TimerDelegate, 1.f, false);
		}
		//GetWorld()->GetTimerManager().ListTimers();
	}
}

//void AAardActor::ImpactEnemy(AEnemyActorParent* Enemy, bool ReverseStatus)
//{
//		UE_LOG(LogTemp, Warning, TEXT("Impact %d"), ReverseStatus);
//		Enemy->SetIsStopped(ReverseStatus);
//		Enemy->SetIsAarded(ReverseStatus);
//}

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

