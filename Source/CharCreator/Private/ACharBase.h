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
	void SetHairColor(USkeletalMeshComponent* MeshPart, const FLinearColor& Color);
	UFUNCTION(BlueprintCallable, Category = "Character Creator")
	void SetSkinColor(USkeletalMeshComponent* MeshPart, const FLinearColor& Color);
	UFUNCTION(BlueprintCallable, Category = "Character Creator")
	void SetEyeColor(USkeletalMeshComponent* MeshPart, const FLinearColor& Color);
	UFUNCTION(BlueprintCallable, Category = "Character Creator")
	void SetTopColor(USkeletalMeshComponent* MeshPart, const FLinearColor& Color);
	UFUNCTION(BlueprintCallable, Category = "Character Creator")
	void SetPantsColor(USkeletalMeshComponent* MeshPart, const FLinearColor& Color); 
	UFUNCTION(BlueprintCallable, Category = "Character Creator")
	void SetShoesColor(USkeletalMeshComponent* MeshPart, const FLinearColor& Color);

	UPROPERTY(EditAnywhere, Category = "Character")
	class UDataTable* DataTable;

	UFUNCTION(BlueprintCallable, Category = "Character Creator")
	void SetUpButtons(UDataTable* table, EBodyPart Parts, UPanelWidget* ParentBox);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterial* HairMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterial* SkinMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterial* EyeMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterial* TopMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterial* PantsMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterial* ShoesMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Character")
	USkeletalMeshComponent* HeadMeshComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Character")
	USkeletalMeshComponent* BodyMeshComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Character")
	USkeletalMeshComponent* LegsMeshComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Character")
	USkeletalMeshComponent* FeetMeshComp;
private:

	UPROPERTY(EditDefaultsOnly, Category= "Widgets")
	TSubclassOf<class UChangePartButton> ChangePartButtonClass;
	
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
