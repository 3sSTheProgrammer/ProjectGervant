// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerActor.h"
#include "ProjectGervant/PlayerActors/Signs/KvenActor.h"
#include "Sound/SoundCue.h"
#include "ProjectGervant/EnemiesActors/EnemyActorParent.h"
#include "ProjectGervant/PlayerActors/Signs/IgniActor.h"
#include "ProjectGervant/PlayerActors/Signs/AardActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerActor::APlayerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
		
	Health = 100.f;
	IsKvenActive = false;

	//static ConstructorHelpers::FClassFinder<UUserWidget> GameInterfaceUIBPClass(TEXT("/Game/ProjectGervant/Menus/Widgets/GameInterface"));

	//if (GameInterfaceUIBPClass.Class != nullptr)
	//{
	//	//UE_LOG(LogTemp, Warning, TEXT("widget class found"));
	//	GameInterfaceClass = GameInterfaceUIBPClass.Class;
	//}
}

// Called when the game starts or when spawned
void APlayerActor::BeginPlay()
{
	Super::BeginPlay();

	UStaticMeshComponent* StaticMeshComponent;
	TArray<UStaticMeshComponent*> StaticMeshComponents;
	GetComponents(StaticMeshComponents);

	if (StaticMeshComponents.Num() > 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("NUMOFCOMPONENTS: %d"), StaticMeshComponents.Num());
		StaticMeshComponent = StaticMeshComponents[0];
		
		//StaticMeshComponent->SetRenderCustomDepth(true);
		//StaticMeshComponent->SetCustomDepthStencilValue(155); //STENCIL_DAMAGING_OUTLINE
	//	// set up delegate for collisions with something else
	//	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActorParent::OnOverlapBegin);
	//	StaticMeshComponent->OnComponentEndOverlap.AddDynamic(this, &AEnemyActorParent::OnOverlapEnd);
	}

	//if (GameInterfaceClass != nullptr)
	//{
	//	GameInterface = CreateWidget<UUW_WitcherSignsInterface>(GetWorld(), GameInterfaceClass);
	//	if (GameInterface != nullptr)
	//	{
	//		GameInterface->AddToViewport();
	//		GameInterface->SetVisibility(ESlateVisibility::Hidden);
	//		//GameInterface->SetOwningPlayer(this);
	//	}
	//}
}

void APlayerActor::ReceiveDamage(float DamageAmount)
{
	
	if (IsKvenActive)
	{
		IsKvenActive = false;
		
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), KvenActorClass, FoundActors);
		if (FoundActors.Num() > 0)
		{
			FoundActors[0]->Destroy();
			UGameplayStatics::PlaySound2D(this, KvenDestroyedSound);
		}
	}
	else
	{
		Health -= DamageAmount;
		UGameplayStatics::PlaySound2D(this, ReceivedDamageSound);
		if (Health <= 0)
		{
			UGameplayStatics::PlaySound2D(this, LoseSound);
			InvokeGameEnd();
		}
	}
}

void APlayerActor::UseKven()
{
	if (!IsKvenActive)
	{
		FVector KvenSpawnLocation = FVector(-10.f, 0.f, 0.f);
		IsKvenActive = true; 
		GetWorld()->SpawnActor<AKvenActor>(KvenActorClass,
			KvenSpawnLocation, FRotator::ZeroRotator);
		UGameplayStatics::PlaySound2D(this, KvenSpawnSound);
	}
	
}

void APlayerActor::UseIgni()
{
	//UE_LOG(LogTemp, Warning, TEXT("Using Igni"));
	UGameplayStatics::PlaySound2D(this, IgniSpawnSound);
	GetWorld()->SpawnActor<AIgniActor>(
		IgniActorClass, FVector::ZeroVector,
		FRotator::ZeroRotator);
}

void APlayerActor::UnstopEnemies(TArray<AEnemyActorParent*> StoppedEnemies)
{
	for (AEnemyActorParent* Enemy : StoppedEnemies)
	{
		Enemy->SetIsStopped(false);
	}
}

void APlayerActor::UseAksii()
{
	//TODO: Add tag "Enemy" in EnemyActor Parent
	TArray<AActor*> EnemyActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "Enemy", EnemyActors);

	UGameplayStatics::PlaySound2D(this, AksiiSound);
	TArray<AEnemyActorParent*> StoppedEnemies;
	for (AActor* Actor : EnemyActors)
	{
		AEnemyActorParent* Enemy = Cast<AEnemyActorParent>(Actor);
		if (Enemy != nullptr)
		{
			if (Enemy->GetEnemyClass() == "Monster")
			{
				Enemy->SetIsStopped(true);
				StoppedEnemies.Add(Enemy);
			}
		}
	}

	FTimerHandle Timer;
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this,
		&APlayerActor::UnstopEnemies, StoppedEnemies);
	GetWorld()->GetTimerManager().SetTimer(Timer, TimerDelegate, 3.f, false);
	
}

void APlayerActor::UseAard()
{
	UGameplayStatics::PlaySound2D(this, AardSpawnSound);
	GetWorld()->SpawnActor<AAardActor>(
		AardActorClass, FVector::ZeroVector,
		FRotator::ZeroRotator);
}

//TODO: implement functionality
void APlayerActor::InvokeGameEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("Game over"));
}

float APlayerActor::GetIgniCooldown()
{
	return IgniCooldown;
}

float APlayerActor::GetAardCooldown()
{
	return AardCooldown;
}

float APlayerActor::GetAksiiCooldown()
{
	return AksiiCooldown;
}

float APlayerActor::GetKvenCooldown()
{
	return KvenCooldown;
}