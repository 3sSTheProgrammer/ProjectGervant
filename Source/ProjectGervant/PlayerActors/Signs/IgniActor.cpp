// Fill out your copyright notice in the Description page of Project Settings.
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ProjectGervant/EnemiesActors/EnemyActorParent.h"
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
	
	//StartCollisionSphereSize = SCollisionSphereSize;
	//CurrentScale = GetActorScale3D();

	SphereComponent = FindComponentByClass<USphereComponent>();

	//StaticMesh = FindComponentByClass<UStaticMeshComponent>();

	/*FVector Origin;
	FVector BoxExtent;
	float Radius;
	UKismetSystemLibrary::GetComponentBounds(StaticMesh, Origin, BoxExtent, Radius);*/

	if (SphereComponent != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("sphere is not null"));
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AIgniActor::OnOverlapBegin);
	}
	/*TArray<UStaticMeshComponent*> StaticMeshComponents;
	GetComponents(StaticMeshComponents);

	if (StaticMeshComponents.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Igni mesh components num %d"), StaticMeshComponents.Num());
		StaticMeshComponent = StaticMeshComponents[0];
		StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AIgniActor::OnOverlapBegin);
		StaticMeshComponent->BodyInstance.SetCollisionProfileName(FName(TEXT("OverlapAll")));
	}*/
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

	FVector CurrentScale = GetActorScale3D();
	//UE_LOG(LogTemp, Warning, TEXT("Scale % f"), CurrentScale.X); //, SphereComponent->GetUnscaledSphereRadius()
	//UE_LOG(LogTemp, Warning, TEXT("Mesh sphere radius %f"), Radius);
	//UE_LOG(LogTemp, Warning, TEXT("Collision sphere radius %f"), SphereComponent->GetScaledSphereRadius());
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

