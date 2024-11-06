// Copyright, NyuAnca 2024

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AbilityTypes.h"
#include "GameFramework/Actor.h"
#include "BaseEffector.generated.h"

UCLASS()
class AURA_API ABaseEffector : public AActor
{
	GENERATED_BODY()

public:
	ABaseEffector();

private:
	// ===== Gameplay Effect ===== //

	UPROPERTY(EditAnywhere, Category=GameplayEffect)
	float EffectLevel = 1.f;

	UPROPERTY(EditAnywhere, Category=GameplayEffect)
	bool bAppliesToEnemy = false;
	
	UPROPERTY(EditAnywhere, Category=GameplayEffect)
	bool bDestroyAfterApplyingEffect = false;
	
	UPROPERTY(EditAnywhere, Category=GameplayEffect)
	TArray<FGameplayEffectData> AppliesGameplayEffects;

	TMultiMap<UAbilitySystemComponent*, FActiveEffectHandle> ActivesEffect;
	
	UFUNCTION(BlueprintCallable)
	void OnEffectBeginOverlap(AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	void OnEffectEndOverlap(AActor* OtherActor);
	
	void ApplyGameplayEffect(UAbilitySystemComponent* TargetAbility, const FGameplayEffectData& Effect, bool& bApplied);
};
