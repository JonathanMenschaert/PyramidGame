// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputConfig;

UCLASS()
class PYRAMIDGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent)
	void GetTraceStartPoint(FVector& forward, FVector& location);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void Move(const FInputActionValue& value);

	UFUNCTION()
	void Look(const FInputActionValue& value);

	UFUNCTION()
	void Interact(const FInputActionValue& value);

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Input")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Input")
	UInputConfig* InputConfig;	

};
