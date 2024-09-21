// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "InputConfig.generated.h"

/**
 * 
 */
UCLASS()
class PYRAMIDGAME_API UInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* InputMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Input")
	UInputAction* InputLook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Input")
	UInputAction* InputInteract;
};
