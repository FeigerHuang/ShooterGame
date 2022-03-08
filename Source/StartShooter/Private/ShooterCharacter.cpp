// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"


// Sets default values
AShooterCharacter::AShooterCharacter()
	: BaseTurnRate(45.f), BaseLoopUpRate(45.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("FollowSpringArm"));
	SpringArmComp->SetupAttachment(GetRootComponent());
	SpringArmComp->TargetArmLength = 300.f;
	SpringArmComp->bUsePawnControlRotation = true;
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AShooterCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis("TurnAround", this, &AShooterCharacter::TurnAtRate);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AShooterCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &AShooterCharacter::StopJumping);
}

void AShooterCharacter::MoveForward(float value)
{
	if (value != 0.0f && GetMovementComponent() != nullptr) {
		const FRotator Rotation = GetController()->GetControlRotation();
		const FVector Direction = FRotationMatrix(FRotator(0, Rotation.Yaw, 0)).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}	
}

void AShooterCharacter::MoveRight(float value)
{
	if (value != 0.0f && GetMovementComponent() != nullptr) {
		const FRotator Rotation = GetController()->GetControlRotation();
		const FVector Direction = FRotationMatrix(FRotator(0, Rotation.Yaw,0)).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, value);
	}
}

void AShooterCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}
void AShooterCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLoopUpRate * GetWorld()->GetDeltaSeconds());
}

