// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectGervant/ProjectGervant.h"
#include "Containers/UnrealString.h"
//#include "ProjectGervant/PlayerActors/BeamActor.h"
#include "ProjectGervant/PlayerActors/PlayerActor.h"

#include "GameFramework/Actor.h"
#include "EnemyActorParent.generated.h"

UCLASS()
class PROJECTGERVANT_API AEnemyActorParent : public AActor
{
	GENERATED_BODY()

protected:

	// Static mesh component saved for efficiency
	UStaticMeshComponent* StaticMeshComponent;

	//An enemy current health. Default value is 100
	float Health{ 100 };
	
	// Maximum health that enemy can have
	float MaxHealth;

	//Shows if the enemy is currently under beam attack
	bool IsAttacked{ false };
	
	//// A reference to beam actor which should apply damage to enemy
	//// TODO: MEDIUM PRIORITY refactor the methods so that another beam heals the enemy
	//ABeamActor* BeamActor;
	
	// Defines if the enemy is Human or Monster
	// TODO: LOW PRIORITY make an enum type EnemyClass
	FString EnemyClass;
	
	// Enemy movement speed. Default value is 100 units per second
	float MovementSpeed{ 100 };

	// A player actor reference saved for efficiency 
	APlayerActor* PlayerActor;

public:

	UPROPERTY(EditAnywhere,	Category = Materials)
		UMaterialInterface* UDefaultMaterial;
	UPROPERTY(EditAnywhere, Category = Materials)
		UMaterialInterface* UDamagedMaterial;

	// Sets default values for this actor's properties
	AEnemyActorParent();

	// returns a class of enemy
	FString GetEnemyClass();

	void SetIsAttacked(bool Status);

	// Applies damage to enemy
	void ReceiveDamage(float DamageAmount);

	// Applies healing to enemy
	void ReceiveHealing(float HealAmount);

protected:

	// Function that describes behaviour when overlap starts
	//UFUNCTION()
	//	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	//		class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	//		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//// Function that describes behaviour when overlap ends
	//UFUNCTION()
	//	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
	//		class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	//		int32 OtherBodyIndex);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

	//// Finds beam actor by tag that is afterwards stored in BeamActor field
	//void FindBeamActor(FName Tag);

	// A function that forces enemy to go to a point
	// specified by a FVector
	virtual void MoveToPoint(FVector Point, float Time);

	// A function that defines enemy movement 
	// By default the enemy moves to player position
	virtual void MovementManager(float Time);
};
