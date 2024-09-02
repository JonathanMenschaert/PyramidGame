// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/Character.h"
#include "GameModeLabyrinth.generated.h"


UCLASS()
class PYRAMIDGAME_API AGameModeLabyrinth : public AGameMode
{
	GENERATED_BODY()

public:
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Classes")
	TSubclassOf<ACharacter> MummyClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Classes")
	TSubclassOf<ACharacter> ExplorerClass;
};
