// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Characters/InputConfig.h"
#include "Components/SkeletalMeshComponent.h"
#include "Util/InteractionInterface.h"

#define ECC_TreasureObject ECollisionChannel::ECC_GameTraceChannel6
#define ECC_LabyrinthWall ECollisionChannel::ECC_GameTraceChannel7

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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

void APlayerCharacter::Move(const FInputActionValue& value)
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

void APlayerCharacter::Look(const FInputActionValue& value)
{
	if (Controller)
	{
		const FVector2D lookVal = value.Get<FVector2D>();

		if (lookVal.X != 0.f)
		{
			AddControllerYawInput(lookVal.X);
		}

		if (lookVal.Y != 0.f)
		{
			AddControllerPitchInput(-lookVal.Y);
		}
	}
}

void APlayerCharacter::Interact(const FInputActionValue& value)
{
	FHitResult outHit{};

	FVector forward;
	FVector start;
	GetTraceStartPoint(forward, start);

	FVector validationLocation = GetActorLocation();

	FCollisionQueryParams queryParams{};
	queryParams.AddIgnoredActor(this);
	queryParams.bTraceComplex = true;

	FCollisionObjectQueryParams objectParams{};
	objectParams.AddObjectTypesToQuery(ECC_TreasureObject);
	//objectParams.AddObjectTypesToQuery(ECC_LabyrinthWall);

	GetWorld()->LineTraceSingleByObjectType(outHit, start, start + 1000.f * forward, objectParams, queryParams);


	AActor* hitActor = outHit.GetActor();
	if (!IsValid(hitActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("No actor found!"));
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("Actor found!"));
	if (hitActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
	{
		IInteractionInterface::Execute_OnInteract(hitActor);
	}
	FVector test = validationLocation;
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* pPlayerController = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* inputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pPlayerController->GetLocalPlayer());
	inputSystem->ClearAllMappings();
	inputSystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* pEnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	pEnhancedInput->BindAction(InputConfig->InputLook, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
	pEnhancedInput->BindAction(InputConfig->InputMove, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
	pEnhancedInput->BindAction(InputConfig->InputInteract, ETriggerEvent::Started, this, &APlayerCharacter::Interact);
}

