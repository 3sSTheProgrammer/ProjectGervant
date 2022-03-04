// Fill out your copyright notice in the Description page of Project Settings.


#include "InputManagerController.h"
#include "BeamActor.h"
#include "Kismet/GameplayStatics.h"


void AInputManagerController::BeginPlay()
{
	HumanBeamActor = (ABeamActor*)GetBeamActor(0);
	MonsterBeamActor = (ABeamActor*)GetBeamActor(1);
}

void AInputManagerController::SetupInputComponent()
{
	Super::SetupInputComponent();	

	check(InputComponent != nullptr);
	InputComponent->BindAxis("HumanBeamRotation", this,
		&AInputManagerController::RotateHumanBeam);
	InputComponent->BindAxis("MonsterBeamRotation", this,
		&AInputManagerController::RotateMonsterBeam);
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
	UE_LOG(LogTemp, Warning, TEXT("getbeamactor started"));
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
			UE_LOG(LogTemp, Warning, TEXT("actor real name %s"), *Actor->GetName());
			UE_LOG(LogTemp, Warning, TEXT("actor supposed name %s"), *ActorName);
			if (*Actor->GetName() == ActorName)
			{
				UE_LOG(LogTemp, Warning, TEXT("VIZHU DRUGOI ACTOR %s"), *Actor->GetName());
				AnotherActor = Actor;
			}
		}
	}

	return AnotherActor;
}