// Copyright, NyuAnca 2024

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Interfaces/HighlightInterface.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class AURA_API AEnemyCharacter : public ABaseCharacter, public IHighlightInterface
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	// ===== Events ===== //
	
	virtual void BeginPlay() override;

public:
	// ===== Highlight ===== //

	virtual void Highlight() override;
	virtual void UnHighlight() override;
};
