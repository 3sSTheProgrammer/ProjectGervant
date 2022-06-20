// Fill out your copyright notice in the Description page of Project Settings.

#include "InputManagerController.h"
#include "ProjectGervant/UW_WitcherSignsInterface.h"
#include "ProjectGervant/PlayerActors/BeamActor.h"
#include "Kismet/GameplayStatics.h"

AInputManagerController::AInputManagerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> GameInterfaceUIBPClass(TEXT("/Game/ProjectGervant/Menus/GameInterface"));

	if (GameInterfaceUIBPClass.Class != nullptr)
	{
		GameInterfaceClass = GameInterfaceUIBPClass.Class;
	}
}


void AInputManagerController::BeginPlay()
{
	Super::BeginPlay();
	HumanBeamActor = static_cast<ABeamActor*>(GetBeamActor(0));
	MonsterBeamActor = static_cast<ABeamActor*>(GetBeamActor(1));

	if (GameInterfaceClass != nullptr)
	{
		GameInterface = CreateWidget<UUW_WitcherSignsInterface>(GetWorld(), GameInterfaceClass);
		if (GameInterface != nullptr)
		{
			GameInterface->AddToViewport();
			GameInterface->SetVisibility(ESlateVisibility::Hidden);
			GameInterface->SetIsEnabled(true);
		}
	}
}

void AInputManagerController::SetupInputComponent()
{
	Super::SetupInputComponent();	

	check(InputComponent != nullptr);
	InputComponent->BindAxis("HumanBeamRotation", this,
		&AInputManagerController::RotateHumanBeam);
	InputComponent->BindAxis("MonsterBeamRotation", this,
		&AInputManagerController::RotateMonsterBeam);

	InputComponent->BindAction("UseIgni", EInputEvent::IE_Pressed,
		this, &AInputManagerController::UseIgni);
	InputComponent->BindAction("UseAksii", EInputEvent::IE_Pressed,
		this, &AInputManagerController::UseAksii);
	InputComponent->BindAction("UseKven", EInputEvent::IE_Pressed,
		this, &AInputManagerController::UseKven);
	InputComponent->BindAction("UseAard", EInputEvent::IE_Pressed,
		this, &AInputManagerController::UseAard);

	InputComponent->BindAction("Pause", EInputEvent::IE_Pressed,
		this, &AInputManagerController::PauseGame);
}

/**
 * @brief Reaction to Rotate Human Beam input
*/
void AInputManagerController::RotateHumanBeam(float input)
{
	if (input != 0)
	{
		HumanBeamActor->Rotate(input);
	}
}

/**
 * @brief Reaction to Rotate Monster Beam input
*/
void AInputManagerController::RotateMonsterBeam(float input)
{
	if (input != 0)
	{
		MonsterBeamActor->Rotate(input);
	}
}

 
/**
 * Gets a pointer to a beam actor object
 * @param marker - defines if human(0) or monster(1) beam should be found
 * @return human/monster actor pointer
*/
AActor* AInputManagerController::GetBeamActor(int marker)
{
	FName Tag;
	FString ActorName;
	if (marker == 0)
	{
		Tag = "HumanBeam";
		ActorName = "HumanBeamActor";
	}
	else if (marker == 1)
	{
		Tag = "MonsterBeam";
		ActorName = "MonsterBeamActor";
	}
	else
	{
		return nullptr;
	}

	TArray<AActor*> AnotherActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), Tag, AnotherActors);

	ABeamActor* AnotherActor{ nullptr };
	if (AnotherActors.Num() > 0)
	{		
		for (int i = 0; i < AnotherActors.Num(); ++i)
		{
			ABeamActor* Actor = static_cast<ABeamActor*>(AnotherActors[i]);
			if (*Actor->GetName() == ActorName)
			{
				AnotherActor = Actor;
			}
		}
	}

	return AnotherActor;
}

/**
 * @brief Reactions to Use sign input
 */
void AInputManagerController::UseIgni()
{
	//UE_LOG(LogTemp, Warning, TEXT("Controller uses igni"));
	GameInterface->UseSign("Igni");
}

void AInputManagerController::UseAksii()
{
	GameInterface->UseSign("Aksii");
}

void AInputManagerController::UseKven()
{
	GameInterface->UseSign("Kven");
}

void AInputManagerController::UseAard()
{
	GameInterface->UseSign("Aard");
}

/**
 * @brief  Reaction to pause input
 */
void AInputManagerController::PauseGame()
{
	if (PauseMenuWidgetClass != nullptr)
	{
		UUserWidget* PauseMenu = CreateWidget<UUserWidget>(GetWorld(), PauseMenuWidgetClass);
		if (PauseMenu != nullptr)
		{
			PauseMenu->AddToViewport();
		}
	}
}