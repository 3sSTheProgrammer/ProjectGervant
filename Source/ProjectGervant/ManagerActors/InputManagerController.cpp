// Fill out your copyright notice in the Description page of Project Settings.


#include "InputManagerController.h"
//#include "BeamActor.h"
#include "Kismet/GameplayStatics.h"

AInputManagerController::AInputManagerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> GameInterfaceUIBPClass(TEXT("/Game/ProjectGervant/Menus/Widgets/GameInterface"));

	if (GameInterfaceUIBPClass.Class != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("widget class found"));
		GameInterfaceClass = GameInterfaceUIBPClass.Class;
	}
}


void AInputManagerController::BeginPlay()
{
	Super::BeginPlay();

	HumanBeamActor = (ABeamActor*)GetBeamActor(0);
	MonsterBeamActor = (ABeamActor*)GetBeamActor(1);

	if (GameInterfaceClass != nullptr)
	{
		GameInterface = CreateWidget<UUW_WitcherSignsInterface>(GetWorld(), GameInterfaceClass);
		if (GameInterface != nullptr)
		{
			GameInterface->AddToViewport();

			//
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
}


void AInputManagerController::RotateHumanBeam(float input)
{
	if (input != 0)
	{
		HumanBeamActor->Rotate(input);
	}
}

void AInputManagerController::RotateMonsterBeam(float input)
{
	if (input != 0)
	{
		MonsterBeamActor->Rotate(input);
	}
}

AActor* AInputManagerController::GetBeamActor(int marker)
{
	//UE_LOG(LogTemp, Warning, TEXT("getbeamactor started"));
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
			ABeamActor* Actor = (ABeamActor*)AnotherActors[i];
			//UE_LOG(LogTemp, Warning, TEXT("actor real name %s"), *Actor->GetName());
			//UE_LOG(LogTemp, Warning, TEXT("actor supposed name %s"), *ActorName);
			if (*Actor->GetName() == ActorName)
			{
				//UE_LOG(LogTemp, Warning, TEXT("VIZHU DRUGOI ACTOR %s"), *Actor->GetName());
				AnotherActor = Actor;
			}
		}
	}

	return AnotherActor;
}

void AInputManagerController::UseIgni()
{
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