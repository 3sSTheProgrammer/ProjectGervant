// Copyright Epic Games, Inc. All Rights Reserved.


#include "ProjectGervantGameModeBase.h"

AProjectGervantGameModeBase::AProjectGervantGameModeBase()
{
	ConstructorHelpers::FObjectFinder<UClass>
		ControllerClass(TEXT("Class'/Game/ProjectGervant/Blueprints/BP_InputManagerController.BP_InputManagerController_C'"));
	if (ControllerClass.Object != nullptr)
	{
		PlayerControllerClass = ControllerClass.Object;
	}
}