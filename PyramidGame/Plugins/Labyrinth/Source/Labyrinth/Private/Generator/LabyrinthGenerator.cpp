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
}

// Called when the game starts or when spawned
void ALabyrinthGenerator::BeginPlay()
{
	Super::BeginPlay();
	
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

inline bool ALabyrinthGenerator::IsValidDirection(uint8 directionValue, uint8 direction) const
{
	return directionValue & direction;
}

inline void ALabyrinthGenerator::IndexToCoordinate(int i, int& x, int& y) const
{
	x = i / GeneratorData->SizeX;
	y = i % GeneratorData->SizeX;
}

inline bool ALabyrinthGenerator::IsValidIndex(int i, int coordX, int coordY) const
{
	int x = -1;
	int y = -1;

	IndexToCoordinate(i, x, y);

	return i >= 0 && i < Tiles.Num() && (coordX == x || coordY == y);
}

