// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputSubsystemInterface.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CreatorCamera.generated.h"

UCLASS()
class ACreatorCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACreatorCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(visibleAnywhere, Category = "View")
	class USpringArmComponent* cameraBoom;

	UPROPERTY(visibleAnywhere, Category = "View")
	class UCameraComponent* viewCamera;
	
	UPROPERTY(EditAnywhere, Category= "Input")
	UInputMappingContext* mappingContext;
	UPROPERTY(EditAnywhere, Category= "Input")
	UInputAction* zoomInAction;
	UPROPERTY(EditAnywhere, Category= "Input")
	UInputAction* zoomOutAction;
	UPROPERTY(EditAnywhere, Category= "Input")
	UInputAction* lookAction;

	UFUNCTION()
	void Look(const FInputActionValue& InputValue);
	void ZoomIn(const FInputActionValue& InputValue);
	void ZoomOut(const FInputActionValue& InputValue);
};
