// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/GeneratorData.h"
#include "Data/LabyrinthDefinitions.h"
#include "LabyrinthGenerator.generated.h"

class UGeneratorData;
class ATileBase;
class UTexture2D;


UCLASS(BlueprintType)
class LABYRINTH_API ALabyrinthGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALabyrinthGenerator();

	UFUNCTION(BlueprintCallable)
	void Generate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "OnGeneratorFinished"))
	void OnGeneratorFinished(UPARAM(DisplayName = "Result") const FLabyrinthGeneratorResult& result);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Generator")
	UGeneratorData* GeneratorData;

private:

	void ResetGenerator();

	void PopulateFromImage(UTexture2D* image, int imagePixelAmount);

	void TrySetTileDirection(ATileBase* tile, int neighbourIdx, int x, int y, uint8 directionValue, ETileDirection direction);

	void AddTreasuresZones(int amountZones, int tileRadius, int treasuresPerZone);

	void AddTreasuresToZone(int zoneIdx, const FVector2f& tileCoordinates, int zoneRadius, int treasuresLeft);

	bool IsZoneCenterValid(const TArray<FVector2f>& zoneCenters, const FVector2f& newZoneCenter, float minSpacingSq);

	inline void IndexToCoordinate(int i, int& x, int& y) const;
	inline int CoordinateToIndex(int x, int y) const;
	inline bool IsValidIndex(int i, int coordX, int coordY) const;
	inline bool IsValidIndex(int i) const;
	inline bool IsValidDirection(uint8 directionValue, uint8 direction) const;

	UPROPERTY()
	TArray<ATileBase*> Tiles;

	UPROPERTY()
	TArray<FTreasureZone> TreasureZones;

};
