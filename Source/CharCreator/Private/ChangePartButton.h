// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CaracterCreatorPart.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "ChangePartButton.generated.h"

class AACharBase;
/**
 * 
 */
UCLASS()
class UChangePartButton : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(meta=(BindWidget), BlueprintReadWrite)
	UImage* WidgetImage;

	UPROPERTY(meta=(BindWidget), BlueprintReadWrite)
	UButton* PartButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Size = FVector2D(300.0f, 300.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* PartImage;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TSubclassOf<AACharBase*> OwningCharacter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBodyPart Part;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* Mesh;

	UFUNCTION(BlueprintCallable)
	void SetPart(EBodyPart ChosenPart) {Part = ChosenPart;};
	void SetImage(UTexture2D* Image) {PartImage = Image;};
	void SetMesh(USkeletalMesh* ChosenMesh) {Mesh = ChosenMesh;};
	//void SetCharacterRef(TSubclassOf<AACharBase*> ChosenCharacter) {OwningCharacter = ChosenCharacter;};
};
