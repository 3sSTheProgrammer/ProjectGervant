// Fill out your copyright notice in the Description page of Project Settings.



#include "EnemyActorParent.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectGervant/KillCountHUD.h"

// Sets default values
AEnemyActorParent::AEnemyActorParent()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

FString AEnemyActorParent::GetEnemyClass()
{
	return EnemyClass;
}

void AEnemyActorParent::SetIsAttacked(bool Status)
{
	IsAttacked = Status;
}

// Called when the game starts or when spawned
void AEnemyActorParent::BeginPlay()
{
	Super::BeginPlay();

	// find static mesh component
	TArray<UStaticMeshComponent*> StaticMeshComponents;
	GetComponents(StaticMeshComponents);

	if (StaticMeshComponents.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("NUMOFCOMPONENTS: %d"), StaticMeshComponents.Num());
		StaticMeshComponent = StaticMeshComponents[0];
		/*UMaterialInterface* Material = StaticMeshComponent->GetMaterial(0);
		if (Material != nullptr)
		{
				UE_LOG(LogTemp, Warning, TEXT("Hello"));
		}*/
		
		//StaticMeshComponent->SetRenderCustomDepth(true); 
		//StaticMeshComponent->SetCustomDepthStencilValue(155); //STENCIL_DAMAGING_OUTLINE
	//	// set up delegate for collisions with something else
	//	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActorParent::OnOverlapBegin);
	//	StaticMeshComponent->OnComponentEndOverlap.AddDynamic(this, &AEnemyActorParent::OnOverlapEnd);
	}

	// find player actor and save it for efficiency
	TArray<AActor*> PlayerActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "Player", PlayerActors);

	if (PlayerActors.Num() > 0)
	{
		//this->
		PlayerActor = (APlayerActor*)PlayerActors[0];
	}


}

// Called every frame
void AEnemyActorParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
	
	// receiving damage if attacked by BeamActor
	//if (IsAttacked)
	//{
	//	//this->
	//	ReceiveDamage(BeamActor->GetDamagePerSecond() * DeltaTime);
	//}

	//UE_LOG(LogTemp, Warning, TEXT("HEALTH: %f"), Health);
	
	
	
	// Moves with enemy specifics
	MovementManager(DeltaTime);
}

//// Function that describes behaviour when overlap starts
//void AEnemyActorParent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
//	AActor* OtherActor, UPrimitiveComponent* OtherComp,
//	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	// setting status to IsAttacked
//	if ((ABeamActor*)OtherActor == BeamActor)
//	{
//		IsAttacked = true;
//	}
//}
//
//// Function that describes behaviour when overlap ends
//void AEnemyActorParent::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
//	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
//	int32 OtherBodyIndex)
//{
//	// setting status to !IsAttacked
//	if ((ABeamActor*)OtherActor == BeamActor)
//	{
//		IsAttacked = false;
//	}
//}

// Applies damage to enemy
void AEnemyActorParent::ReceiveDamage(float DamageAmount)
{
	// Reduce health
	Health -= DamageAmount;

	StaticMeshComponent->SetMaterial(0, UDamagedMaterial);
	// if health is below zero adds kill to HUD and destroys self
	if (Health <= 0)
	{
		AKillCountHUD* Hud = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AKillCountHUD>();
		if (Hud != nullptr)
		{
			Hud->AddKill(EnemyClass);
		}
		Destroy();
	}
}

void AEnemyActorParent::ReceiveHealing(float HealAmount)
{
	StaticMeshComponent->SetMaterial(0, UDefaultMaterial);
	Health = FMath::Clamp(Health + HealAmount, 0.f, MaxHealth);
}

//// Finds beam actor by tag that is afterwards stored in BeamActor field
//void AEnemyActorParent::FindBeamActor(FName Tag)
//{
//	TArray<AActor*> AnotherActors;
//UGameplayStatics::GetAllActorsWithTag(
//	GetWorld(), Tag, AnotherActors);
//	
//	if (AnotherActors.Num() > 0)
//	{
//		//this->
//		BeamActor = (ABeamActor*)AnotherActors[0];
//	}
//}

void AEnemyActorParent::MoveToPoint(FVector Point, float Time)
{
	FVector CurrentLocation = GetActorLocation();
	
	// math stuff
	float Angle = FGenericPlatformMath::Atan2(CurrentLocation.Y - Point.Y, CurrentLocation.Z - Point.Z);
	float MoveAmount = Time * MovementSpeed;

	CurrentLocation.Y -= MoveAmount * FGenericPlatformMath::Sin(Angle);
	CurrentLocation.Z -= MoveAmount * FGenericPlatformMath::Cos(Angle);

	float DistanceFromPoint = FGenericPlatformMath::Sqrt(FGenericPlatformMath::Pow(CurrentLocation.Y - Point.Y, 2)
		+ FGenericPlatformMath::Pow(CurrentLocation.Z - Point.Z, 2));
	
	// moving only if enemy is further than 10 units from destination point
	if (DistanceFromPoint >= 5)
	{
		SetActorLocation(CurrentLocation);
	}
}

void AEnemyActorParent::MovementManager(float Time)
{
	FVector CurrentLocation = GetActorLocation();

	// math stuff
	float Angle = FGenericPlatformMath::Atan2(CurrentLocation.Y, CurrentLocation.Z);
	float MoveAmount = Time * MovementSpeed;

	CurrentLocation.Y -= MoveAmount * FGenericPlatformMath::Sin(Angle);
	CurrentLocation.Z -= MoveAmount * FGenericPlatformMath::Cos(Angle);

	float DistanceFromCenter = FGenericPlatformMath::Sqrt(FGenericPlatformMath::Pow(CurrentLocation.Y, 2)
		+ FGenericPlatformMath::Pow(CurrentLocation.Z, 2));

	// if enemy reached player it destroys itself, otherwise continue moving
	// TODO: Add ReceiveDamage for the player
	if (DistanceFromCenter < 100)
	{
		Destroy();
	}
	else
	{
		SetActorLocation(CurrentLocation);
	}
}
