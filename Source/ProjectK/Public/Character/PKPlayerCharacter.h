// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PKCharacterBase.h"
#include "PKPlayerCharacter.generated.h"

UCLASS()
class PROJECTK_API APKPlayerCharacter : public APKCharacterBase
{
	GENERATED_BODY()

public:
	APKPlayerCharacter();
//PossessedBy is only called on server
	virtual  void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void InitAbilityActorInfo() override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere , Category = "Player Movement Tweak")
	FRotator PlayerRotationRate{FRotator::ZeroRotator};

	
};
