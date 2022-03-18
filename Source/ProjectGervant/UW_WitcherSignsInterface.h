// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "ProjectGervant/PlayerActors/PlayerActor.h"
#include "ProjectGervant/PlayerActors/Signs/IgniActor.h"
#include "ProjectGervant/PlayerActors/Signs/AardActor.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "UW_WitcherSignsInterface.generated.h"

//TODO: make a field to hold a world timer manager, populate it in NativeConstruct
//UPD: this doesnt work(((
/**
 * 
 */
UCLASS()
class PROJECTGERVANT_API UUW_WitcherSignsInterface : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	
	//TODO: balance cooldowns. Some signs mb will be usable once per level. If so, change logic
	FTimerHandle IgniTimer;
	float IgniCooldown{ 5.f };
	bool IsIgniAvailable{ true };
	float IgniRemainingTime{ 0.f };

	FTimerHandle AksiiTimer;
	float AksiiCooldown{ 1.f };
	bool IsAksiiAvailable{ true };
	float AksiiRemainingTime{ 0.f };

	FTimerHandle KvenTimer;
	float KvenCooldown{ 5.f };
	bool IsKvenAvailable{ true };
	float KvenRemainingTime{ 0.f };

	FTimerHandle AardTimer;
	float AardCooldown{ 1.f };
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

	UPROPERTY(EditAnywhere, Category = "Actors")
		TSubclassOf<AIgniActor> IgniActor;

	UPROPERTY(EditAnywhere, Category = "Actors")
		TSubclassOf<AAardActor> AardActor;

	/*UPROPERTY(EditAnywhere, Category = "Actors")
		TSubclassOf <APlayerActor> PlayerActor;*/
	APlayerActor* PlayerActor;

	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	//FTimerManager& WorldTimerManager = GetWorld()->GetTimerManager();

	void RefreshSign(FString SignName);

	void Igni();

	void Aksii();

	void Kven();

	void Aard();

	void UnstopEnemies(TArray<AEnemyActorParent*> StoppedEnemies);
public:

	virtual void NativeConstruct() override;

	void SetSignCooldownTimer(FString SignName);

	void UseSign(FString SignName);
	//UUW_WitcherSignsInterface();

	
};
