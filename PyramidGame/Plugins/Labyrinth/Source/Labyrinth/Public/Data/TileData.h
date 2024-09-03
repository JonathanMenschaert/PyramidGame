// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ETileDirection : uint8
{
	NONE = 0	UMETA(DisplayName = "None"),
	LEFT = 1	UMETA(DisplayName = "Left"),
	RIGHT = 2	UMETA(DisplayName = "Right"),
	UP = 4		UMETA(DisplayName = "Up"),
	DOWN = 8	UMETA(DisplayName = "Down")
};
ENUM_RANGE_BY_VALUES(ETileDirection, ETileDirection::LEFT, ETileDirection::RIGHT, ETileDirection::UP, ETileDirection::DOWN)

UENUM(BlueprintType)
enum class ETileType : uint8
{
	NONE = 0	UMETA(Hidden),
	VOID = 1	UMETA(DisplayName = "Void"),
	HALLWAY = 2	UMETA(DisplayName = "Hallway"),
	ROOM = 4	UMETA(DisplayName = "Room")
};