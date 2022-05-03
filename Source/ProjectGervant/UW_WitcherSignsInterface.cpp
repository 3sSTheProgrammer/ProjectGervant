// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectGervant/UW_WitcherSignsInterface.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectGervant/PlayerActors/PlayerActor.h"
#include "ProjectGervant/PlayerActors/Signs/IgniActor.h"
#include "ProjectGervant/PlayerActors/Signs/AardActor.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

//UUW_WitcherSignsInterface::UUW_WitcherSignsInterface()
//{
//	PrimaryActorTick.bCanEverTick = true;
//}

void UUW_WitcherSignsInterface::NativeConstruct()
{
	UUserWidget::NativeConstruct();

	InitPlayerActor();
	
	MonsterKillCount = 0;
	HumanKillCount = 0;

	HighHPColor = FLinearColor(0.03, 0.54, 0.06, 1.0); //Green
	MediumHPColor = FLinearColor(0.96, 0.4, 0.0, 1.0); //Orange
	LowHPColor = FLinearColor(0.45, 0.0, 0.01, 1.0); //Red
	/*UWorld* World = GetWorld();
	WorldTimerManager = World->GetTimerManager();
	WorldTimerManager = GetWorld()->GetTimerManager();*/
}

void UUW_WitcherSignsInterface::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	UUserWidget::NativeTick(MyGeometry, DeltaTime);

	bool IsIgniTimerActive = GetWorld()->GetTimerManager().IsTimerActive(IgniTimer);

	if (IsIgniTimerActive)
	{
		IgniRemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(IgniTimer);
		if (IgniRemainingTime != -1)
		{
			IgniProgressBar->SetPercent(IgniRemainingTime / IgniCooldown);
		}
	}

	bool IsAksiiTimerActive = GetWorld()->GetTimerManager().IsTimerActive(AksiiTimer);

	if (IsAksiiTimerActive)
	{
		AksiiRemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(AksiiTimer);
		if (AksiiRemainingTime != -1)
		{
			AksiiProgressBar->SetPercent(AksiiRemainingTime / AksiiCooldown);
		}
	}

	bool IsKvenTimerActive = GetWorld()->GetTimerManager().IsTimerActive(KvenTimer);

	if (IsKvenTimerActive)
	{
		KvenRemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(KvenTimer);
		if (KvenRemainingTime != -1)
		{
			KvenProgressBar->SetPercent(KvenRemainingTime / KvenCooldown);
		}
	}

	bool IsAardTimerActive = GetWorld()->GetTimerManager().IsTimerActive(AardTimer);

	if (IsAardTimerActive)
	{
		AardRemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(AardTimer);
		if (AardRemainingTime != -1)
		{
			AardProgressBar->SetPercent(AardRemainingTime / AardCooldown);
		}
	}
	
}

void UUW_WitcherSignsInterface::SetSignCooldownTimer(FString SignName)
{
	bool* IsSignAvailable{ nullptr };
	FTimerHandle* SignTimer{ nullptr };
	float* SignCooldown{ nullptr };
	FTimerDelegate SignDelegate;

	if (SignName == "Igni")
	{
		IsSignAvailable = &IsIgniAvailable;
		SignTimer = &IgniTimer;
		SignCooldown = &IgniCooldown;
		SignDelegate = FTimerDelegate::CreateUObject(this, &UUW_WitcherSignsInterface::RefreshSign, FString("Igni"));
	}
	else if (SignName == "Aksii")
	{
		IsSignAvailable = &IsAksiiAvailable;
		SignTimer = &AksiiTimer;
		SignCooldown = &AksiiCooldown;
		SignDelegate = FTimerDelegate::CreateUObject(this, &UUW_WitcherSignsInterface::RefreshSign, FString("Aksii"));
	}
	else if (SignName == "Kven")
	{
		IsSignAvailable = &IsKvenAvailable;
		SignTimer = &KvenTimer;
		SignCooldown = &KvenCooldown;
		SignDelegate = FTimerDelegate::CreateUObject(this, &UUW_WitcherSignsInterface::RefreshSign, FString("Kven"));
	}
	else if (SignName == "Aard")
	{
		IsSignAvailable = &IsAardAvailable;
		SignTimer = &AardTimer;
		SignCooldown = &AardCooldown;
		SignDelegate = FTimerDelegate::CreateUObject(this, &UUW_WitcherSignsInterface::RefreshSign, FString("Aard"));
	}
	else
	{
		return;
	}

	*IsSignAvailable = false;
	if (SignTimer != nullptr && SignCooldown != nullptr)
	{
		GetWorld()->GetTimerManager().SetTimer(*SignTimer, SignDelegate, *SignCooldown, false);
	}
}

void UUW_WitcherSignsInterface::RefreshSign(FString SignName)
{
	UProgressBar* SignProgressBar{ nullptr };
	bool* IsSignAvailable{ nullptr };
	
	if (SignName == "Igni")
	{
		IsSignAvailable = &IsIgniAvailable;
		SignProgressBar = IgniProgressBar;
	}
	else if (SignName == "Aksii")
	{
		IsSignAvailable = &IsAksiiAvailable;
		SignProgressBar = AksiiProgressBar;
	}
	else if (SignName == "Kven")
	{
		IsSignAvailable = &IsKvenAvailable;
		SignProgressBar = KvenProgressBar;
	}
	else if (SignName == "Aard")
	{
		IsSignAvailable = &IsAardAvailable;
		SignProgressBar = AardProgressBar;
	}
	else
	{
		return;
	}

	*IsSignAvailable = true;
	SignProgressBar->SetPercent(0.f);
}

//TODO: move usage stuff to another actor mb
void UUW_WitcherSignsInterface::UseSign(FString SignName)
{
	
	bool* IsSignAvailable{ nullptr };
	
	if (SignName == "Igni")
	{
		IsSignAvailable = &IsIgniAvailable;
	}
	else if (SignName == "Aksii")
	{
		IsSignAvailable = &IsAksiiAvailable;
	}
	else if (SignName == "Kven")
	{
		IsSignAvailable = &IsKvenAvailable;
	}
	else if (SignName == "Aard")
	{
		IsSignAvailable = &IsAardAvailable;
	}
	else
	{
		return;
	}
	if (*IsSignAvailable)
	{
		if (SignName == "Igni") Igni();
		else if (SignName == "Aksii") Aksii();
		else if (SignName == "Kven") Kven();
		else if (SignName == "Aard") Aard();

		//UE_LOG(LogTemp, Warning, TEXT("You used %s"), *SignName);
		
		SetSignCooldownTimer(SignName);
	}

}



void UUW_WitcherSignsInterface::Igni()
{
	//Spawn an Igni actor
	//It increases scale until it occupies half of the screen
	//OnOverlapBegin damages all enemies and kills them (?)
	if (PlayerActor != nullptr) PlayerActor->UseIgni();
}

void UUW_WitcherSignsInterface::Aksii()
{
	//Stops all human enemies
	//Get all enemies by tag (add tag to EnemyParentActor with this->Tags.Add())
	//Add IsStopped bool var to EnemyParentActor
	//Set IsStopped = true to all human enemies for 3 seconds
	//Add some animations to them
	if (PlayerActor != nullptr) PlayerActor->UseAksii();
	//return;

	//TArray<AActor*> EnemyActors;
	//UGameplayStatics::GetAllActorsWithTag(
	//	GetWorld(), "Enemy", EnemyActors);

	////UE_LOG(LogTemp, Warning, TEXT("Found %d enemies"), EnemyActors.Num());

	//TArray<AEnemyActorParent*> StoppedEnemies;
	//for (AActor* Actor : EnemyActors)
	//{
	//	AEnemyActorParent* Enemy = Cast<AEnemyActorParent>(Actor);
	//	if (Enemy != nullptr)
	//	{
	//		if (Enemy->GetEnemyClass() == "Human")
	//		{
	//			//UE_LOG(LogTemp, Warning, TEXT("Stopping an enemy"));
	//			Enemy->SetIsStopped(true);
	//			StoppedEnemies.Add(Enemy);
	//		}
	//	}
	//}

	//FTimerHandle Timer;
	//FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, 
	//	&UUW_WitcherSignsInterface::UnstopEnemies, StoppedEnemies);
	//GetWorld()->GetTimerManager().SetTimer(Timer, TimerDelegate, 3.f, false);

	
}

//void UUW_WitcherSignsInterface::UnstopEnemies(TArray<AEnemyActorParent*> StoppedEnemies)
//{
//	for (AEnemyActorParent* Enemy : StoppedEnemies)
//	{
//		Enemy->SetIsStopped(false);
//	}
//}



//TODO: check if Kven is already used
void UUW_WitcherSignsInterface::Kven()
{
	//Spawn a KvenShieldActor
	//Set player actor's IsKvenActive to true
	//p.s get player actor in begin play or smthg
	
	if (PlayerActor != nullptr) PlayerActor->UseKven();
}

void UUW_WitcherSignsInterface::Aard()
{
	//Stop all enemies
	//Make them move back with 300-500 ms for a second
	//Unstop stopped enemies
	//Add function to move back to EnemyParentActor

	if (PlayerActor != nullptr) PlayerActor->UseAard();
	
	/*GetWorld()->SpawnActor<AAardActor>(
		AardActor, FVector::ZeroVector,
		FRotator::ZeroRotator);*/
}

int UUW_WitcherSignsInterface::GetMonsterKillCount()
{
	return MonsterKillCount;
}

int UUW_WitcherSignsInterface::GetHumanKillCount()
{
	return HumanKillCount;
}

void UUW_WitcherSignsInterface::AddHumanKill()
{
	HumanKillCount += 1;
}

void UUW_WitcherSignsInterface::AddMonsterKill()
{
	MonsterKillCount += 1;
}

void UUW_WitcherSignsInterface::AddKill(FString EnemyClass)
{
	if (EnemyClass == "Monster")
	{
		AddMonsterKill();
		UpdateLabel(EnemyClass);
	}
	else if (EnemyClass == "Human")
	{
		AddHumanKill();
		UpdateLabel(EnemyClass);
	}
}

void UUW_WitcherSignsInterface::UpdateLabel(FString EnemyClass)
{
	if (EnemyClass == "Monster")
	{
		if (MonsterKillCounter != nullptr)
		{
			MonsterKillCounter->SetText(FText::AsNumber(MonsterKillCount));
		}
	}
	else if (EnemyClass == "Human")
	{
		if (HumanKillCounter != nullptr)
		{
			HumanKillCounter->SetText(FText::AsNumber(HumanKillCount));
		}
	}
}

void UUW_WitcherSignsInterface::SetHP(float HealthAmount)
{
	HPProgressBar->SetPercent(HealthAmount / 100.f);
	if (HealthAmount < 25)
	{
		HPProgressBar->SetFillColorAndOpacity(LowHPColor);
	}
	else if (HealthAmount < 75)
	{
		HPProgressBar->SetFillColorAndOpacity(MediumHPColor);
	}
	else
	{
		HPProgressBar->SetFillColorAndOpacity(HighHPColor);
	}
	
}

void UUW_WitcherSignsInterface::InitPlayerActor()
{
	TArray<AActor*> PlayerActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "Player", PlayerActors);
	if (PlayerActors.Num() > 0)
	{
		PlayerActor = (APlayerActor*)PlayerActors[0];
		IgniCooldown = PlayerActor->GetIgniCooldown();
		AardCooldown = PlayerActor->GetAardCooldown();
		AksiiCooldown = PlayerActor->GetAksiiCooldown();
		KvenCooldown = PlayerActor->GetKvenCooldown();
	}
}