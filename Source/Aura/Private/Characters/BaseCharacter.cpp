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

void ABaseCharacter::ApplyEffectSelf(const TSubclassOf<UGameplayEffect>& EffectClass, const float Level) const
{
	if (!EffectClass) return;
	
	FGameplayEffectContextHandle EffectContext { AbilitySystemComp->MakeEffectContext() };
	EffectContext.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpec { AbilitySystemComp->MakeOutgoingSpec(EffectClass, Level, EffectContext)};
	AbilitySystemComp->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data);
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}
