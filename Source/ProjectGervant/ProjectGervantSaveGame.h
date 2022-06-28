// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ProjectGervantSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTGERVANT_API UProjectGervantSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Saved Game Data")
		int HighScore;
};
