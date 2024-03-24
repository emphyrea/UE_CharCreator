// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"

#include "CaracterCreatorPart.generated.h"

UENUM(BlueprintType)
enum class EBodyPart : uint8
{
	None,
	Head,
	Body,
	Legs,
	Feet
};

/**
 * 
 */
USTRUCT(BlueprintType, Blueprintable)
struct FCharacterCreatorPart : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, Category = "BodyParts")
	EBodyPart BodyPart;
	
	UPROPERTY(EditAnywhere, Category = "BodyParts")
	class UTexture2D* Image;

	UPROPERTY(EditAnywhere, Category = "BodyParts")
	class USkeletalMesh* Mesh;
};