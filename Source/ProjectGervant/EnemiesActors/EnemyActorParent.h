// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActorParent.generated.h"

class APlayerActor;
class USoundCue;

UCLASS()
class PROJECTGERVANT_API AEnemyActorParent : public AActor
{
	GENERATED_BODY()

protected:

	// Static mesh component saved for efficiency
	UStaticMeshComponent* StaticMeshComponent;
	
	// Maximum health that enemy can have
	// Should be defined in constructor
	float MaxHealth{ 100 };

	//Shows if the enemy is currently interacts with damaging beam
	bool IsAttacked{ false };
	
	//Shows if the enemy is currently interacts with healing beam
	bool IsHealed{ false };

	// If true, enemy doesnt move according to MovementManager
	bool IsStopped{ false };
	
	bool IsAarded{ false };

	bool KilledByIgni{ false };

	// Defines if the enemy is Human or Monster
	FString EnemyClass;

	// A player actor reference saved for efficiency 
	APlayerActor* PlayerActor;

	// Material of the actor which can be modified during runtime
	UMaterialInstanceDynamic* EnemyDinamicMaterial;

	TSubclassOf<class UUserWidget> GameInterfaceClass;

	UUserWidget* GameInterface;

	FTimerHandle AttackedSoundTimer;
public:

	UPROPERTY(EditAnywhere, Category = Parameters)
		float DistanceFromCenterDeath{ 150.f };

	UPROPERTY(EditAnywhere, Category = Parameters)
		float Damage;

	UPROPERTY(EditAnywhere, Category = Parameters)
		float Health;

	UPROPERTY(EditAnywhere, Category = Parameters)
		float MovementSpeed{ 100 };

	UPROPERTY(EditAnywhere, Category = Materials)
		TSubclassOf<AActor> RemainsActor;

	UPROPERTY(EditAnywhere, Category = Materials)
		TSubclassOf<AActor> BurnedRemainsActor;

	// Actor's material
	UPROPERTY(EditAnywhere, Category = Materials)
		UMaterialInterface* UEnemyMaterial;
	
	// Texture of mask to highlight enemy if it is damaged/healed 
	UPROPERTY(EditAnywhere, Category = Materials)
		UTexture* UInteractionTexture;

	// Default enemy texture
	UPROPERTY(EditAnywhere, Category = Materials)
		UTexture* UColorTexture;

	UPROPERTY(EditAnywhere, Category = Materials)
		UTexture* UEmptyTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* SpawnSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* IsAttackedSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* DieSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* KilledByIgniSound;

	// Sets default values for this actor's properties
	AEnemyActorParent();

	// returns a class of enemy
	FString GetEnemyClass();

	// Sets IsAttacked or IsHealed status based on Interaction parameter
	void SetBeamInteractionStatus(FString Interaction, bool Status);

	// Applies damage to enemy
	void ReceiveDamage(float DamageAmount);

	// Applies healing to enemy
	void ReceiveHealing(float HealAmount);

	// Sets IsStopped status
	void SetIsStopped(bool Status);

	void SetIsAarded(bool Status);

	void SetKilledByIgni(bool Status);
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// A function that forces enemy to go to a point
	// specified by a FVector
	virtual void MoveToPoint(FVector Point, float Time);

	// A function that defines enemy movement 
	// By default the enemy moves to player position
	virtual void MovementManager(float Time);

	void MoveBack(float Time);

	float GetDistanceToPoint(FVector Point);

	void PlayHitSound();

	void ResetHitSoundTimer();
};
