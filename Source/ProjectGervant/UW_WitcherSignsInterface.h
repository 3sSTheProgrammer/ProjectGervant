// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_WitcherSignsInterface.generated.h"

class UProgressBar;
class UTextBlock;
class AAardActor;
class AIgniActor;
class APlayerActor;
class AStoryTellerActor;

UCLASS()
class PROJECTGERVANT_API UUW_WitcherSignsInterface : public UUserWidget
{
	GENERATED_BODY()


protected:
	// Amount of monster kills 
	int MonsterKillCount;
	
	// Amount of human kills
	int HumanKillCount;
	
	// Total enemies that died on level
	int TotalDeadEnemies;

	// Reference to story teller
	UPROPERTY()
	AStoryTellerActor* StoryTeller;

	// Sign cooldowns, availability and time remaining till availability
	FTimerHandle IgniTimer;
	float IgniCooldown;
	bool IsIgniAvailable{ true };
	float IgniRemainingTime{ 0.f };

	FTimerHandle AksiiTimer;
	float AksiiCooldown;
	bool IsAksiiAvailable{ true };
	float AksiiRemainingTime{ 0.f };

	FTimerHandle KvenTimer;
	float KvenCooldown;
	bool IsKvenAvailable{ true };
	float KvenRemainingTime{ 0.f };

	FTimerHandle AardTimer;
	float AardCooldown;
	bool IsAardAvailable{ true };
	float AardRemainingTime{ 0.f };

	// Widget components
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* IgniProgressBar;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* AksiiProgressBar;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* KvenProgressBar;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* AardProgressBar;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MonsterKillCounterLabel;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* HumanKillCounterLabel;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MonsterKillCounter;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* HumanKillCounter;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HPProgressBar;




	// Reference to player actor
	UPROPERTY()
	APlayerActor* PlayerActor;

	// Colors for HP bar
	FLinearColor HighHPColor;
	FLinearColor MediumHPColor;
	FLinearColor LowHPColor;

	/**
		@brief Native tick of widget. Checks if signs cooldowns are active and updates its progress
	*/
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	/**
	 @brief Updates progress bar for chosen sign
	 @param SignName updates sign name
	*/
	void RefreshSign(FString SignName);

	/**
		@brief Make player use Igni
	*/
	void Igni() const;

	/**
		@brief Make player use Aksii
	*/
	void Aksii() const;

	/**
	 @brief Make player use Kven
	*/
	void Kven() const;

	/**
	 @brief Make player use Aard
	*/
	void Aard() const;

	/**
	 @brief Find player actor in the level and get needed info
	 from it (sign cooldowns)
	*/
	void InitPlayerActor();

	/**
	 @brief Find Story Teller in the level
	*/
	void InitStoryTeller();

	/**
	 @brief Updates label with kill counter
	 @param EnemyClass "Human"/"Monster"
	*/
	void UpdateLabel(FString EnemyClass);

public:
	/**
	 @brief Constructor. Sets default values for fields 
	*/
	virtual void NativeConstruct() override;

	/**
	 @brief Starts cooldown of chosen sign
	 @param SignName name of sign
	*/
	void SetSignCooldownTimer(FString SignName);

	/**
	 @brief Checks if sign is available and uses it
	 @param SignName Name of used sign
	*/
	void UseSign(FString SignName);

	/**
		@param EnemyClass "Human"/"Monster"
		@brief Increases counter of killed enemies. If counter is more than
		number of enemies on this level than end level  
	*/
	void AddKill(FString EnemyClass);

	/**
	 @param EnemyClass "Human"/"Monster"
	 @brief Adds an enemy which was not killed by player to
	 total dead enemy counter. If counter is more than
	 number of enemies on this level than end level  
	*/
	void AddNotKilledEnemy(FString EnemyClass);

	/**
	 @brief Updates HP bar to current player health
	 @param HealthAmount current player HP
	*/
	void SetHP(float HealthAmount);
	
};
