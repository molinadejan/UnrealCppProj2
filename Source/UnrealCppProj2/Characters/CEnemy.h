#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Characters/ICharacter.h"
#include "Components/CStateComponent.h"
#include "CEnemy.generated.h"

UCLASS()
class UNREALCPPPROJ2_API ACEnemy : public ACharacter, public IICharacter
{
	GENERATED_BODY()

public:
	ACEnemy();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;

public:
	virtual void ChangeColor(FLinearColor InColor) override;

	virtual float TakeDamage(float Damage, FDamageEvent const& FDamageEvent, 
		AController* EventInstigator, AActor* DamageCauser) override;

private:
	UPROPERTY(EditAnywhere, Category = "Hitted")
		float LaunchAmount = 100.0f;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UCActionComponent* Action;

	UPROPERTY(VisibleDefaultsOnly)
		class UCMontagesComponent* Montages;

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* NameWidget;

	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* HealthWidget;

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNextType);

	UFUNCTION()
		void RestoreColor();

private:
	class AController* DamageInstigator;
	float DamageValue;

private:
	void Hitted();
};
