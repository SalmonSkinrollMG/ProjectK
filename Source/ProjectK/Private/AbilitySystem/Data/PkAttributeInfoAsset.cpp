// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "AbilitySystem/Data/PkAttributeInfoAsset.h"

#include "GameplayTagsManager.h"

FPKAttributeinfo UPkAttributeInfoAsset::GetAttributesInfo(FGameplayTag Tag, bool bPrintNotFound)
{
	FPKAttributeinfo AttributeInfo;
	bool bFound = false;
	for (FPKAttributeinfo Info : AbilityInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(Tag))
		{
			bFound = true;
			AttributeInfo = Info;
			break;
		}
	}
	if (!bFound && bPrintNotFound)
	{
		UE_LOG(LogTemp , Error , TEXT("Attribute [%s] not found"),*Tag.ToString());
	}
	return AttributeInfo;
}
