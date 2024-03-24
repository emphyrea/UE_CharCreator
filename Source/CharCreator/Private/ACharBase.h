// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CaracterCreatorPart.h"
#include "ChangePartButton.h"
#include "Components/PanelWidget.h"
#include "ACharBase.generated.h"

UCLASS()
class AACharBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AACharBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	UChangePartButton* WidgetPartButtonTemplate;
	
private:
	//Character Customizer
	
	UFUNCTION(BlueprintCallable, Category= "Character Creator")
	void SwapHead(USkeletalMesh* MeshPart);
	UFUNCTION(BlueprintCallable, Category= "Character Creator")
	void SwapBody(USkeletalMesh* MeshPart);
	UFUNCTION(BlueprintCallable, Category= "Character Creator")
	void SwapLegs(USkeletalMesh* MeshPart);
	UFUNCTION(BlueprintCallable, Category= "Character Creator")
	void SwapFeet(USkeletalMesh* MeshPart);

	UFUNCTION(BlueprintCallable, Category = "Character Creator")
	void SetHairColor(USkeletalMesh* MeshPart, const FColor& Color);
	UFUNCTION(BlueprintCallable, Category = "Character Creator")
	void SetSkinColor(USkeletalMesh* MeshPart, const FColor& Color);
	UFUNCTION(BlueprintCallable, Category = "Character Creator")
	void SetEyeColor(USkeletalMesh* MeshPart, const FColor& Color);
	UFUNCTION(BlueprintCallable, Category = "Character Creator")
	void SetTopColor(USkeletalMesh* MeshPart, const FColor& Color);
	UFUNCTION(BlueprintCallable, Category = "Character Creator")
	void SetPantsColor(USkeletalMesh* MeshPart, const FColor& Color); 
	UFUNCTION(BlueprintCallable, Category = "Character Creator")
	void SetShoesColor(USkeletalMesh* MeshPart, const FColor& Color);

	UPROPERTY(EditAnywhere, Category = "Character")
	class UDataTable* DataTable;

	UFUNCTION(BlueprintCallable, Category = "Character Creator")
	void SetUpButtons(UDataTable* table, EBodyPart Parts, UPanelWidget* ParentBox);

public:
	UPROPERTY(EditAnywhere, Category= "Character")
	USkeletalMeshComponent* HeadMesh;
	UPROPERTY(EditAnywhere, Category= "Character")
	USkeletalMeshComponent* BodyMesh;
	UPROPERTY(EditAnywhere, Category= "Character")
	USkeletalMeshComponent* LegsMesh;
	UPROPERTY(EditAnywhere, Category= "Character")
	USkeletalMeshComponent* FeetMesh;
private:
	
	UPROPERTY(visibleAnywhere, Category = "View")
	class USpringArmComponent* cameraBoom;

	UPROPERTY(visibleAnywhere, Category = "View")
	class UCameraComponent* viewCamera;
	
	UPROPERTY(EditAnywhere, Category= "Input")
	UInputMappingContext* mappingContext;
	UPROPERTY(EditAnywhere, Category= "Input")
	UInputAction* moveAction;
	UPROPERTY(EditAnywhere, Category= "Input")
	UInputAction* jumpAction;
	UPROPERTY(EditAnywhere, Category= "Input")
	UInputAction* lookAction;

	UFUNCTION()
	void Move(const FInputActionValue& InputValue);
	void Look(const FInputActionValue& InputValue);
	FVector GetMoveFwdDir() const;
	FVector GetMoveRightDir() const;
};
