// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Game/GameDefinitions.h"
#include "PlayerStateLabyrinth.generated.h"

/**
 * 
 */
UCLASS()
class PYRAMIDGAME_API APlayerStateLabyrinth : public APlayerState
{
	GENERATED_BODY()

public:

	EPlayerType GetPlayerType();

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

protected:
	
	virtual void CopyProperties(APlayerState* playerState) override;

	UFUNCTION(BlueprintCallable)
	void SetPlayerType(EPlayerType playerType);

	UFUNCTION(BlueprintCallable)
	void SetPlayerName(FText playerName);

	UPROPERTY(Replicated, BlueprintReadOnly)
	EPlayerType PlayerType;

	UPROPERTY(Replicated, BlueprintReadOnly)
	FText PlayerName = FText::FromString("Player");
};
