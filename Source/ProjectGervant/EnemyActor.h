// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Containers/UnrealString.h"
#include "BeamActor.h"


//#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor.generated.h"

UCLASS()
class PROJECTGERVANT_API AEnemyActor : public AActor
{
	GENERATED_BODY()

private:
	float Health{ 100 };
	bool IsAttacked{ false };
	//FString EnemyClass;
	//ABeamActor* BeamActor;

public:	

	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "EnemyClass"),
		Category = EnemyClass)
		FString EnemyClass;

	// Sets default values for this actor's properties
	AEnemyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, 
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex);

private:
	void ReceiveDamage(float DPS, float time);
};
