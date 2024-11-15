// Copyright, RilAnca 2024

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AuraAbility.generated.h"

UCLASS()
class AURA_API UAuraAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	
	// ===== Gameplay Tag ===== //
	
	UPROPERTY(EditAnywhere, Category=Tags)
	FGameplayTag StartupInputTag;	
};
