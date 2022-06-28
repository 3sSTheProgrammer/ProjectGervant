// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectGervant/UW_WitcherSignsInterface.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectGervant/PlayerActors/PlayerActor.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "ProjectGervant/ManagerActors/StoryTellerActor.h"


/**
 @brief Constructor. Sets default values for fields 
 */
void UUW_WitcherSignsInterface::NativeConstruct()
{
	UUserWidget::NativeConstruct();

	InitPlayerActor();
	InitStoryTeller();

	MonsterKillCount = 0;
	HumanKillCount = 0;

	HighHPColor = FLinearColor(0.03, 0.54, 0.06, 1.0); //Green
	MediumHPColor = FLinearColor(0.96, 0.4, 0.0, 1.0); //Orange
	LowHPColor = FLinearColor(0.45, 0.0, 0.01, 1.0); //Red

	FString CurrentLevel = GetWorld()->GetMapName();
	if (CurrentLevel == "InfiniteLevel")
	{
		MonsterKillCounterLabel->SetVisibility(ESlateVisibility::Visible);
		MonsterKillCounter->SetVisibility(ESlateVisibility::Visible);
		HumanKillCounter->SetVisibility(ESlateVisibility::Visible);
		HumanKillCounterLabel->SetVisibility(ESlateVisibility::Visible);
	}
}

/**
 @brief Native tick of widget. Checks if signs cooldowns are active and updates its progress
*/
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

/**
 @brief Starts cooldown of chosen sign
 @param SignName name of sign
*/
void UUW_WitcherSignsInterface::SetSignCooldownTimer(const FString SignName)
{
	bool* IsSignAvailable; //{ nullptr }
	FTimerHandle* SignTimer; //{ nullptr }
	float* SignCooldown; //{ nullptr }
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

/**
 @brief Updates progress bar for chosen sign
 @param SignName updates sign name
*/
void UUW_WitcherSignsInterface::RefreshSign(const FString SignName)
{
	UProgressBar* SignProgressBar;
	bool* IsSignAvailable; 
	
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

/**
 @brief Checks if sign is available and uses it
 @param SignName Name of used sign
*/
void UUW_WitcherSignsInterface::UseSign(const FString SignName)
{
	bool* IsSignAvailable; 
	
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
		
		SetSignCooldownTimer(SignName);
	}
}

/**
	@brief Make player use Igni
*/
void UUW_WitcherSignsInterface::Igni() const
{
	if (PlayerActor != nullptr) PlayerActor->UseIgni();
}

/**
	@brief Make player use Aksii
*/
void UUW_WitcherSignsInterface::Aksii() const
{
	if (PlayerActor != nullptr) PlayerActor->UseAksii();
}

/**
 @brief Make player use Kven
*/
void UUW_WitcherSignsInterface::Kven() const
{
	if (PlayerActor != nullptr) PlayerActor->UseKven();
}

/**
 @brief Make player use Aard
*/
void UUW_WitcherSignsInterface::Aard() const
{
	if (PlayerActor != nullptr) PlayerActor->UseAard();
}

/**
	@param EnemyClass "Human"/"Monster"
	@brief Increases counter of killed enemies. If counter is more than
	number of enemies on this level than end level  
*/
void UUW_WitcherSignsInterface::AddKill(FString EnemyClass)
{
	if (EnemyClass == "Monster")
	{
		MonsterKillCount += 1;
		UpdateLabel(EnemyClass);
	}
	else if (EnemyClass == "Human")
	{
		HumanKillCount += 1;
		UpdateLabel(EnemyClass);
	}
	TotalDeadEnemies += 1;

	if (StoryTeller == nullptr)
	{
		InitStoryTeller();
	}
	int MaxKills = StoryTeller->GetAmountOfKillsNeeded();
	UE_LOG(LogTemp, Warning, TEXT("Score %d"), TotalDeadEnemies);
	if (TotalDeadEnemies >= MaxKills)
	{
		PlayerActor->InvokeLevelCompleted();
	}
}

/**
 @brief Updates label with kill counter
 @param EnemyClass "Human"/"Monster"
 */
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

/**
 @brief Updates HP bar to current player health
 @param HealthAmount current player HP
*/
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

int UUW_WitcherSignsInterface::GetTotalScore()
{
	return HumanKillCount + MonsterKillCount;
}

/**
    @param EnemyClass "Human"/"Monster"
    @brief Adds an enemy which was not killed by player to
    total dead enemy counter. If counter is more than
    number of enemies on this level than end level  
*/
void UUW_WitcherSignsInterface::AddNotKilledEnemy(FString EnemyClass)
{
	TotalDeadEnemies += 1;

	if (StoryTeller == nullptr)
	{
		InitStoryTeller();
	}
	int MaxKills = StoryTeller->GetAmountOfKillsNeeded();
	UE_LOG(LogTemp, Warning, TEXT("Score %d"), TotalDeadEnemies);
	if (TotalDeadEnemies >= MaxKills)
	{
		PlayerActor->InvokeLevelCompleted();
	}
}

/**
 @brief Find player actor in the level and get needed info
 from it (sign cooldowns)
*/
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

/**
 @brief Find Story Teller in the level
*/
void UUW_WitcherSignsInterface::InitStoryTeller()
{
	TArray<AActor*> StoryTellers;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "StoryTeller", StoryTellers);
	if (StoryTellers.Num() > 0)
	{
		StoryTeller = static_cast<AStoryTellerActor*>(StoryTellers[0]);
	}
}