// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectGervant/UW_WitcherSignsInterface.h"

//UUW_WitcherSignsInterface::UUW_WitcherSignsInterface()
//{
//	PrimaryActorTick.bCanEverTick = true;
//}

void UUW_WitcherSignsInterface::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);
	float IgniElapsedTime = GetWorld()->GetTimerManager().GetTimerElapsed(IgniTimer);
	//UE_LOG(LogTemp, Warning, TEXT("Elapsed time %f"), IgniElapsedTime);
	if (IgniElapsedTime != -1)
	{
		IgniProgressBar->SetPercent(IgniElapsedTime / IgniCooldown);
	}
}

void UUW_WitcherSignsInterface::TestProgressBar()
{
	
	GetWorld()->GetTimerManager().SetTimer(IgniTimer, this,
		&UUW_WitcherSignsInterface::TestTest, IgniCooldown);

	
	
}

void UUW_WitcherSignsInterface::TestTest()
{
	TestProgressBar();
}