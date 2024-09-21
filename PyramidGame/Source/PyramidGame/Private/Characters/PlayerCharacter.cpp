// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Characters/InputConfig.h"
#include "Components/SkeletalMeshComponent.h"
#include "Util/InteractionInterface.h"

#define ECC_InteractionObject ECollisionChannel::ECC_GameTraceChannel6

// Sets default values
APlayerCharacter::APlayerCharacter()
{

	PrimaryActorTick.bCanEverTick = true;	

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	USkeletalMeshComponent* mesh = FindComponentByClass<USkeletalMeshComponent>();
	if (IsValid(mesh))
	{
		mesh->bOnlyAllowAutonomousTickPose = false;
	}
}

void APlayerCharacter::OnMove(const FInputActionValue& value)
{
	if (Controller)
	{
		const FVector2D moveVal = value.Get<FVector2D>();
		if (moveVal.X == 0.f && moveVal.Y == 0.f)
		{
			return;
		}
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation(0, rotation.Yaw, 0);

		const FVector directionY = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		const FVector directionX = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(directionY, moveVal.Y);
		AddMovementInput(directionX, moveVal.X);
	}
}

void APlayerCharacter::OnLook(const FInputActionValue& value)
{
	if (Controller)
	{
		const FVector2D lookVal = value.Get<FVector2D>();
		
		AddControllerYawInput(lookVal.X);
		PitchValue = FMath::Clamp(PitchValue - lookVal.Y, -PitchMinMax, PitchMinMax);
		YawValue = GetControlRotation().Yaw;
		SER_OnUpdateControlRotation(PitchValue, YawValue);
	}
}

void APlayerCharacter::OnInteract(const FInputActionValue& value)
{
	if (!CanInteract())
	{
		return;
	}

	SER_OnInteraction();
	
	AActor* interactionActor{ GetInteractionActor() };

	if (!IsValid(interactionActor))
	{
		OnInteractionFailed(false);
		return;
	}

	if (interactionActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
	{
		if (IInteractionInterface::Execute_AllowsInteraction(interactionActor))
		{
			IInteractionInterface::Execute_OnInteract(interactionActor);
			OnInteractionSuccess(false);
		}		
		else
		{
			OnInteractionFailed(false);
		}
	}	
}

bool APlayerCharacter::CanInteract_Implementation()
{
	return true;
}

AActor* APlayerCharacter::GetInteractionActor()
{
	FHitResult outHit{};

	FVector forward;
	FVector start;
	GetTraceStartPoint(forward, start);

	FCollisionQueryParams queryParams{};
	queryParams.AddIgnoredActor(this);
	queryParams.bTraceComplex = true;

	FCollisionObjectQueryParams objectParams{};
	objectParams.AddObjectTypesToQuery(ECC_InteractionObject);

	GetWorld()->LineTraceSingleByObjectType(outHit, start, start + 250.f * forward, objectParams, queryParams);
	
	return outHit.GetActor();
}

void APlayerCharacter::MUL_OnUpdateControlRotation_Implementation(float pitchValue, float yawValue)
{
	if (!IsLocallyControlled())
	{
		PitchValue = pitchValue;
		YawValue = yawValue;
	}
}

void APlayerCharacter::SER_OnUpdateControlRotation_Implementation(float pitchValue, float yawValue)
{
	MUL_OnUpdateControlRotation(pitchValue, yawValue);
}

void APlayerCharacter::SER_OnInteraction_Implementation()
{
	//Move this to seperate function
	AActor* interactionActor{ GetInteractionActor() };

	if (!IsValid(interactionActor))
	{
		OnInteractionFailed(true);
		return;
	}

	if (interactionActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
	{
		if (IInteractionInterface::Execute_AllowsInteraction(interactionActor))
		{
			IInteractionInterface::Execute_OnInteract(interactionActor);
			OnInteractionSuccess(true);
		}
		else
		{
			OnInteractionFailed(true);
		}
	}
	
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* pPlayerController = Cast<APlayerController>(GetController());

	UEnhancedInputComponent* pEnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	pEnhancedInput->BindAction(InputConfig->InputLook, ETriggerEvent::Triggered, this, &APlayerCharacter::OnLook);
	pEnhancedInput->BindAction(InputConfig->InputMove, ETriggerEvent::Triggered, this, &APlayerCharacter::OnMove);
	pEnhancedInput->BindAction(InputConfig->InputInteract, ETriggerEvent::Started, this, &APlayerCharacter::OnInteract);
}

