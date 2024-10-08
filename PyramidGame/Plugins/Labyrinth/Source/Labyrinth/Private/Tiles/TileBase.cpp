// Fill out your copyright notice in the Description page of Project Settings.


#include "Tiles/TileBase.h"
#include "Net/UnrealNetwork.h"
#include "Net/Core/PushModel/PushModel.h"

// Sets default values
ATileBase::ATileBase()
	: HasTreasure{false}
{
}

void ATileBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	FDoRepLifetimeParams sharedParams;
	sharedParams.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(ATileBase, TileType, sharedParams);
	DOREPLIFETIME_WITH_PARAMS_FAST(ATileBase, HasTreasure, sharedParams);

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
	MARK_PROPERTY_DIRTY_FROM_NAME(ATileBase, TileType, this);

}

void ATileBase::SetTileMetaData(uint8 data)
{
	TileMetaData.Empty();

	for (int meta{ 1 }; meta < 256; meta *= 2)
	{
		if (meta & data)
		{
			TileMetaData.Add(static_cast<ETileMetaData>(meta));
		}
	}

	OnTileMetaData(TileMetaData);
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
	MARK_PROPERTY_DIRTY_FROM_NAME(ATileBase, HasTreasure, this);
	OnTreasureAdded(zoneIdx, treasureIdx);
}

void ATileBase::UpdateTileDirections_Implementation(const TArray<ETileDirection>& directions, const TMap<ETileDirection, ATileBase*>& adjacentTiles)
{
}

void ATileBase::OnTreasureAdded_Implementation(int zoneIdx, int treasureIdx)
{

}

void ATileBase::OnTileMetaData_Implementation(const TArray<ETileMetaData>& metaData)
{

}

void ATileBase::SetTileCoordinate(int x, int y)
{
	CoordinateX = x;
	CoordinateY = y;
}

