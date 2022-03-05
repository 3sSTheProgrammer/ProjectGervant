// Fill out your copyright notice in the Description page of Project Settings.



#include "EnemyActorParent.h"
#include "Kismet/GameplayStatics.h"
#include "KillCountHUD.h"

// Sets default values
AEnemyActorParent::AEnemyActorParent()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyActorParent::BeginPlay()
{
	Super::BeginPlay();

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
		StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActorParent::OnOverlapBegin);
		StaticMeshComponent->OnComponentEndOverlap.AddDynamic(this, &AEnemyActorParent::OnOverlapEnd);
	}


	//POTOM UBRAT'
	TArray<AActor*> PlayerActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "Player", PlayerActors);

	if (PlayerActors.Num() > 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Player Actors found: %d"), PlayerActors.Num())
		this->PlayerActor = (APlayerActor*)PlayerActors[0];
	}


}

// Called every frame
void AEnemyActorParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsAttacked)
	{
		this->ReceiveDamage(DamageFromBeam, DeltaTime);
	}
	
	MoveToCenter(MovementSpeed * DeltaTime);
}

void AEnemyActorParent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//TODO refactor project so that enemyactor class has children monster 
	//and human which have own children as HumanEnemy1 etc. enemyactor should have a 
	//property "EnemyClass"
	if ((ABeamActor*)OtherActor == BeamActor)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Overlap started"));
		IsAttacked = true;
	}
}

void AEnemyActorParent::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if ((ABeamActor*)OtherActor == BeamActor)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Overlap ended"));
		IsAttacked = false;
	}
}

void AEnemyActorParent::ReceiveDamage(float DPS, float time)
{
	Health -= DPS * time;
	//UE_LOG(LogTemp, Warning, TEXT("Health is %f"), Health);
	if (Health <= 0)
	{
		AKillCountHUD* Hud = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AKillCountHUD>();
		if (Hud != nullptr)
		{
			FString Class = GetEnemyClass();
			UE_LOG(LogTemp, Warning, TEXT("dobavill kill %s"), *EnemyClass);
			Hud->AddKill(EnemyClass);
			
			/*if (Hud->GetKillsAmount() > 5)
			{
				UWorld* TheWorld = GetWorld();
				FString CurrentLevel = TheWorld->GetMapName();
				UE_LOG(LogTemp, Warning, TEXT("%s"), *CurrentLevel);
				if (CurrentLevel == "UEDPIE_0_Map0")
				{
					UGameplayStatics::OpenLevel(GetWorld(), "Map1");
				}
				else
				{
					UGameplayStatics::OpenLevel(GetWorld(), "Map0");
				}
			}*/
		}
		//{
		//	//EnemyClass = GetEnemyClass();
		//	UE_LOG(LogTemp, Warning, TEXT("ya %s"), *this->EnemyClass);
		//	if (EnemyClass == "Monster")
		//	{
		//		UE_LOG(LogTemp, Warning, TEXT("ubil monstra"));
		//		Hud->AddMonsterKill();
		//	}
		//	else if (EnemyClass == "Human")
		//	{
		//		UE_LOG(LogTemp, Warning, TEXT("ubil humana"));
		//		Hud->AddHumanKill();
		//	}
		//}
		
		Destroy();
	}
}

void AEnemyActorParent::FindBeamActor(FName Tag)
{
	TArray<AActor*> AnotherActors;
UGameplayStatics::GetAllActorsWithTag(
	GetWorld(), Tag, AnotherActors);
	
	if (AnotherActors.Num() > 0)
	{
		this->BeamActor = (ABeamActor*)AnotherActors[0];
	}
}

FString AEnemyActorParent::GetEnemyClass()
{
	return this->EnemyClass;
}

void AEnemyActorParent::MoveToCenter(float MoveAmount)
{
	FVector CurrentLocation = GetActorLocation();
	float Angle = FGenericPlatformMath::Atan2(CurrentLocation.Y, CurrentLocation.Z);
	
	CurrentLocation.Y -= MoveAmount * FGenericPlatformMath::Sin(Angle);
	CurrentLocation.Z -= MoveAmount * FGenericPlatformMath::Cos(Angle);

	float DistanceFromCenter = FGenericPlatformMath::Sqrt(FGenericPlatformMath::Pow(CurrentLocation.Y, 2) 
		+ FGenericPlatformMath::Pow(CurrentLocation.Z, 2));
	if (DistanceFromCenter < 100)
	{
		//UE_LOG(LogTemp, Warning, TEXT("niche ne slyshno(("));
		//UGameplayStatics::PlaySound2D(this, HitSound);
		PlayerActor->PlayHitSound();
		Destroy();
	}
	else
	{
		SetActorLocation(CurrentLocation);
	}
	
}