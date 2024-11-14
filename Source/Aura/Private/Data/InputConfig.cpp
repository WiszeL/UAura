// Copyright, NyuAnca 2024

#include "Data/InputConfig.h"

UInputAction* UInputConfig::FindInputByTag(const FGameplayTag& Tag, bool bWarnNotFound)
{
	for (const auto& Cfg : Configs)
		if (Cfg.InputTag == Tag && Cfg.InputAction) return Cfg.InputAction;

	if (bWarnNotFound) UE_LOG(LogTemp, Error, TEXT("Input with tag [%s] is not found on %s!"), *Tag.ToString(), *GetNameSafe(this));
	
	return nullptr;
}
