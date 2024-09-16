// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/TileData.h"
#include "TileBase.generated.h"

UCLASS(BlueprintType)
class LABYRINTH_API ATileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileBase();

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	void AddAdjacentTile(ETileDirection tileDirection, ATileBase* tile);
	void AddTileDirection(ETileDirection tileDirection);
	void SetTileType(ETileType tileType);
	void SetTileMetaData(uint8 data);
	void SetTileCoordinate(int x, int y);

	void UpdateTile();

	bool IsValidTreasureTile();
	void AddTreasure(int treasureIdx, int zoneIdx);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "OnTileDirectionsUpdated"))
	void UpdateTileDirections(UPARAM(DisplayName = "Directions") const TArray<ETileDirection>&directions, UPARAM(DisplayName = "Adjacent Tiles") const TMap<ETileDirection, ATileBase*>& adjacentTiles);
	void UpdateTileDirections_Implementation(const TArray<ETileDirection>& directions, const TMap<ETileDirection, ATileBase*>& adjacentTiles);

	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "OnTreasureAdded"))
	void OnTreasureAdded(UPARAM(DisplayName = "Zone Id") int zoneIdx, UPARAM(DisplayName = "Treasure Id") int treasureIdx);
	void OnTreasureAdded_Implementation(int zoneIdx, int treasureIdx);

	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "OnTileMetaData"))
	void OnTileMetaData(UPARAM(DisplayName = "Meta Data") const TArray<ETileMetaData>& metaData);
	void OnTileMetaData_Implementation(const TArray<ETileMetaData>& metaData);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<ETileDirection> GetTreasureDirections() const;

	UPROPERTY(Replicated, BlueprintReadOnly)
	ETileType TileType = ETileType::HALLWAY;

	UPROPERTY(BlueprintReadOnly)
	TArray<ETileDirection> TileDirections;

	UPROPERTY(BlueprintReadOnly)
	TArray<ETileMetaData> TileMetaData;

	UPROPERTY(Replicated, BlueprintReadOnly)
	bool HasTreasure;

	UPROPERTY(BlueprintReadOnly)
	int CoordinateX;

	UPROPERTY(BlueprintReadOnly)
	int CoordinateY;

private:

	UPROPERTY()
	TMap<ETileDirection, ATileBase*> AdjacentTiles;
	


};
