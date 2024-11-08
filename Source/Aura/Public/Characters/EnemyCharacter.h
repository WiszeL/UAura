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

protected:
	// ===== Ability System ===== //

	UPROPERTY(EditAnywhere)
	uint16 CombatLevel = 1;

public:
	FORCEINLINE virtual uint16 GetCombatLevel() const override
	{
		return CombatLevel;
	}
	
public:
	// ===== Highlight ===== //

	virtual void Highlight() override;
	virtual void UnHighlight() override;
};
