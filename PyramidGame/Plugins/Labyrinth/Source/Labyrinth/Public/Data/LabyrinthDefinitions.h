// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tiles/TileBase.h"
#include "LabyrinthDefinitions.generated.h"

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
};