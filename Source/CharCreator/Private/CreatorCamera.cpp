// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatorCamera.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystemInterface.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Pawn.h"

// Sets default values
ACreatorCamera::ACreatorCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	cameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	viewCamera = CreateDefaultSubobject<UCameraComponent>("View Camera");

	cameraBoom->SetupAttachment(GetRootComponent());
	viewCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);

	cameraBoom->bUsePawnControlRotation = true;
	cameraBoom->TargetArmLength = 800.f;
	bUseControllerRotationYaw = false;

}

// Called when the game starts or when spawned
void ACreatorCamera::BeginPlay()
{
	Super::BeginPlay();
	if(APlayerController* playerController = Cast<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
		{
			subsystem->AddMappingContext(mappingContext, 0);
		}
	}
}

// Called every frame
void ACreatorCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACreatorCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if(UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		enhancedInputComponent->BindAction(lookAction, ETriggerEvent::Triggered, this, &ACreatorCamera::Look);
		enhancedInputComponent->BindAction(zoomInAction, ETriggerEvent::Triggered, this, &ACreatorCamera::ZoomIn);
		enhancedInputComponent->BindAction(zoomOutAction, ETriggerEvent::Triggered, this, &ACreatorCamera::ZoomOut);
	}

}

void ACreatorCamera::Look(const FInputActionValue& InputValue)
{
	FVector2D input = InputValue.Get<FVector2D>();
	AddControllerYawInput(input.X);
	AddControllerPitchInput(-input.Y);
}

void ACreatorCamera::ZoomIn(const FInputActionValue& InputValue)
{
	float zoomLevel = 20.0f;
	float clampedZoom = FMathf::Clamp(zoomLevel, 150, 850);
	cameraBoom->TargetArmLength -= clampedZoom;
}

void ACreatorCamera::ZoomOut(const FInputActionValue& InputValue)
{
	float zoomLevel = 20.0f;
	float clampedZoom = FMathf::Clamp(zoomLevel, 150, 850);
	cameraBoom->TargetArmLength += clampedZoom;
}

