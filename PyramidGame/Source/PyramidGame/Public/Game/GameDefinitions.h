// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EPlayerType : uint8
{
	EXPLORER	UMETA(DisplayName = "Explorer"),
	MUMMY		UMETA(DisplayName = "Mummy")
};
