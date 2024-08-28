// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Labyrinth/LabyrinthHolder.h"

// Sets default values
ALabyrinthHolder::ALabyrinthHolder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALabyrinthHolder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALabyrinthHolder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

