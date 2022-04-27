// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "ProjectGervant/PlayerActors/PlayerActor.h"


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
	ABeamActor* HumanBeamActor{ nullptr };
	ABeamActor* MonsterBeamActor{ nullptr };

protected:
	virtual void BeginPlay() override;

	//APlayerActor* PlayerActor;

	// Dynamic reference to the blueprint class
	TSubclassOf<class UUserWidget> GameInterfaceClass;

	TSubclassOf<class UUserWidget> PauseMenuClass;

	// Internal reference to the blueprint for gameplay logic
	UPROPERTY(BlueprintReadWrite, Category = "UI")
		class UUW_WitcherSignsInterface* GameInterface;

	//UPROPERTY(BlueprintReadWrite, Category = "UI")
	//	class UUserWidget* PauseMenu;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> PauseMenuWidgetClass;
public:
	AInputManagerController();

	virtual void SetupInputComponent() override;

	void RotateHumanBeam(float input);

	void RotateMonsterBeam(float input);

	/**
	 * Gets a pointer to a beam actor object
	 * @param marker - defines if human(0) or monster(1) beam should be found
	 * @return human/monster actor pointer
	*/
	//TODO: change marker to be FString
	AActor* GetBeamActor(int marker);

	void UseIgni();

	void UseAksii();
	
	void UseKven();
	
	void UseAard();

	void SetPause();
};
