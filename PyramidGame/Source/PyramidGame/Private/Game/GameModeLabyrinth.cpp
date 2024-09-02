// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameModeLabyrinth.h"
#include "Characters/PlayerControllerLabyrinth.h"
#include "Characters/PlayerStateLabyrinth.h"
#include "Game/GameDefinitions.h"

UClass* AGameModeLabyrinth::GetDefaultPawnClassForController_Implementation(AController* inController)
{
	APlayerControllerLabyrinth* pc = Cast<APlayerControllerLabyrinth>(inController);
	if (!IsValid(pc))
	{
		return DefaultPawnClass;
	}

	APlayerStateLabyrinth* ps = Cast < APlayerStateLabyrinth>(pc->PlayerState);
	if (!IsValid(ps))
	{
		return DefaultPawnClass;
	}

	switch (ps->GetPlayerType())
	{
	case EPlayerType::EXPLORER:
		return ExplorerClass;
		break;
	case EPlayerType::MUMMY:
		return MummyClass;
		break;	
	}
	
	return DefaultPawnClass;
}
