// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/LabyrinthDefinitions.h"
#include "LabyrinthGameManager.generated.h"

UCLASS()
class PYRAMIDGAME_API ALabyrinthGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALabyrinthGameManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "Generator")
	FLabyrinthGeneratorResult GeneratorData;

};
