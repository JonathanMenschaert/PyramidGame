// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TreasureInfo.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PYRAMIDGAME_API UTreasureInfo : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Description;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterialInstance* TreasureImage;
	
};
