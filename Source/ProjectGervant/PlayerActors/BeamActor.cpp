// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamActor.h"

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
			UE_LOG(LogTemp, Warning, TEXT("started overlap with %s"), *Class);
			OverlapingEnemies.Add(EnemyActor);


			//TODO: Refactor as a function 
			if (InteractiveEnemy != nullptr)
			{
				if (BeamType == InteractiveEnemy->GetEnemyClass())
				{
					InteractiveEnemy->SetIsAttacked(false);
				}
				else
				{
					InteractiveEnemy->SetIsHealed(false);
				}
				
			}
			InteractiveEnemy = FindClosestEnemy();
			if (InteractiveEnemy != nullptr)
			{
				if (BeamType == InteractiveEnemy->GetEnemyClass())
				{
					InteractiveEnemy->SetIsAttacked(true);
				}
				else
				{
					InteractiveEnemy->SetIsHealed(true);
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
			FString Class;
			Class = EnemyActor->GetEnemyClass();
			UE_LOG(LogTemp, Warning, TEXT("ended overlap with %s"), *Class);
			OverlapingEnemies.Remove(EnemyActor);
			
			//TODO: Refactor as a function 
			if (InteractiveEnemy != nullptr)
			{
				if (BeamType == InteractiveEnemy->GetEnemyClass())
				{
					InteractiveEnemy->SetIsAttacked(false);
				}
				else
				{
					InteractiveEnemy->SetIsHealed(false);
				}

			}
			InteractiveEnemy = FindClosestEnemy();
			if (InteractiveEnemy != nullptr)
			{
				if (BeamType == InteractiveEnemy->GetEnemyClass())
				{
					InteractiveEnemy->SetIsAttacked(true);
				}
				else
				{
					InteractiveEnemy->SetIsHealed(true);
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
		//CurrentRotation.Roll += CurrentRotationVelocity.Roll * RotationVelocityPerSecond * DeltaTime;
		CurrentRotation.Roll -= CurrentRotationVelocity.Roll * RotationVelocityPerSecond * DeltaTime;
		CurrentRotation.Roll = FMath::Clamp(CurrentRotation.Roll, -85.f, 85.f);
		SetActorRotation(CurrentRotation);
		CurrentRotationVelocity = FRotator(0);
	}

	if (InteractiveEnemy != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("TICK:Interacting with %s"), *InteractiveEnemy->GetName());
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
	//UE_LOG(LogTemp, Warning, TEXT("%s rotating"), *GetName());
	CurrentRotationVelocity.Roll = moveScale;
}

float ABeamActor::GetDamagePerSecond()
{
	return DamagePerSecond;
}

AEnemyActorParent* ABeamActor::FindClosestEnemy()
{
	//nemnogo govnokod((
	float MinDistance = 10000;
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
	//UE_LOG(LogTemp, Warning, TEXT("FINDCLOSESTENEMY: %f"), DistanceToEnemy);
	/*if (ClosestEnemy != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("FINDCLOSESTENEMY:closest enemy is %s"), *ClosestEnemy->GetName());
	}*/

	return ClosestEnemy;
}