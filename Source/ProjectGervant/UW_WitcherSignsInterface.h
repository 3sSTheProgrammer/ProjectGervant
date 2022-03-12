// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "UW_WitcherSignsInterface.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTGERVANT_API UUW_WitcherSignsInterface : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	
	FTimerHandle IgniTimer;

	float IgniCooldown{ 5.f };

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TestLabel;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* IgniProgressBar;

	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;



	void TestTest();
public:
	void TestProgressBar();

	//UUW_WitcherSignsInterface();
};
