// Fill out your copyright notice in the Description page of Project Settings.


#include "Generator/LabyrinthGenerator.h"
#include "Tiles/TileBase.h"
#include "Labyrinth.h"

// Sets default values
ALabyrinthGenerator::ALabyrinthGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ALabyrinthGenerator::Generate()
{
	if (!IsValid(GeneratorData))
	{
		UE_LOG(LogLabyrinth, Error, TEXT("No Generator Data set!"));
		return;
	}

	ResetGenerator();

	//Set labyrinth size to the texture dimensions if a template is present
	bool isTemplatePresent = IsValid(GeneratorData->StartTemplate);
	if (isTemplatePresent)
	{
		GeneratorData->SizeX = GeneratorData->StartTemplate->GetSizeX();
		GeneratorData->SizeY = GeneratorData->StartTemplate->GetSizeY();
	}

	int amountOfTiles = GeneratorData->SizeX * GeneratorData->SizeY;
	if (amountOfTiles <= 0)
	{
		UE_LOG(LogLabyrinth, Error, TEXT("Labyrinth contains a dimension with incorrect size!"));
		return;
	}
	Tiles.Reserve(amountOfTiles);

	if (!IsValid(GeneratorData->TileClass))
	{
		UE_LOG(LogLabyrinth, Error, TEXT("No Tile class is set in the generator data!"));
		return;
	}

	for (int i{ 0 }; i < amountOfTiles; ++i)
	{
		Tiles.Add(GetWorld()->SpawnActor<ATileBase>(GeneratorData->TileClass, GetActorTransform()));
	}

	if (isTemplatePresent)
	{
		PopulateFromImage(GeneratorData->StartTemplate, amountOfTiles);
	}
	else
	{
		UE_LOG(LogLabyrinth, Warning, TEXT("Random generation not implemented yet!"));
	}

	AddTreasuresZones(AmountOfZones, ZoneRadius, TreasuresPerZone);

	FLabyrinthGeneratorResult result{};
	result.GeneratedTiles = Tiles;
	result.SizeX = GeneratorData->SizeX;
	result.SizeY = GeneratorData->SizeY;
	result.TileSize = GeneratorData->TileSize;
	result.CenterPoint = GetActorLocation() + FVector{ 
		GeneratorData->SizeX * GeneratorData->TileSize * 0.5f, 
		GeneratorData->SizeY * GeneratorData->TileSize * 0.5f, 
		0.f 
	};
	result.TreasureZones = TreasureZones;

	OnGeneratorFinished(result);
}

// Called when the game starts or when spawned
void ALabyrinthGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALabyrinthGenerator::OnGeneratorFinished_Implementation(const FLabyrinthGeneratorResult& result)
{
}

void ALabyrinthGenerator::ResetGenerator()
{
	for (ATileBase* tile : Tiles)
	{
		tile->Destroy();
	}
	Tiles.Empty();
}

void ALabyrinthGenerator::PopulateFromImage(UTexture2D* image, int imagePixelAmount)
{
	image->UpdateResource();
	const FTexturePlatformData* platformData = image->GetPlatformData();
	const FByteBulkData textureData = platformData->Mips[0].BulkData;

	TArray<FColor> imagePixels;
	
	imagePixels.AddDefaulted(imagePixelAmount);
	const FColor* pixelData = static_cast<const FColor*>(textureData.LockReadOnly());	
	FMemory::Memcpy(imagePixels.GetData(), pixelData, sizeof(FColor) * imagePixelAmount);
	textureData.Unlock();
	 
	const FVector generatorLocation = GetActorLocation();
	for (int i{ 0 }; i < imagePixelAmount; ++i)
	{
		int x = 0;
		int y = 0;

		IndexToCoordinate(i, x, y);
		ATileBase* tile = Tiles[i];
		tile->SetActorLocation(generatorLocation + FVector{ x * GeneratorData->TileSize, y * GeneratorData->TileSize, 0.f });

		TrySetTileDirection(tile, i - 1, x, y, imagePixels[i].R, ETileDirection::LEFT);
		TrySetTileDirection(tile, i + 1, x, y, imagePixels[i].R, ETileDirection::RIGHT);
		TrySetTileDirection(tile, i + GeneratorData->SizeY, x, y, imagePixels[i].R, ETileDirection::UP);
		TrySetTileDirection(tile, i - GeneratorData->SizeY, x, y, imagePixels[i].R, ETileDirection::DOWN);

		tile->UpdateTile();
	}
}

void ALabyrinthGenerator::TrySetTileDirection(ATileBase* tile, int neighbourIdx, int x, int y, uint8 directionValue, ETileDirection direction)
{
	if (IsValidIndex(neighbourIdx, x, y))
	{
		tile->AddAdjacentTile(direction, Tiles[neighbourIdx]);
	}

	if (IsValidDirection(directionValue, static_cast<uint8>(direction)))
	{
		tile->AddTileDirection(direction);
	}
}

void ALabyrinthGenerator::AddTreasuresZones(int amountZones, int zoneRadius, int treasuresPerZone)
{
	TArray<FVector2f> zoneCenters;

	while (zoneCenters.Num() < amountZones)
	{
		int randIdx = FMath::RandRange(0, Tiles.Num());
		int x{};
		int y{};
		IndexToCoordinate(randIdx, x, y);

		if (FVector2f newCenter{ static_cast<float>(x), static_cast<float>(y) }; IsZoneCenterValid(zoneCenters, newCenter, 16.f))
		{
			zoneCenters.Add(newCenter);
		}

	}

	TreasureZones.Empty();

	for (int treasureZoneIdx{}; treasureZoneIdx < amountZones; ++treasureZoneIdx)
	{
		TreasureZones.Add(FTreasureZone{});
		AddTreasuresToZone(treasureZoneIdx, zoneCenters[treasureZoneIdx], zoneRadius, treasuresPerZone);
	}
}

void ALabyrinthGenerator::AddTreasuresToZone(int zoneIdx, const FVector2f& tileCoordinates, int zoneRadius, int treasuresLeft)
{
	int x = FMath::RoundToInt(tileCoordinates.X);
	int y = FMath::RoundToInt(tileCoordinates.Y);

	int coordXMin = x - zoneRadius;
	int coordXMax = x + zoneRadius;
	int coordYMin = y - zoneRadius;
	int coordYMax = y + zoneRadius;

	int amountOfTiles = (coordXMax - coordXMin) * (coordYMax - coordYMin);

	for (int coordX{ coordXMin }; coordX < coordXMax; ++coordX)
	{
		for (int coordY{ coordYMin }; coordY < coordYMax; ++coordY)
		{
			int idx = CoordinateToIndex(coordX, coordY);
			if (!IsValidIndex(idx) || !Tiles[idx]->IsValidTreasureTile())
			{
				--amountOfTiles;
				continue;
			}

			float randNumber = FMath::RandRange(0.f, 1.f);
			float treasureChance = treasuresLeft / static_cast<float>(amountOfTiles);
			if (randNumber <= treasureChance)
			{
				Tiles[idx]->AddTreasure(treasuresLeft - 1, zoneIdx);
				TreasureZones[zoneIdx].Treasures.Add(Tiles[idx]);
				--treasuresLeft;
			}

			if (treasuresLeft <= 0)
			{
				return;
			}

			--amountOfTiles;
		}
	}
}

bool ALabyrinthGenerator::IsZoneCenterValid(const TArray<FVector2f>& zoneCenters, const FVector2f& newZoneCenter, float minSpacingSq)
{
	for (const FVector2f& zoneCenter : zoneCenters)
	{
		FVector2f difference = zoneCenter - newZoneCenter;

		if (difference.SquaredLength() < minSpacingSq)
		{
			return false;
		}
	}

	return true;
}

inline bool ALabyrinthGenerator::IsValidDirection(uint8 directionValue, uint8 direction) const
{
	return directionValue & direction;
}

inline void ALabyrinthGenerator::IndexToCoordinate(int i, int& x, int& y) const
{
	x = i / GeneratorData->SizeX;
	y = i % GeneratorData->SizeX;
}

inline int ALabyrinthGenerator::CoordinateToIndex(int x, int y) const
{
	return x * GeneratorData->SizeX + y;
}

inline bool ALabyrinthGenerator::IsValidIndex(int i, int coordX, int coordY) const
{
	int x = -1;
	int y = -1;

	IndexToCoordinate(i, x, y);

	return IsValidIndex(i) && (coordX == x || coordY == y);
}

inline bool ALabyrinthGenerator::IsValidIndex(int i) const
{
	return i >= 0 && i < Tiles.Num();
}

