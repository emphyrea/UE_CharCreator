// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"

#include "CaracterCreatorPart.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class EBodyPart : uint8
{
	Head,
	Body,
	Legs,
	Feet
};


UENUM(BlueprintType, Blueprintable)
enum class EBodyPartColor : uint8
{
	Hair,
	Skin,
	Eye,
	Top,
	Pants,
	Shoes
};

/**
 * 
 */
USTRUCT(BlueprintType, Blueprintable)
struct FCharacterCreatorPart : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "BodyParts")
	EBodyPart BodyPart;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyParts")
	class UTexture2D* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyParts")
	class USkeletalMesh* Mesh;
	
};

USTRUCT(BlueprintType, Blueprintable)
struct FCharacterCreatorColorPart : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "BodyParts")
	EBodyPartColor BodyPartToColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyParts")
	class USkeletalMesh* Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BodyPartsColor")
	 FLinearColor Color;
	
};