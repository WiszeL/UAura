// Copyright, NyuAnca 2024

#include "Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindByTag(const FGameplayTag& Tag, const bool bWarnNotFound) const
{
	for (const auto& Info : AttributeInfo)
		if (Info.AttributeTag == Tag) return Info;

	if (bWarnNotFound) UE_LOG(LogTemp, Error, TEXT("Info with tag [%s] is not found on %s!"), *Tag.ToString(), *GetNameSafe(this))

	return {};
}
