// Fill out your copyright notice in the Description page of Project Settings.


#include "IgniActor.h"

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
	
	CurrentScale = GetActorScale3D();

	TArray<UStaticMeshComponent*> StaticMeshComponents;
	GetComponents(StaticMeshComponents);

	if (StaticMeshComponents.Num() > 0)
	{
		StaticMeshComponent = StaticMeshComponents[0];
		StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AIgniActor::OnOverlapBegin);
	}
}

void AIgniActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("IGNI:Began overlap with %s"), *OtherActor->GetName());
		AEnemyActorParent* EnemyActor = Cast<AEnemyActorParent>(OtherActor);
		if (EnemyActor != nullptr)
		{
			//UE_LOG(LogTemp, Warning, TEXT("IGNI: Damaging an enemy"));
			EnemyActor->SetKilledByIgni(true);
			EnemyActor->ReceiveDamage(500);
		}
	}
}

// Called every frame
void AIgniActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FVector CurrentScale = GetActorScale3D();
	
	if (CurrentScale.Z > GrowthPerSecond / 2)
	{
		Destroy();
	}
	else
	{
		CurrentScale.Z += GrowthPerSecond * DeltaTime;
		CurrentScale.Y += GrowthPerSecond * DeltaTime;
		SetActorScale3D(CurrentScale);
	}
	

}

