// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/Texture2D.h"
#include "Tiles/TileBase.h"
#include "GeneratorData.generated.h"

UCLASS(BlueprintType)
class LABYRINTH_API UGeneratorData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	UTexture2D* StartTemplate;

	UPROPERTY(EditAnywhere)
	int SizeX;

	UPROPERTY(EditAnywhere)
	int SizeY;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATileBase> TileClass;
};
