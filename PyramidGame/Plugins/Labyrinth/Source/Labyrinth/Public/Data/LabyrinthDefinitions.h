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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "esult")
	TArray<ATileBase*> GeneratedTiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Result")
	float SizeX = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Result")
	float SizeY = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Result")
	float TileSize = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Result")
	FVector CenterPoint{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Result")
	TArray<FTreasureZone> TreasureZones;
};