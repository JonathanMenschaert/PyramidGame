// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerLabyrinth.generated.h"

UCLASS()
class PYRAMIDGAME_API APlayerControllerLabyrinth : public APlayerController
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintCallable)
	void SetActorInvisible(AActor* actorToHide);
		
	
};
