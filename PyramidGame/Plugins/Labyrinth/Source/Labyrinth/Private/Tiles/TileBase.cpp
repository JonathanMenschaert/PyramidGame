// Fill out your copyright notice in the Description page of Project Settings.


#include "Tiles/TileBase.h"

// Sets default values
ATileBase::ATileBase()
	: HasTreasure{false}
{
}

// Called when the game starts or when spawned
void ATileBase::BeginPlay()
{
	Super::BeginPlay();

}

TArray<ETileDirection> ATileBase::GetTreasureDirections() const
{
	TArray<ETileDirection> treasureDirections;

	for (ETileDirection direction : TEnumRange<ETileDirection>())
	{
		if (!TileDirections.Contains(direction))
		{
			treasureDirections.Add(direction);
		}
	}

	return treasureDirections;
}

void ATileBase::AddAdjacentTile(ETileDirection tileDirection, ATileBase* tile)
{
	AdjacentTiles.Add(tileDirection, tile);
	
}

void ATileBase::AddTileDirection(ETileDirection tileDirection)
{
	TileDirections.AddUnique(tileDirection);
}

void ATileBase::SetTileType(ETileType tileType)
{
	TileType = tileType;
}

void ATileBase::UpdateTile()
{
	UpdateTileDirections(TileDirections, AdjacentTiles);
}

bool ATileBase::IsValidTreasureTile()
{
	return !HasTreasure && TileType == ETileType::HALLWAY && TileDirections.Num() < 4;
}

void ATileBase::AddTreasure(int treasureIdx, int zoneIdx)
{
	HasTreasure = true;
	OnTreasureAdded(zoneIdx, treasureIdx);
}

void ATileBase::UpdateTileDirections_Implementation(const TArray<ETileDirection>& directions, const TMap<ETileDirection, ATileBase*>& adjacentTiles)
{
}

void ATileBase::OnTreasureAdded_Implementation(int zoneIdx, int treasureIdx)
{

}

