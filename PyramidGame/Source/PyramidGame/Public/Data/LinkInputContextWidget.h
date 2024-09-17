// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "LinkInputContextWidget.generated.h"


USTRUCT(BlueprintType, Blueprintable)
struct FClassArray
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSubclassOf<UUserWidget>> WidgetClasses;
};


UCLASS(BlueprintType, Blueprintable)
class PYRAMIDGAME_API ULinkInputContextWidget : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")

	TMap<UInputMappingContext*, FClassArray> LinkedWidgets;
};
