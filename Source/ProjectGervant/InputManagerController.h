// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BeamActor.h"

//#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"
#include "InputManagerController.generated.h"



/**
 * 
 */
UCLASS()
class PROJECTGERVANT_API AInputManagerController : public APlayerController
{
	GENERATED_BODY()

private:
	ABeamActor* HumanBeamActor{ nullptr };
	ABeamActor* MonsterBeamActor{ nullptr };

protected:
	virtual void BeginPlay() override;

public:
	
	virtual void SetupInputComponent() override;

	void RotateHumanBeam(float input);

	void RotateMonsterBeam(float input);

	/**
	 * Gets a pointer to a beam actor object
	 * @param marker - defines if human(0) or monster(1) beam should be found
	 * @return human/monster actor pointer
	*/
	AActor* GetBeamActor(int marker);
};
