// Copyright, RilAnca 2024

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class AURA_API ICombatInterface
{
	GENERATED_BODY()

public:
	virtual uint16 GetCombatLevel() const { return 0; }
	virtual FVector GetCombatSocketLocation() const { return FVector::ZeroVector; }
};
