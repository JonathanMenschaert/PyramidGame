// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerStartLabyrinth.h"
#include "Components/CapsuleComponent.h"

APlayerStartLabyrinth::APlayerStartLabyrinth(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	GetCapsuleComponent()->SetMobility(EComponentMobility::Movable);
}
