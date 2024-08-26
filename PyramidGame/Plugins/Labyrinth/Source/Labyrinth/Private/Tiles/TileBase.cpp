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

void ATileBase::AddAdjacentTile(ETileDirection tileDirection, TWeakPtr<ATileBase> tile)
{
	AdjacentTiles.Add(tileDirection, tile);
	TileDirections.AddUnique(tileDirection);
}

void ATileBase::SetTileType(ETileType tileType)
{
	TileType = tileType;
}

void ATileBase::UpdateTile()
{
}


