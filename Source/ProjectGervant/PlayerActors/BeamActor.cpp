// Fill out your copyright notice in the Description page of Project Settings.

#include "BeamActor.h"
//#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ProjectGervant/EnemiesActors/EnemyActorParent.h"


// Sets default values
ABeamActor::ABeamActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABeamActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (this->Tags.Contains("HumanBeam"))
	{
		BeamType = "Human";
	}
	else if (this->Tags.Contains("MonsterBeam"))
	{
		BeamType = "Monster";
	}

	// find static mesh component
	UStaticMeshComponent* StaticMeshComponent;
	TArray<UStaticMeshComponent*> StaticMeshComponents;
	GetComponents(StaticMeshComponents);

	if (StaticMeshComponents.Num() > 0)
	{
		StaticMeshComponent = StaticMeshComponents[0];

		// set up delegate for collisions with something else
		StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ABeamActor::OnOverlapBegin);
		StaticMeshComponent->OnComponentEndOverlap.AddDynamic(this, &ABeamActor::OnOverlapEnd);
	}
}

void ABeamActor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		AEnemyActorParent* EnemyActor = Cast<AEnemyActorParent>(OtherActor);
		if (EnemyActor != nullptr)
		{
			FString Class;
			Class = EnemyActor->GetEnemyClass();
			OverlapingEnemies.Add(EnemyActor);


			//TODO: Refactor as a function 
			if (InteractiveEnemy != nullptr)
			{
				if (BeamType == InteractiveEnemy->GetEnemyClass())
				{
					InteractiveEnemy->SetBeamInteractionStatus("Attack", false);
				}
				else
				{
					InteractiveEnemy->SetBeamInteractionStatus("Heal", false);
				}
				
			}
			InteractiveEnemy = FindClosestEnemy();
			if (InteractiveEnemy != nullptr)
			{
				if (BeamType == InteractiveEnemy->GetEnemyClass())
				{
					InteractiveEnemy->SetBeamInteractionStatus("Attack", true);
				}
				else
				{
					InteractiveEnemy->SetBeamInteractionStatus("Heal", true);
				}
			}

		}
	}
}

void ABeamActor::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherActor != nullptr)
	{
		AEnemyActorParent* EnemyActor = Cast<AEnemyActorParent>(OtherActor);
		if (EnemyActor != nullptr)
		{
			OverlapingEnemies.Remove(EnemyActor);
			
			if (InteractiveEnemy != nullptr)
			{
				if (BeamType == InteractiveEnemy->GetEnemyClass())
				{
					InteractiveEnemy->SetBeamInteractionStatus("Attack", false);
				}
				else
				{
					InteractiveEnemy->SetBeamInteractionStatus("Heal", false);
				}

			}
			InteractiveEnemy = FindClosestEnemy();
			if (InteractiveEnemy != nullptr)
			{
				if (BeamType == InteractiveEnemy->GetEnemyClass())
				{
					InteractiveEnemy->SetBeamInteractionStatus("Attack", true);
				}
				else
				{
					InteractiveEnemy->SetBeamInteractionStatus("Heal", true);
				}
			}
			
		}

		
	}
}

// Called every frame
void ABeamActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentRotationVelocity.Roll != 0)
	{
		FRotator CurrentRotation = GetActorRotation();
		CurrentRotation.Roll -= CurrentRotationVelocity.Roll * RotationVelocityPerSecond * DeltaTime;
		CurrentRotation.Roll = FMath::Clamp(CurrentRotation.Roll, -85.f, 85.f);
		SetActorRotation(CurrentRotation);
		CurrentRotationVelocity = FRotator(0);
	}

	if (InteractiveEnemy != nullptr)
	{
		if (InteractiveEnemy->GetEnemyClass() == BeamType)
		{
			InteractiveEnemy->ReceiveDamage(DamagePerSecond * DeltaTime);
		}
		else
		{
			InteractiveEnemy->ReceiveHealing(HealingEfficiency * DamagePerSecond * DeltaTime);
		}
	}
}

void ABeamActor::Rotate(float moveScale)
{
	CurrentRotationVelocity.Roll = moveScale;
}

float ABeamActor::GetDamagePerSecond()
{
	return DamagePerSecond;
}

AEnemyActorParent* ABeamActor::FindClosestEnemy()
{
	float MinDistance = MAX_FLT;
	AEnemyActorParent* ClosestEnemy{ nullptr };
	for (AEnemyActorParent* Enemy : OverlapingEnemies)
	{
		FVector EnemyLocation = Enemy->GetActorLocation();
		float DistanceToEnemy =  FGenericPlatformMath::Sqrt(FGenericPlatformMath::Pow(EnemyLocation.Y, 2)
			+ FGenericPlatformMath::Pow(EnemyLocation.Z, 2));

		if (DistanceToEnemy < MinDistance)
		{
			MinDistance = DistanceToEnemy;
			ClosestEnemy = Enemy;
		}
	}

	return ClosestEnemy;
}