// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tiles/TileBase.h"
#include "LabyrinthDefinitions.generated.h"

USTRUCT(BlueprintType)
struct FTreasureZone
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	TArray<ATileBase*> Treasures;
};

USTRUCT(Blueprintable, BlueprintType)
struct FLabyrinthGeneratorResult
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ATileBase*> GeneratedTiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SizeX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SizeY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TileSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector CenterPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FTreasureZone> TreasureZones;
};