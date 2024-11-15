// Copyright, RilAnca 2024

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Data/InputConfig.h"
#include "AuraInputComponent.generated.h"

UCLASS()
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityAction(const UInputConfig* Config, UserClass* Object, PressedFuncType PressedFunc,
		ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
	{
		check(Config);

		for (const auto& Cfg : Config->Configs)
		{
			if (!Cfg.InputTag.IsValid() || !Cfg.InputAction) continue;
			
			if (PressedFunc) BindAction(Cfg.InputAction, ETriggerEvent::Started, Object, PressedFunc, Cfg.InputTag);
			if (ReleasedFunc) BindAction(Cfg.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Cfg.InputTag);
			if (HeldFunc) BindAction(Cfg.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Cfg.InputTag);
		}
	}
};
