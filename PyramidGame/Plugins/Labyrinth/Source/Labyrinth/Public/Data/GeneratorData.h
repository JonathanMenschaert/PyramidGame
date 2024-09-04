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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Generator")
	UTexture2D* StartTemplate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Generator")
	int SizeX;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Generator")
	int SizeY;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Generator")
	TSubclassOf<ATileBase> TileClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Generator")
	FVector2D StartTileCoordinate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Generator")
	float TileSize;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Generator")
	int AmountOfZones = 5;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Generator")
	int ZoneRadius = 2;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Generator")
	int TreasuresPerZone = 4;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Generator")
	float ZoneSpacingSq = 16.f;
};
