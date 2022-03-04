// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "KillCountHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTGERVANT_API AKillCountHUD : public AHUD
{
	GENERATED_BODY()

		const int LeftOffset{ 75 };
		const int TopOffset{ 50 };
		const FString MonsterKillLabel{ "Monster: "};
		const FString HumanKillLabel{ "Human: " };
		int MonsterKills{ 0 };
		int HumanKills{ 0 };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = HUDFont)
		UFont* HudFont;

	virtual void DrawHUD() override;

	/**
	 * adds a score to a specific enemy class
	 * @param EnemyClass specifies which enemy class to add kill to (Monster/Human)
	*/
	void AddKill(FString EnemyClass);

	void AddMonsterKill();

	void AddHumanKill();

	int GetKillsAmount();
};
