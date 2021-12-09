#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDoAction.generated.h"

UCLASS()
class UNREALCPPPROJ2_API ACDoAction : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDoAction();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UCStateComponent* State;

	UPROPERTY(BlueprintReadOnly)
		class UCStatusComponent* Status;

public:
	virtual void DoAction() {}
	virtual void Begin_DoAction() {}
	virtual void End_DoAction() {}
};
