// Copyright, NyuAnca 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEffector.generated.h"

UCLASS()
class AURA_API ABaseEffector : public AActor
{
	GENERATED_BODY()

public:
	ABaseEffector();

	// ===== Events ===== //
	
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(AActor* Other);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* Other);
};
