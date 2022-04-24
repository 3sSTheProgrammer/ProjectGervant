// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectGervant/PlayerActors/PlayerActor.h"
#include "MonsterEnemyWerewolf.h"

AMonsterEnemyWerewolf::AMonsterEnemyWerewolf()
{
	MaxHealth = 200;
	Health = MaxHealth;
	MovementSpeed = 150; //200
	Damage = 30;
	RegenPerSecond = 25;
	IsTransforming = false;

}

void AMonsterEnemyWerewolf::BeginPlay()
{
	Super::BeginPlay();
}

void AMonsterEnemyWerewolf::MovementManager(float Time)
{
	if (GetDistanceToPoint(FVector::ZeroVector) < 100)
	{
		PlayerActor->ReceiveDamage(Damage);
		Destroy();
	}

	if (!IsTransforming)
	{
		if (Health < MaxHealth - 50)
		{
			IsTransforming = true;
			MaxHealth -= 50;
			SetActorEnableCollision(false);
			EnemyDinamicMaterial->
				SetTextureParameterValue(FName(TEXT("InteractionMask")), UInteractionTexture);
			FTimerHandle Timer;
			GetWorldTimerManager().SetTimer(Timer, 
				this, &AMonsterEnemyWerewolf::ChangeForm, 2.f);
		}
		else
		{
			MoveToPoint(FVector::ZeroVector, Time);
		}
	}
	else
	{
		ReceiveHealing(RegenPerSecond * Time);
	}
}

void AMonsterEnemyWerewolf::ChangeForm()
{
	
	UTexture* Texture{ nullptr };
	FString NewEnemyClass;
	bool BufferStatus;

	if (EnemyClass == "Monster")
	{
		UE_LOG(LogTemp, Warning, TEXT("Changing form to human"));
		Texture = UHumanFormTexture;
		NewEnemyClass = "Human";
		MovementSpeed = 50;
	}
	else if (EnemyClass == "Human")
	{
		UE_LOG(LogTemp, Warning, TEXT("Changing form to monster"));
		Texture = UMonsterFormTexture;
		NewEnemyClass = "Monster";
		MovementSpeed = 150;
	}

	// switching IsAttacked and IsHealedStatuses
	BufferStatus = IsHealed;
	IsHealed = IsAttacked;
	IsAttacked = BufferStatus;
	if (Texture != nullptr) EnemyDinamicMaterial->
		SetTextureParameterValue(FName(TEXT("EnemyTexture")), Texture);
	EnemyClass = NewEnemyClass;
	SetBeamInteractionStatus("Heal", IsHealed);
	SetBeamInteractionStatus("Attack", IsAttacked);
	IsTransforming = false;
	SetActorEnableCollision(true);
}
