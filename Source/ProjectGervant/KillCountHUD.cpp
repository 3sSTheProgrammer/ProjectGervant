// Fill out your copyright notice in the Description page of Project Settings.


#include "KillCountHUD.h"

void AKillCountHUD::DrawHUD()
{
	Super::DrawHUD();

	FString HudString = MonsterKillLabel + FString::FromInt(MonsterKills) +
		"\n" + HumanKillLabel + FString::FromInt(HumanKills);
	
	DrawText(HudString, FLinearColor::White,
		LeftOffset, TopOffset, HudFont);
}

void AKillCountHUD::AddKill(FString EnemyClass)
{
	if (EnemyClass == "Monster")
	{
		AddMonsterKill();
	}
	else if (EnemyClass == "Human")
	{
		AddHumanKill();
	}
}

void AKillCountHUD::AddMonsterKill()
{
	MonsterKills += 1;
	//UE_LOG(LogTemp, Warning, TEXT("Monster kills %d"), MonsterKills);
}

void AKillCountHUD::AddHumanKill()
{
	HumanKills += 1;
	//UE_LOG(LogTemp, Warning, TEXT("Human kills %d"), HumanKills);
}

int AKillCountHUD::GetKillsAmount()
{
	return HumanKills + MonsterKills;
}