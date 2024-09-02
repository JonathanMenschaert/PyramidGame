// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerStateLabyrinth.h"
#include "Net/UnrealNetwork.h"
#include "Net/Core/PushModel/PushModel.h"

EPlayerType APlayerStateLabyrinth::GetPlayerType()
{
	return PlayerType;
}

void APlayerStateLabyrinth::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams sharedParams;
	sharedParams.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(APlayerStateLabyrinth, PlayerType, sharedParams);
}

void APlayerStateLabyrinth::CopyProperties(APlayerState* playerState)
{

	Super::CopyProperties(playerState);

	APlayerStateLabyrinth* ps = Cast<APlayerStateLabyrinth>(playerState);
	if (IsValid(ps))
	{
		ps->PlayerType = PlayerType;
	}
}

void APlayerStateLabyrinth::SetPlayerType(EPlayerType playerType)
{
	PlayerType = playerType;
}

void APlayerStateLabyrinth::SetPushRepPlayerType(EPlayerType playerType)
{
	PlayerType = playerType;
	MARK_PROPERTY_DIRTY_FROM_NAME(APlayerStateLabyrinth, PlayerType, this);
}
