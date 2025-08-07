#pragma once
#include "GameplayEffectTypes.h"

#include "PKAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FPKGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()
private:
	
public:
	bool IsCriticalHit() const {return bIsCriticalHit;}

	void SetIsCriticalHit(bool bIsCritical){bIsCriticalHit = bIsCritical;}
	
	/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const
	{
		return FGameplayEffectContext::StaticStruct();
	}
	
	/** Custom serialization, subclasses must override this */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

protected:

	bool bIsCriticalHit = false;
};

template<>
struct TStructOpsTypeTraits< FPKGameplayEffectContext > : public TStructOpsTypeTraitsBase2< FPKGameplayEffectContext >
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};