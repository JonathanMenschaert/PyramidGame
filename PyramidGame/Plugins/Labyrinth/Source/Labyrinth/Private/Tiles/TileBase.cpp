// Fill out your copyright notice in the Description page of Project Settings.


#include "Tiles/TileBase.h"

// Sets default values
ATileBase::ATileBase()
{
}

// Called when the game starts or when spawned
void ATileBase::BeginPlay()
{
	Super::BeginPlay();

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
	UpdateTileDirections(TileDirections);
}

void ATileBase::UpdateTileDirections_Implementation(const TArray<ETileDirection>& directions)
{
}

