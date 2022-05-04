// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyActorParent.h"
#include "ProjectGervant/PlayerActors/PlayerActor.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "ProjectGervant/UW_WitcherSignsInterface.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

// Sets default values
AEnemyActorParent::AEnemyActorParent()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Find game interface widget
	static ConstructorHelpers::FClassFinder<UUserWidget> GameInterfaceUIBPClass(TEXT("/Game/ProjectGervant/Menus/GameInterface"));

	if (GameInterfaceUIBPClass.Class != nullptr)
	{
		GameInterfaceClass = GameInterfaceUIBPClass.Class;
	}
}

FString AEnemyActorParent::GetEnemyClass()
{
	return EnemyClass;
}

//TODO: consider create a enum for enemy status
// Setting Attacked status 
//void AEnemyActorParent::SetIsAttacked(bool Status)
//{
//	// Change material mask depending on Status value
//	if (IsHealed && Status)
//	{
//		EnemyDinamicMaterial->SetTextureParameterValue(FName(TEXT("Mask")), UMaskTexture);
//		EnemyDinamicMaterial->SetVectorParameterValue(FName(TEXT("MaskColor")), FLinearColor(1.f, 0.39, 0.0f, 0.f));
//	}
//	else if (Status)
//	{
//		EnemyDinamicMaterial->SetTextureParameterValue(FName(TEXT("Mask")), UMaskTexture);
//		EnemyDinamicMaterial->SetVectorParameterValue(FName(TEXT("MaskColor")), FLinearColor(0.5, 0.f, 0.f, 1.f));
//	}
//	else
//	{
//		EnemyDinamicMaterial->SetTextureParameterValue(FName(TEXT("Mask")), UDefaultTexture);
//
//	}
//	IsAttacked = Status;
//}
//
//// Setting Healed status
//void AEnemyActorParent::SetIsHealed(bool Status)
//{
//	// Change material mask depending on Status value
//	if (IsAttacked && Status)
//	{
//		EnemyDinamicMaterial->SetTextureParameterValue(FName(TEXT("Mask")), UMaskTexture);
//		EnemyDinamicMaterial->SetVectorParameterValue(FName(TEXT("MaskColor")), FLinearColor(1.f, 0.39, 0.0f, 0.f));
//	}
//	else if (Status)
//	{
//		EnemyDinamicMaterial->SetTextureParameterValue(FName(TEXT("Mask")), UMaskTexture);
//		EnemyDinamicMaterial->SetVectorParameterValue(FName(TEXT("MaskColor")), FLinearColor(0.f, 0.9, 0.02f, 1.f));
//	}
//	else
//	{
//		EnemyDinamicMaterial->SetTextureParameterValue(FName(TEXT("Mask")), UDefaultTexture);
//	}
//	IsAttacked = Status;
//}

// Set actor status for Attacked/healed or both 
void AEnemyActorParent::SetBeamInteractionStatus(FString Interaction, bool Status)
{
	if (Interaction == "Heal") IsHealed = Status;
	else if (Interaction == "Attack") IsAttacked = Status;
	

	if (IsAttacked && IsHealed)
	{
		PlayHitSound();
		EnemyDinamicMaterial->SetTextureParameterValue(FName(TEXT("InteractionMask")), UInteractionTexture);
		EnemyDinamicMaterial->SetVectorParameterValue(FName(TEXT("InteractionMaskColor")), FLinearColor(1.f, 0.39, 0.0f, 0.f));
	}
	else if (IsAttacked)
	{
		PlayHitSound();
		EnemyDinamicMaterial->SetTextureParameterValue(FName(TEXT("InteractionMask")), UInteractionTexture);
		EnemyDinamicMaterial->SetVectorParameterValue(FName(TEXT("InteractionMaskColor")), FLinearColor(0.5, 0.f, 0.f, 1.f));
		
	}
	else if (IsHealed)
	{
		EnemyDinamicMaterial->SetTextureParameterValue(FName(TEXT("InteractionMask")), UInteractionTexture);
		EnemyDinamicMaterial->SetVectorParameterValue(FName(TEXT("InteractionMaskColor")), FLinearColor(0.f, 0.9, 0.02f, 1.f));
	}
	else
	{
		EnemyDinamicMaterial->SetTextureParameterValue(FName(TEXT("InteractionMask")), UEmptyTexture);
	}

}

// Called when the game starts or when spawned
void AEnemyActorParent::BeginPlay()
{
	Super::BeginPlay();
	
	// find static mesh component
	TArray<UStaticMeshComponent*> StaticMeshComponents;
	GetComponents(StaticMeshComponents);

	//UE_LOG(LogTemp, Warning, TEXT("Components: "), StaticMeshComponents.Num());

	if (StaticMeshComponents.Num() > 0)
	{
		StaticMeshComponent = StaticMeshComponents[0];
	}

	// find player actor and save it for efficiency
	TArray<AActor*> PlayerActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "Player", PlayerActors);

	if (PlayerActors.Num() > 0)
	{
		PlayerActor = (APlayerActor*)PlayerActors[0];
	}

	TArray<UUserWidget*> Widgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), Widgets, GameInterfaceClass);
	//UE_LOG(LogTemp, Warning, TEXT("WIDGETS: %d"), Widgets.Num());
	if (Widgets.Num() > 0)
	{
		GameInterface = Widgets[0];
		//UE_LOG(LogTemp, Warning, TEXT("NASHEL WIDGET"));
	}
	//return;
	// Create an instance of default material and set it to static mesh
	EnemyDinamicMaterial = UMaterialInstanceDynamic::Create(UEnemyMaterial, this);
	EnemyDinamicMaterial->SetTextureParameterValue(FName(TEXT("ColorMask")), UColorTexture);
	StaticMeshComponent->SetMaterial(0, EnemyDinamicMaterial);
	
	
	

	UGameplayStatics::PlaySound2D(this, SpawnSound);
}

// Called every frame
void AEnemyActorParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	


	// Moves with enemy specifics
	/*UE_LOG(LogTemp, Warning, TEXT("ISSTOPPED: %d"), IsStopped);
	UE_LOG(LogTemp, Warning, TEXT("ISAARDED: %d"), IsAarded);*/
	if (!IsStopped && !IsAarded)
	{
		MovementManager(DeltaTime);
	}
	else if (IsAarded)
	{
		MoveBack(DeltaTime);
	}
}

// Applies damage to enemy
void AEnemyActorParent::ReceiveDamage(float DamageAmount)
{
	//TODO: Somehow this doesnt find anything in BeginPlay(), so it has to be moved to somewhere
	// Finding GameInterface Widget
	/*if (GameInterface == nullptr)
	{
		TArray<UUserWidget*> Widgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), Widgets, GameInterfaceClass);
		UE_LOG(LogTemp, Warning, TEXT("WIDGETS: %d"), Widgets.Num());
		if (Widgets.Num() > 0)
		{
			GameInterface = Widgets[0];
			UE_LOG(LogTemp, Warning, TEXT("NASHEL WIDGET"));
		}
	}*/


	// Reduce health
	Health -= DamageAmount;

	// if health is below zero adds kill to HUD and destroys self
	if (Health <= 0)
	{
		/*AKillCountHUD* Hud = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AKillCountHUD>();
		if (Hud != nullptr)
		{
			Hud->AddKill(EnemyClass);
		}*/
		
		UUW_WitcherSignsInterface* Interface = Cast<UUW_WitcherSignsInterface>(GameInterface);
		if (Interface != nullptr)
		{
			Interface->AddKill(EnemyClass);
		}
		
		FVector SpawnLocation{ GetActorLocation() };

		if (KilledByIgni == true)
		{
			UGameplayStatics::PlaySound2D(this, KilledByIgniSound);
			
			GetWorld()->SpawnActor<AActor>(
				BurnedRemainsActor, SpawnLocation,
				FRotator::ZeroRotator);
		}
		else
		{
			UGameplayStatics::PlaySound2D(this, DieSound);

			GetWorld()->SpawnActor<AActor>(
				RemainsActor, SpawnLocation,
				FRotator::ZeroRotator);
		}
		//UGameplayStatics::PlaySound2D(this, DieSound);
		Destroy();
	}
}

// Receive Heal (from beam)
void AEnemyActorParent::ReceiveHealing(float HealAmount)
{
	//UMaterialInstance->SetVectorParameterValue(FName(TEXT("MaskColor")), FLinearColor(0.f, 0.9, 0.02f, 1.f));
	//StaticMeshComponent->SetMaterial(0, EnemyDinamicMaterial);
	Health = FMath::Clamp(Health + HealAmount, 0.f, MaxHealth);
}

// Sets IsStopped status 
void AEnemyActorParent::SetIsStopped(bool Status)
{
	IsStopped = Status;
}

void AEnemyActorParent::SetIsAarded(bool Status)
{
	IsAarded = Status;
}

void AEnemyActorParent::SetKilledByIgni(bool Status)
{
	KilledByIgni = Status;
}

// Can be used by some types of enemies to move to arbitrary point
void AEnemyActorParent::MoveToPoint(FVector Point, float Time)
{
	FVector CurrentLocation = GetActorLocation();
	
	// calculating moving coordinates
	float Angle = FGenericPlatformMath::Atan2(CurrentLocation.Y - Point.Y, CurrentLocation.Z - Point.Z);
	float MoveAmount = Time * MovementSpeed;

	CurrentLocation.Y -= MoveAmount * FGenericPlatformMath::Sin(Angle);
	CurrentLocation.Z -= MoveAmount * FGenericPlatformMath::Cos(Angle);

	// calculatig distance to destination point
	float DistanceFromPoint = GetDistanceToPoint(Point);
	/*float DistanceFromPoint = FGenericPlatformMath::Sqrt(FGenericPlatformMath::Pow(CurrentLocation.Y - Point.Y, 2)
		+ FGenericPlatformMath::Pow(CurrentLocation.Z - Point.Z, 2));*/
	
	// moving only if further than 10 units from destination point
	if (DistanceFromPoint >= 5)
	{
		SetActorLocation(CurrentLocation);
	}
}

// Default enemy movement manager. Actor moves to player location which is
// origin of coordinates. Is overriden if needed
void AEnemyActorParent::MovementManager(float Time)
{
	FVector CurrentLocation = GetActorLocation();

	// calculating moving coordinates
	float Angle = FGenericPlatformMath::Atan2(CurrentLocation.Y, CurrentLocation.Z);
	float MoveAmount = Time * MovementSpeed;

	CurrentLocation.Y -= MoveAmount * FGenericPlatformMath::Sin(Angle);
	CurrentLocation.Z -= MoveAmount * FGenericPlatformMath::Cos(Angle);

	// calculatig distance to destination point
	float DistanceFromCenter = GetDistanceToPoint(FVector::ZeroVector);
	/*float DistanceFromCenter = FGenericPlatformMath::Sqrt(FGenericPlatformMath::Pow(CurrentLocation.Y, 2)
			+ FGenericPlatformMath::Pow(CurrentLocation.Z, 2));*/

	// if enemy reached player it destroys itself, otherwise continue moving
	if (DistanceFromCenter < DistanceFromCenterDeath)
	{
		Destroy();
		PlayerActor->ReceiveDamage(Damage);
		UUW_WitcherSignsInterface* Interface = Cast<UUW_WitcherSignsInterface>(GameInterface);
		if (Interface != nullptr)
		{
			Interface->AddNotKilledEnemy(EnemyClass);
		}
	}
	else
	{
		SetActorLocation(CurrentLocation);
	}
}

void AEnemyActorParent::MoveBack(float Time)
{
	FVector CurrentLocation = GetActorLocation();

	// calculating moving coordinates
	float Angle = FGenericPlatformMath::Atan2(CurrentLocation.Y, CurrentLocation.Z);
	float MoveAmount = Time * 500.f;

	CurrentLocation.Y += MoveAmount * FGenericPlatformMath::Sin(Angle);
	CurrentLocation.Z += MoveAmount * FGenericPlatformMath::Cos(Angle);

	SetActorLocation(CurrentLocation);
	
}

float AEnemyActorParent::GetDistanceToPoint(FVector Point)
{
	FVector CurrentLocation = GetActorLocation();
	// calculatig distance to destination point
	float DistanceFromPoint = FGenericPlatformMath::Sqrt(FGenericPlatformMath::Pow(CurrentLocation.Y - Point.Y, 2)
		+ FGenericPlatformMath::Pow(CurrentLocation.Z - Point.Z, 2));
	return DistanceFromPoint;
}

void AEnemyActorParent::PlayHitSound()
{
	if (IsAttacked && !GetWorldTimerManager().IsTimerActive(AttackedSoundTimer))
	{
		//TODO: make standalone function to reset timer (.clear) and call this function again
		UGameplayStatics::PlaySound2D(this, IsAttackedSound);
		GetWorldTimerManager().SetTimer(AttackedSoundTimer, this,
		&AEnemyActorParent::ResetHitSoundTimer, 1.f);
	}
}

void AEnemyActorParent::ResetHitSoundTimer()
{
	GetWorldTimerManager().ClearTimer(AttackedSoundTimer);
	PlayHitSound();
}
