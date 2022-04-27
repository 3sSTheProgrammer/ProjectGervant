// Fill out your copyright notice in the Description page of Project Settings.

#include "TutorialWidget.h"
#include "Components/Image.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Styling/SlateBrush.h"

void UTutorialWidget::ShowHint(FString HintName)
{
	FSlateBrush Brush = UWidgetBlueprintLibrary::MakeBrushFromTexture(BeamsHint, 1920, 1080);
	HintImage->SetBrush(Brush);
}
