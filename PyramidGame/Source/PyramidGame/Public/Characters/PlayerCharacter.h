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
	void OnMove(const FInputActionValue& value);

	UFUNCTION()
	void OnLook(const FInputActionValue& value);

	UFUNCTION()
	void OnInteract(const FInputActionValue& value);

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteractionFailed(bool isServer);

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteractionSuccess(bool isServer, AActor* interactionActor);

	UFUNCTION(BlueprintNativeEvent)
	bool CanInteract();

	UFUNCTION()
	AActor* GetInteractionActor();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void SER_OnInteraction();

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteractionRepair();

	UFUNCTION(Server, Unreliable, BlueprintCallable)
	void SER_OnUpdateControlRotation(float pitchValue, float yawValue);

	UFUNCTION(NetMulticast, Unreliable, BlueprintCallable)
	void MUL_OnUpdateControlRotation(float pitchValue, float yawValue);

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Input")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Input")
	UInputConfig* InputConfig;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float YawValue = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	float YawMinMax = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float PitchValue = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	float PitchMinMax = 90.f;

	UPROPERTY()
	AActor* HoverActor;
};
