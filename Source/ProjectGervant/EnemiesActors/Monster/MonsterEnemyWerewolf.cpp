// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterEnemyWerewolf.h"

AMonsterEnemyWerewolf::AMonsterEnemyWerewolf()
{
	MaxHealth = 200;
	Health = MaxHealth;
	MovementSpeed = 200; //200
	Damage = 30;

}

void AMonsterEnemyWerewolf::BeginPlay()
{
	Super::BeginPlay();
	HumanFormMaterial = UMaterialInstanceDynamic::Create(UHumanFormMaterial, this);
	HumanFormMaterial->SetTextureParameterValue(FName(TEXT("Mask")), UDefaultTexture);
	MonsterFormMaterial = UMaterialInstanceDynamic::Create(UDamagedMaterial, this);;
	MonsterFormMaterial->SetTextureParameterValue(FName(TEXT("Mask")), UDefaultTexture);

	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this, &AMonsterEnemyWerewolf::ChangeForm, 2.f);
}

void AMonsterEnemyWerewolf::MovementManager(float Time)
{
	/*if (Health < MaxHealth - 50)
	{
		ChangeForm();
	}*/
	
}

void AMonsterEnemyWerewolf::ChangeForm()
{
	UE_LOG(LogTemp, Warning, TEXT("Changing form"));
	UMaterialInstanceDynamic* Material{ nullptr };
	FString NewEnemyClass;
	int index;
	if (EnemyClass == "Monster")
	{
		Material = HumanFormMaterial;
		NewEnemyClass = "Human";
		index = 0;
	}
	else if (EnemyClass == "Human")
	{
		Material = MonsterFormMaterial;
		NewEnemyClass = "Monster";
		index = 1;
	}

	//StaticMeshComponent->SetMaterial(index, Material);
	//Material->SetTextureParameterValue(FName(TEXT("Mask")), UDefaultTexture);
	EnemyDinamicMaterial = Material;
	EnemyClass = NewEnemyClass;

	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this, &AMonsterEnemyWerewolf::ChangeForm, 2.f);
}
