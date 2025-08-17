// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "PKAIController.generated.h"

class UBehaviorTreeComponent;

UCLASS()
class PROJECTK_API APKAIController : public AAIController
{
	GENERATED_BODY()

public:

	APKAIController();

protected:

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

};
