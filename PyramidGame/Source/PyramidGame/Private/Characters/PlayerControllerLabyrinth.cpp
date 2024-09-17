// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerControllerLabyrinth.h"

void APlayerControllerLabyrinth::SetActorInvisible(AActor* actorToHide)
{
	HiddenActors.Add(actorToHide);
}
