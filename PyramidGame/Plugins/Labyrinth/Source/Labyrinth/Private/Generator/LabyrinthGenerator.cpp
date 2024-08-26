// Fill out your copyright notice in the Description page of Project Settings.


#include "Generator/LabyrinthGenerator.h"
#include "Data/GeneratorData.h"
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

	UGeneratorData* generatorData = GeneratorData;

	//Set labyrinth size to the texture dimensions if a template is present
	bool isTemplatePresent = IsValid(generatorData->StartTemplate);
	if (isTemplatePresent)
	{
		generatorData->SizeX = generatorData->StartTemplate->GetSizeX();
		generatorData->SizeY = generatorData->StartTemplate->GetSizeY();
	}

	int amountOfTiles = generatorData->SizeX * generatorData->SizeY;
	if (amountOfTiles <= 0)
	{
		UE_LOG(LogLabyrinth, Error, TEXT("Labyrinth contains a dimension with incorrect size!"));
		return;
	}
	Tiles.Reserve(amountOfTiles);

	if (!IsValid(generatorData->TileClass))
	{
		UE_LOG(LogLabyrinth, Error, TEXT("No Tile class is set in the generator data!"));
		return;
	}

	for (int i{ 0 }; i < amountOfTiles; ++i)
	{
		Tiles.Add(NewObject<ATileBase>(this, generatorData->TileClass));
	}

	if (isTemplatePresent)
	{
		PopulateFromImage(generatorData->StartTemplate, amountOfTiles);
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

	for (const FColor& pixel : imagePixels)
	{
		//FString colorStr = FString::FromInt(pixel.R) + " " + FString::FromInt(pixel.G) + " " + FString::FromInt(pixel.B) + " " + FString::FromInt(pixel.A);
		//UE_LOG(LogLabyrinth, Log, TEXT("Color: %s"), *colorStr);
	}
}

