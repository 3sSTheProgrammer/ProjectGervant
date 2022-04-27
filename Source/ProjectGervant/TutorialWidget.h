// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TutorialWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class PROJECTGERVANT_API UTutorialWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
		class UImage* HintImage;

public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Textures")
		UTexture2D* BeamsHint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Textures")
		UTexture2D* KvenHint;

public:

	void ShowHint(FString HintName);
};
