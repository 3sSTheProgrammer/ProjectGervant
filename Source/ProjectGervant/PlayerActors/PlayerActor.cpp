// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerActor.h"
#include "ProjectGervant/PlayerActors/Signs/KvenActor.h"
#include "Sound/SoundCue.h"
#include "ProjectGervant/EnemiesActors/EnemyActorParent.h"
#include "ProjectGervant/PlayerActors/Signs/IgniActor.h"
#include "ProjectGervant/PlayerActors/Signs/AardActor.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "ProjectGervant/UW_WitcherSignsInterface.h" 
#include "GameFramework/GameModeBase.h"
// Sets default values
APlayerActor::APlayerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
		
	Health = 100.f;
	IsKvenActive = false;

	static ConstructorHelpers::FClassFinder<UUserWidget> GameInterfaceUIBPClass(TEXT("/Game/ProjectGervant/Menus/GameInterface"));

	if (GameInterfaceUIBPClass.Class != nullptr)
	{
		GameInterfaceClass = GameInterfaceUIBPClass.Class;
	}
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
	}

	//TArray<UUserWidget*> Widgets;
	//UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), Widgets, GameInterfaceClass);
	//UE_LOG(LogTemp, Warning, TEXT("WIDGETS: %d"), Widgets.Num());
	//if (Widgets.Num() > 0)
	//{
	//	UUserWidget* Interface = Widgets[0];
	//	GameInterface = Cast<UUW_WitcherSignsInterface>(Interface);
	//	if (GameInterface != nullptr)
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("NASHEL WIDGET"));
	//	}
	//	else
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("NE NASHEL WIDGET"));
	//	}
	//	//GameInterface = Cast<UUW_WitcherSignsInterface>(GameInterfaceTemp);
	//	//UE_LOG(LogTemp, Warning, TEXT("NASHEL WIDGET"));
	//}
}

void APlayerActor::InitHUDWidget()
{
	TArray<UUserWidget*> Widgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), Widgets, GameInterfaceClass);
	//UE_LOG(LogTemp, Warning, TEXT("WIDGETS: %d"), Widgets.Num());
	if (Widgets.Num() > 0)
	{
		UUserWidget* Interface = Widgets[0];
		GameInterface = Cast<UUW_WitcherSignsInterface>(Interface);
		/*if (GameInterface != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("NASHEL WIDGET"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("NE NASHEL WIDGET"));
		}*/
		//GameInterface = Cast<UUW_WitcherSignsInterface>(GameInterfaceTemp);
		//UE_LOG(LogTemp, Warning, TEXT("NASHEL WIDGET"));
	}
}

void APlayerActor::ReceiveDamage(float DamageAmount)
{
	if (GameInterface == nullptr)
	{
		InitHUDWidget();
	}

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
		if (GameInterface != nullptr) GameInterface->SetHP(Health);
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

//.h
//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
//	TSubclassOf<UUserWidget> PauseMenuWidgetClass;
//.cpp
//if (PauseMenuWidgetClass != nullptr)
//{
//	UUserWidget* CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PauseMenuWidgetClass);
//	if (CurrentWidget != nullptr)
//	{
//		CurrentWidget->AddToViewport();
//		SetInputMode(FInputModeUIOnly());
//		bShowMouseCursor = true;
//		SetPause(true);
//	}
//}

//TODO: Move to story teller mb
//TODO: Save player controller as a field
void APlayerActor::InvokeGameEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("Game over"));
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController != nullptr) 
	{
		//PlayerController->SetPause(true);
		if (GameOverWidgetClass != nullptr)
		{
			UUserWidget* CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
			if (CurrentWidget != nullptr)
			{
				CurrentWidget->AddToViewport();
				PlayerController->SetInputMode(FInputModeUIOnly());
				PlayerController->bShowMouseCursor = true;
				PlayerController->SetPause(true);
			}
		}
	}
	
	//GetPlayerController
}

void APlayerActor::InvokeLevelCompleted()
{
	UE_LOG(LogTemp, Warning, TEXT("Level Completed"));
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController != nullptr)
	{
		if (LevelCompletedWidgetClass != nullptr)
		{
			UUserWidget* CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), LevelCompletedWidgetClass);
			if (CurrentWidget != nullptr)
			{
				CurrentWidget->AddToViewport();
				PlayerController->SetInputMode(FInputModeUIOnly());
				PlayerController->bShowMouseCursor = true;
				PlayerController->SetPause(true);
			}
		}
	}
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