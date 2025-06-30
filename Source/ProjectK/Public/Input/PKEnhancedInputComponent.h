// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "PKInputConfig.h"
#include "PKEnhancedInputComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTK_API UPKEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserClass , typename PressedFuncType, typename ReleaseFuncType, typename HeldFuncType >
	void BindAbilityActions(UPKInputConfig* InputConfig , UserClass* Object ,
		PressedFuncType PressedFunc, ReleaseFuncType ReleaseFunc, HeldFuncType HoldFunc);
};



template <class UserClass, typename PressedFuncType, typename ReleaseFuncType, typename HoldFuncType>
void UPKEnhancedInputComponent::BindAbilityActions(UPKInputConfig* InputConfig, UserClass* Object,
	PressedFuncType PressedFunc, ReleaseFuncType ReleaseFunc, HoldFuncType HeldFunc)
{
	checkf(InputConfig,TEXT("DefaultPrimaryAttribute is not a valid APKCharacterBase"));

	for (auto [InputAction, InputTag] : InputConfig->InputActions)
	{
		if (InputAction && InputTag.IsValid())
		{
			/*
			 *Arguments send after the Func will be sent to the function as parameters
			 *Eg BindAction(InputAction, ETriggerEvent::Triggered, Object, HoldFunc, InputTag);
			 *Here, Hold function should have a parameter of type(InputTag) ie) FGameplayTag;
			 */
			if (PressedFunc)
			{
				BindAction(InputAction, ETriggerEvent::Started, Object, PressedFunc, InputTag);
			}
			if (ReleaseFunc)
			{
				BindAction(InputAction , ETriggerEvent::Completed, Object, ReleaseFunc, InputTag);
			}
			if (HeldFunc)
			{
				BindAction(InputAction, ETriggerEvent::Triggered, Object, HeldFunc, InputTag);
			}
		}
	}
}
