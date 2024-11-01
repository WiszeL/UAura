// Copyright, NyuAnca 2024

#include "Characters/BaseCharacter.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h" 

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// Weapon Mesh
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	WeaponMesh->SetupAttachment(GetMesh(), "WeaponHandSocket");
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// ===== Events ===== //

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// ===== Ability System ===== //

void ABaseCharacter::InitAbilityInfo()
{
	
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
