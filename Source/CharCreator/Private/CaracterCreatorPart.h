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

	FCharacterCreatorPart()
	{
		BodyPart = EBodyPart::Head;
		Image = nullptr;
		Mesh = nullptr;
	}
};