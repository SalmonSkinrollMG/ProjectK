// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.


#include "Input/PKInputConfig.h"

const UInputAction* UPKInputConfig::FindInputActionForTag(const FGameplayTag TagToFind) const
{
	for (auto [InputAction, InputTag] : InputActions)
	{
		if (InputAction && InputTag.MatchesTagExact(TagToFind))
		{
			return InputAction;
		}
	}
	UE_LOG(LogTemp , Error , TEXT("Cant Find Input Action for the Tag %s"),*TagToFind.ToString())
	return nullptr;
}
