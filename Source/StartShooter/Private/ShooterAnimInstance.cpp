// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"


void UShooterAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (nullptr == ShooterCharacter) {
		ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
	}
	if (ShooterCharacter != nullptr) {
		FVector Vel = ShooterCharacter->GetMovementComponent()->Velocity;
	    Vel.Z = 0.f;
		this->Speed = Vel.Size();

	  // is the character in the air ? 
		this->bIsInAir = ShooterCharacter->GetMovementComponent()->IsFalling();

	  // is the character acceleration ? 
		this->bIsAccelerating = ShooterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f;
	}
}

void UShooterAnimInstance::NativeInitializeAnimation()
{
    ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
	return;
}
