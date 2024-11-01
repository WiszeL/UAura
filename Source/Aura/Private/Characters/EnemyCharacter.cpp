// Copyright, NyuAnca 2024

#include "Characters/EnemyCharacter.h"

AEnemyCharacter::AEnemyCharacter()
{
	// Set the mesh to be responsive to Visibility Trace (for highlighting purpose)
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	// Set stencil for highlighting
	GetMesh()->SetCustomDepthStencilValue(255);
	WeaponMesh->SetCustomDepthStencilValue(255);
}

// ===== Events ===== //

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
