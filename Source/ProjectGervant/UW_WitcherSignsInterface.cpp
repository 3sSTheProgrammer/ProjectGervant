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

	//TODO: check if all pointers are not nullptrs
	*IsSignAvailable = false;
	//UE_LOG(LogTemp, Warning, TEXT("Ingi available: %d"), *IsSignAvailable);
	//UE_LOG(LogTemp, Warning, TEXT("Ingi available: %d"), IsIgniAvailable);
	GetWorld()->GetTimerManager().SetTimer(*SignTimer, SignDelegate, *SignCooldown, false);
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
		UE_LOG(LogTemp, Warning, TEXT("You used %s"), *SignName);
		SetSignCooldownTimer(SignName);
	}
}