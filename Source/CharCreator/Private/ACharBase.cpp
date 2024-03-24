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
	
	BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>("BodyMesh");
	LegsMesh = CreateDefaultSubobject<USkeletalMeshComponent>("LegsMesh");
	FeetMesh = CreateDefaultSubobject<USkeletalMeshComponent>("FeetMesh");

	HeadMesh = this->GetMesh();
	BodyMesh->SetupAttachment(HeadMesh);
	LegsMesh->SetupAttachment(BodyMesh);
	FeetMesh->SetupAttachment(LegsMesh);
	
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
		HeadMesh->SetSkeletalMesh(MeshPart, false);
	}
}

void AACharBase::SwapBody(USkeletalMesh* MeshPart)
{
	if(MeshPart)
	{
		BodyMesh->SetSkeletalMesh(MeshPart, false);
	}
}

void AACharBase::SwapLegs(USkeletalMesh* MeshPart)
{
	if(MeshPart)
	{
		LegsMesh->SetSkeletalMesh(MeshPart, false);
	}
}

void AACharBase::SwapFeet(USkeletalMesh* MeshPart)
{
	if(MeshPart)
	{
		FeetMesh->SetSkeletalMesh(MeshPart, false);
	}
}

void AACharBase::SetHairColor(USkeletalMesh* MeshPart, const FColor& Color)
{
}

void AACharBase::SetSkinColor(USkeletalMesh* MeshPart, const FColor& Color)
{
}

void AACharBase::SetEyeColor(USkeletalMesh* MeshPart, const FColor& Color)
{
}

void AACharBase::SetTopColor(USkeletalMesh* MeshPart, const FColor& Color)
{
}

void AACharBase::SetPantsColor(USkeletalMesh* MeshPart, const FColor& Color)
{
}

void AACharBase::SetShoesColor(USkeletalMesh* MeshPart, const FColor& Color)
{
}

void AACharBase::SetUpButtons(UDataTable* table,EBodyPart Parts, UPanelWidget* ParentBox)
{
	//look at wbp ui
	TArray<FName> RowNames = table->GetRowNames();
	for (FName RowName : RowNames)
	{
		EBodyPart RowPart = table->FindRow<FCharacterCreatorPart>(RowName, "")->BodyPart;
		UTexture2D* Image = table->FindRow<FCharacterCreatorPart>(RowName, "")->Image;
		USkeletalMesh* ChosenMesh = table->FindRow<FCharacterCreatorPart>(RowName, "")->Mesh;
		
		if(RowPart == Parts)
		{
			WidgetPartButtonTemplate->SetImage(Image);
			WidgetPartButtonTemplate->SetPart(RowPart);
			WidgetPartButtonTemplate->SetMesh(ChosenMesh);

			//CreateWidget(GetWorld(), WidgetPartButtonTemplate); //fix
			//ParentBox->AddChild(ChangePartButtonWidget);
		}
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


