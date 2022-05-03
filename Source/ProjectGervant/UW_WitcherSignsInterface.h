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

UCLASS()
class PROJECTGERVANT_API UUW_WitcherSignsInterface : public UUserWidget
{
	GENERATED_BODY()


protected:
	
	int MonsterKillCount;
	int HumanKillCount;

	//TODO: balance cooldowns. Some signs mb will be usable once per level. If so, change logic
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

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* IgniProgressBar;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* AksiiProgressBar;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* KvenProgressBar;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* AardProgressBar;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MonsterKillCounter;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* HumanKillCounter;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HPProgressBar;

	UPROPERTY(EditAnywhere, Category = "Actors")
		TSubclassOf<AIgniActor> IgniActor;

	UPROPERTY(EditAnywhere, Category = "Actors")
		TSubclassOf<AAardActor> AardActor;

	/*UPROPERTY(EditAnywhere, Category = "Actors")
		TSubclassOf <APlayerActor> PlayerActor;*/
	APlayerActor* PlayerActor;

	FLinearColor HighHPColor;
	FLinearColor MediumHPColor;
	FLinearColor LowHPColor;

	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	//FTimerManager& WorldTimerManager = GetWorld()->GetTimerManager();

	void RefreshSign(FString SignName);

	void Igni();

	void Aksii();

	void Kven();

	void Aard();

	//void UnstopEnemies(TArray<AEnemyActorParent*> StoppedEnemies);

	void InitPlayerActor();

	void UpdateLabel(FString EnemyClass);

public:

	virtual void NativeConstruct() override;

	void SetSignCooldownTimer(FString SignName);

	void UseSign(FString SignName);
	//UUW_WitcherSignsInterface();

	UFUNCTION(BlueprintCallable)
		int GetMonsterKillCount();

	UFUNCTION(BlueprintCallable)
		int GetHumanKillCount();

	void AddHumanKill();

	void AddMonsterKill();

	void AddKill(FString EnemyClass);

	void SetHP(float HealthAmount);
	
};
