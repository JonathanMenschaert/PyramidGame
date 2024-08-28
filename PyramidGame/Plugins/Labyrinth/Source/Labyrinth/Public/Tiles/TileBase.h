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

	void AddAdjacentTile(ETileDirection tileDirection, ATileBase* tile);
	void AddTileDirection(ETileDirection tileDirection);
	void SetTileType(ETileType tileType);

	void UpdateTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "OnTileDirectionsUpdated"))
	void UpdateTileDirections(UPARAM(DisplayName = "Directions") const TArray<ETileDirection>&directions, UPARAM(DisplayName = "Adjacent Tiles") const TMap<ETileDirection, ATileBase*>& adjacentTiles);

	UPROPERTY(BlueprintReadOnly)
	ETileType TileType = ETileType::HALLWAY;

private:

	UPROPERTY()
	TMap<ETileDirection, ATileBase*> AdjacentTiles;
	
	TArray<ETileDirection> TileDirections;

};
