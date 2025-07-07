// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PKCharacterBase.h"
#include "Interface/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "PKEnemeyCharacter.generated.h"


class UWidgetComponent;

UCLASS()
class PROJECTK_API APKEnemeyCharacter : public APKCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:

	APKEnemeyCharacter();

	UPROPERTY(BlueprintReadWrite, Category = "Enemy Visualization")
	bool bHighlighted = false;

	virtual void InitAbilityActorInfo() override;

	UFUNCTION()
	virtual int GetPlayerLevel() const override {return Level;}

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBarWidget;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthAttributeUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthAttributeUpdated;

protected:

	virtual void BeginPlay() override;

//Enemy interface for higlightling the enemy.
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	UPROPERTY(EditAnywhere , BlueprintReadOnly ,Category = "Enemy Attribute")
	int Level = 0;
};
