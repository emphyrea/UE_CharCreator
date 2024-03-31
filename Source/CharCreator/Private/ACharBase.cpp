// Fill out your copyright notice in the Description page of Project Settings.


#include "ACharBase.h"

#include "Camera/CameraComponent.h"
#include "CaracterCreatorPart.h"
#include "ChangePartButton.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputSubsystemInterface.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AACharBase::AACharBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	cameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	viewCamera = CreateDefaultSubobject<UCameraComponent>("View Camera");
	
	BodyMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("BodyMesh");
	LegsMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("LegsMesh");
	FeetMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("FeetMesh");

	HeadMeshComp = this->GetMesh();
	BodyMeshComp->SetupAttachment(HeadMeshComp);
	LegsMeshComp->SetupAttachment(BodyMeshComp);
	FeetMeshComp->SetupAttachment(LegsMeshComp);
	
	cameraBoom->SetupAttachment(GetRootComponent());
	viewCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);

	cameraBoom->bUsePawnControlRotation = true;
	cameraBoom->TargetArmLength = 300.f;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(1080.f);
	GetCharacterMovement()->JumpZVelocity = 600.f;

	
}

// Called when the game starts or when spawned
void AACharBase::BeginPlay()
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
void AACharBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AACharBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		enhancedInputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &AACharBase::Move);
		enhancedInputComponent->BindAction(jumpAction, ETriggerEvent::Started, this, &AACharBase::Jump);
		enhancedInputComponent->BindAction(jumpAction, ETriggerEvent::Completed, this, &AACharBase::Jump);
		enhancedInputComponent->BindAction(lookAction, ETriggerEvent::Triggered, this, &AACharBase::Look);
	}
}

void AACharBase::SwapHead(USkeletalMesh* MeshPart)
{
	if(MeshPart)
	{
		HeadMeshComp->SetSkeletalMesh(MeshPart,false);
	}
}

void AACharBase::SwapBody(USkeletalMesh* MeshPart)
{
	if(MeshPart)
	{
		BodyMeshComp->SetSkeletalMesh(MeshPart,false);
	}
}

void AACharBase::SwapLegs(USkeletalMesh* MeshPart)
{
	if(MeshPart)
	{
		LegsMeshComp->SetSkeletalMesh(MeshPart,false);
	}
}

void AACharBase::SwapFeet(USkeletalMesh* MeshPart)
{
	if(MeshPart)
	{
		FeetMeshComp->SetSkeletalMesh(MeshPart,false);
	}
}

void AACharBase::SetHairColor(USkeletalMeshComponent* MeshPart, const FLinearColor& Color)
{

	TArray<UMaterialInterface*> Mats = MeshPart->GetMaterials();
	UE_LOG(LogTemp, Warning, TEXT("Materials Gotten: %d"), Mats.Num());
	for(UMaterialInterface* mat : Mats)
	{
		if(mat == HairMaterial)
		{
			UMaterial* HairMat = mat->GetMaterial();
			UMaterialInstanceDynamic* dynamicHairMat = UMaterialInstanceDynamic::Create(HairMat, this);

			if(MeshPart->GetMaterialIndex("Hair"))
			{
				int index = MeshPart->GetMaterialIndex("Hair");
				MeshPart->SetMaterial(index, dynamicHairMat);
			}
			dynamicHairMat->SetVectorParameterValue(TEXT("Color"), Color);
			dynamicHairMat = nullptr;
		}
	}
}

void AACharBase::SetSkinColor(USkeletalMeshComponent* MeshPart, const FLinearColor& Color)
{
	
	TArray<UMaterialInterface*> MatInterfaces = MeshPart->GetMaterials();
	//UE_LOG(LogTemp, Warning, TEXT("Materials Gotten Skin: %d"), MatInterfaces.Num());
	for(UMaterialInterface* matInterface : MatInterfaces)
	{
		UMaterial* mat = matInterface->GetBaseMaterial();
		UE_LOG(LogTemp, Warning, TEXT("Material mat: %s"), *mat->GetName());

		if(mat == SkinMaterial)
		{
			/*UE_LOG(LogTemp, Warning, TEXT("got skin main"));
			UMaterialInstanceDynamic* dynamicSkinMat = UMaterialInstanceDynamic::Create(mat, this);
			if(MeshPart->GetMaterialIndex("Skin"))
			{
				
			}*/
			int index = MeshPart->GetMaterialIndex("Skin");
			UMaterialInstanceDynamic* dynamicSkinMat = UMaterialInstanceDynamic::Create(SkinMaterial, this);
			MeshPart->SetMaterial(index, dynamicSkinMat);
			dynamicSkinMat->SetVectorParameterValue(TEXT("Color"), Color);
			dynamicSkinMat = nullptr;
		}
	}
	
}

void AACharBase::SetEyeColor(USkeletalMeshComponent* MeshPart, const FLinearColor& Color)
{
	
	TArray<UMaterialInterface*> Mats = MeshPart->GetMaterials();

	for(UMaterialInterface* mat : Mats)
	{

		if(mat == EyeMaterial)
		{
			UMaterial* EyeMat = mat->GetMaterial();
			UMaterialInstanceDynamic* dynamicEyeMat = UMaterialInstanceDynamic::Create(EyeMat, this);

			if(MeshPart->GetMaterialIndex("Eye"))
			{
				int index = MeshPart->GetMaterialIndex("Eye");
				MeshPart->SetMaterial(index, dynamicEyeMat);
			}
			dynamicEyeMat->SetVectorParameterValue(TEXT("Color"), Color);
			dynamicEyeMat = nullptr;
		}
	}
}

void AACharBase::SetTopColor(USkeletalMeshComponent* MeshPart, const FLinearColor& Color)
{
	
	TArray<UMaterialInterface*> Mats = MeshPart->GetMaterials();
	for(UMaterialInterface* mat : Mats)
	{
		if(mat == TopMaterial)
		{
			/*UE_LOG(LogTemp, Warning, TEXT("got skin main"));
			UMaterialInstanceDynamic* dynamicSkinMat = UMaterialInstanceDynamic::Create(mat, this);
			if(MeshPart->GetMaterialIndex("Skin"))
			{
				
			}*/

			//UE_LOG(LogTemp, Warning, TEXT("Set material: %s"), *MeshPart->GetMaterial(index)->GetName());
			UMaterialInstanceDynamic* dynamicTopMat = UMaterialInstanceDynamic::Create(TopMaterial, this);
			if(MeshPart->GetMaterialIndex("Top"))
			{
				int index = MeshPart->GetMaterialIndex("Top");
				MeshPart->SetMaterial(index, dynamicTopMat);
			}
			
			dynamicTopMat->SetVectorParameterValue(TEXT("Color"), Color);
			dynamicTopMat = nullptr;
		}
	}
}

void AACharBase::SetPantsColor(USkeletalMeshComponent* MeshPart, const FLinearColor& Color)
{
	
	TArray<UMaterialInterface*> Mats = MeshPart->GetMaterials();
	for(UMaterialInterface* mat : Mats)
	{
		if(mat == PantsMaterial)
		{
			/*UE_LOG(LogTemp, Warning, TEXT("got skin main"));
			UMaterialInstanceDynamic* dynamicSkinMat = UMaterialInstanceDynamic::Create(mat, this);
			if(MeshPart->GetMaterialIndex("Skin"))
			{
				
			}*/
			//UE_LOG(LogTemp, Warning, TEXT("Set material: %s"), *MeshPart->GetMaterial(index)->GetName());
			UMaterialInstanceDynamic* dynamicPantsMat = UMaterialInstanceDynamic::Create(PantsMaterial, this);
			if(MeshPart->GetMaterialIndex("Pants"))
			{
				int index = MeshPart->GetMaterialIndex("Pants");
				MeshPart->SetMaterial(index, dynamicPantsMat);
			}
			dynamicPantsMat->SetVectorParameterValue(TEXT("Color"), Color);
			dynamicPantsMat = nullptr;
		}
	}
}

void AACharBase::SetShoesColor(USkeletalMeshComponent* MeshPart, const FLinearColor& Color)
{
	
	TArray<UMaterialInterface*> Mats = MeshPart->GetMaterials();
	for(UMaterialInterface* mat : Mats)
	{
		if(mat == ShoesMaterial)
		{
			/*UE_LOG(LogTemp, Warning, TEXT("got skin main"));
			UMaterialInstanceDynamic* dynamicSkinMat = UMaterialInstanceDynamic::Create(mat, this);
			if(MeshPart->GetMaterialIndex("Skin"))
			{
				
			}*/
			//UE_LOG(LogTemp, Warning, TEXT("Set material: %s"), *MeshPart->GetMaterial(index)->GetName());
			UMaterialInstanceDynamic* dynamicShoesMat = UMaterialInstanceDynamic::Create(ShoesMaterial, this);
			if(MeshPart->GetMaterialIndex("Shoes"))
			{
				int index = MeshPart->GetMaterialIndex("Shoes");
				MeshPart->SetMaterial(index, dynamicShoesMat);
			}
			dynamicShoesMat->SetVectorParameterValue(TEXT("Color"), Color);
			dynamicShoesMat = nullptr;
		}
	}
}

void AACharBase::SetUpButtons(UDataTable* table,EBodyPart Parts, UPanelWidget* ParentBox)
{
	TArray<FName> RowNames = table->GetRowNames();
	for (FName RowName : RowNames)
	{
		EBodyPart RowPart = table->FindRow<FCharacterCreatorPart>(RowName, "")->BodyPart;
		UTexture2D* Image = table->FindRow<FCharacterCreatorPart>(RowName, "")->Image;
		USkeletalMesh* ChosenMesh = table->FindRow<FCharacterCreatorPart>(RowName, "")->Mesh;
		
		if(RowPart == Parts)
		{
			UChangePartButton* WidgetPartButtonTemplate = CreateWidget<UChangePartButton>(GetWorld(), ChangePartButtonClass);
			//WidgetPartButtonTemplate->OwningCharacter = this;
			WidgetPartButtonTemplate->SetPart(RowPart);
			WidgetPartButtonTemplate->SetImage(Image);
			WidgetPartButtonTemplate->SetMesh(ChosenMesh);
			ParentBox->AddChild(WidgetPartButtonTemplate);
		}
		continue;
	}
}


void AACharBase::Move(const FInputActionValue& InputValue)
{
	FVector2D input = InputValue.Get<FVector2D>();
	input.Normalize();

	AddMovementInput(input.Y * GetMoveFwdDir() + input.X * GetMoveRightDir());
}

void AACharBase::Look(const FInputActionValue& InputValue)
{
	FVector2D input = InputValue.Get<FVector2D>();
	AddControllerYawInput(input.X);
	AddControllerPitchInput(-input.Y);
}

FVector AACharBase::GetMoveFwdDir() const
{
	FVector CameraFwd = viewCamera->GetForwardVector();
	CameraFwd.Z = 0;
	return CameraFwd.GetSafeNormal();
}

FVector AACharBase::GetMoveRightDir() const
{
	return viewCamera->GetRightVector();
}


