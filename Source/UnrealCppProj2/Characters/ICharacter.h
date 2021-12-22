#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICharacter.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UICharacter : public UInterface
{
	GENERATED_BODY()
};

class UNREALCPPPROJ2_API IICharacter
{
	GENERATED_BODY()

public:
	virtual void ChangeColor(FLinearColor InColor) = 0;
};
