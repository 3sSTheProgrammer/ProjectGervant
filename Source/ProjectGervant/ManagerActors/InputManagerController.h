// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputManagerController.generated.h"

class ABeamActor;
class UUW_WitcherSignsInterface;

/**
 * 
 */
UCLASS()
class PROJECTGERVANT_API AInputManagerController : public APlayerController
{
	GENERATED_BODY()

private:
	// References to human and monster beams
	UPROPERTY()
	ABeamActor* HumanBeamActor{ nullptr };
	UPROPERTY()
	ABeamActor* MonsterBeamActor{ nullptr };

protected:
	virtual void BeginPlay() override;

	// Reference to game interface widget class
	TSubclassOf<class UUserWidget> GameInterfaceClass;

	// Reference to pause menu widget class
	TSubclassOf<class UUserWidget> PauseMenuClass;

	// Reference to game interface widget 
	UPROPERTY(BlueprintReadWrite, Category = "UI")
		class UUW_WitcherSignsInterface* GameInterface;

	// Reference to pause menu widget
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> PauseMenuWidgetClass;
public:
	// Constructor
	AInputManagerController();
	
	virtual void SetupInputComponent() override;

	/**
	 @brief Reaction to Rotate Human Beam input
	*/
	void RotateHumanBeam(float input);

	/**
	 @brief Reaction to Rotate Monster Beam input
	*/
	void RotateMonsterBeam(float input);

	/**
	 * Gets a pointer to a beam actor object
	 * @param marker - defines if human(0) or monster(1) beam should be found
	 * @return human/monster actor pointer
	*/
	//TODO: change marker to be FString
	AActor* GetBeamActor(int marker);

	/**
	* @brief Reactions to Use sign input
	*/
	void UseIgni();
	void UseAksii();
	void UseKven();
	void UseAard();

	/**
	* @brief  Reaction to pause input
	*/
	void SetPause();
};
