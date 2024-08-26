// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ETileDirection : uint8
{
	LEFT		UMETA(DisplayName = "Left"),
	RIGHT		UMETA(DisplayName = "Right"),
	UP			UMETA(DisplayName = "Up"),
	DOWN		UMETA(DisplayName = "Down")
};


UENUM(BlueprintType)
enum class ETileType : uint8
{
	VOID		UMETA(DisplayName = "Void"),
	HALLWAY		UMETA(DisplayName = "Hallway"),
	ROOM		UMETA(DisplayName = "Room")
};