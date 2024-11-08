// Copyright, NyuAnca 2024

#include "Characters/EnemyCharacter.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AEnemyCharacter::AEnemyCharacter()
{
	// Set the mesh to be responsive to Visibility Trace (for highlighting purpose)
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	// Set stencil for highlighting
	GetMesh()->SetCustomDepthStencilValue(255);
	WeaponMesh->SetCustomDepthStencilValue(255);

	// Ability System
	AbilitySystemComp = CreateDefaultSubobject<UAuraAbilitySystemComponent>("Ability System");
	AbilitySystemComp->SetIsReplicated(true);
	AbilitySystemComp->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("Attribute Set");

	// Tags
	Tags.Add("Enemy");
}

// ===== Events ===== //

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Prepare Ability System
	AbilitySystemComp->InitAbilityActorInfo(this, this);
	ApplyEffectSelf(DefaultPrimaryAttributes.LoadSynchronous());
}

// ===== Highlight ===== //

void AEnemyCharacter::Highlight()
{
	GetMesh()->SetRenderCustomDepth(true);
	WeaponMesh->SetRenderCustomDepth(true);
}

void AEnemyCharacter::UnHighlight()
{
	GetMesh()->SetRenderCustomDepth(false);
	WeaponMesh->SetRenderCustomDepth(false);
}
