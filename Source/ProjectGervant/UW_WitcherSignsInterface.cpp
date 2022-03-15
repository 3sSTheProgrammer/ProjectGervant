// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectGervant/UW_WitcherSignsInterface.h"

//UUW_WitcherSignsInterface::UUW_WitcherSignsInterface()
//{
//	PrimaryActorTick.bCanEverTick = true;
//}

void UUW_WitcherSignsInterface::NativeConstruct()
{
	UUserWidget::NativeConstruct();

	/*UWorld* World = GetWorld();
	WorldTimerManager = World->GetTimerManager();
	WorldTimerManager = GetWorld()->GetTimerManager();*/
}

void UUW_WitcherSignsInterface::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	//here should be Super::, but it somehow thinks that Super is UWidget((
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
	//TODO: implement usage of SignName
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
	//TFunction<void()> SignFunction{ nullptr };
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

		UE_LOG(LogTemp, Warning, TEXT("You used %s"), *SignName);
		
		SetSignCooldownTimer(SignName);
	}

}

void UUW_WitcherSignsInterface::Igni()
{
	//Spawn an Igni actor
	//It increases scale until it occupies half of the screen
	//OnOverlapBegin damages all enemies and kills them (?)

	GetWorld()->SpawnActor<AIgniActor>(
		IgniActor, FVector::ZeroVector,
		FRotator::ZeroRotator);
}

void UUW_WitcherSignsInterface::Aksii()
{
	//Stops all human enemies
	//Get all enemies by tag (add tag to EnemyParentActor with this->Tags.Add())
	//Add IsStopped bool var to EnemyParentActor
	//Set IsStopped = true to all human enemies for 3 seconds
	//Add some animations to them

	//TODO: Add tag "Enemy" in EnemyActor Parent
	TArray<AActor*> EnemyActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "Enemy", EnemyActors);

	TArray<AEnemyActorParent*> StoppedEnemies;
	for (AActor* Actor : EnemyActors)
	{
		AEnemyActorParent* Enemy = Cast<AEnemyActorParent>(Actor);
		if (Enemy != nullptr)
		{
			if (Enemy->GetEnemyClass() == "Monster") //"Human"
			{
				UE_LOG(LogTemp, Warning, TEXT("Stopping an enemy"));
				Enemy->SetIsStopped(true);
				StoppedEnemies.Add(Enemy);
			}
		}
	}

	FTimerHandle Timer;
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, 
		&UUW_WitcherSignsInterface::UnstopEnemies, StoppedEnemies);
	GetWorld()->GetTimerManager().SetTimer(Timer, TimerDelegate, 3.f, false);

	
}

void UUW_WitcherSignsInterface::UnstopEnemies(TArray<AEnemyActorParent*> StoppedEnemies)
{
	for (AEnemyActorParent* Enemy : StoppedEnemies)
	{
		Enemy->SetIsStopped(false);
	}
}

void UUW_WitcherSignsInterface::Kven()
{
	//Spawn a KvenShieldActor
	//Set player actor's IsKvenActive to true
	//p.s get player actor in begin play or smthg

	/*APlayerActor* Player = Cast<APlayerActor>(PlayerActor);
	if (Player != nullptr) Player->TurnKvenOn();
	else UE_LOG(LogTemp, Warning, TEXT("Player is null"));*/

	TArray<AActor*> PlayerActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "Player", PlayerActors);
	if (PlayerActors.Num() > 0) PlayerActor = (APlayerActor*)PlayerActors[0];
	
	if (PlayerActor != nullptr) PlayerActor->TurnKvenOn();
}

void UUW_WitcherSignsInterface::Aard()
{
	//Stop all enemies
	//Make them move back with 300-500 ms for a second
	//Unstop stopped enemies
	//Add function to move back to EnemyParentActor
}