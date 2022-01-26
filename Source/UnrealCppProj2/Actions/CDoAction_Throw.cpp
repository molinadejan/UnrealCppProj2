#include "CDoAction_Throw.h"

#include "CThrow.h"
#include "Global.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Actions/CAim.h"

void ACDoAction_Throw::BeginPlay()
{
	Super::BeginPlay();

	Aim = NewObject<UCAim>();
	Aim->BeginPlay(OwnerCharacter);
	//Aim->ConditionalFinishDestroy();
}

void ACDoAction_Throw::DoAction()
{
	Super::DoAction();

	if (Aim->IsAvailable())
		CheckFalse(Aim->InZoom());

	CheckFalse(State->IsIdleMode());
	State->SetActionMode();
	
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage,
		Datas[0].PlayRatio,
		Datas[0].StartSection);

	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Throw::Begin_DoAction()
{
	FVector location = OwnerCharacter->GetMesh()->GetSocketLocation(
		"Hand_Throw_Projectile");

	FRotator rotator = OwnerCharacter->GetController()->GetControlRotation();

	FTransform transform = Datas[0].EffectTransform;
	transform.AddToTranslation(location);
	transform.SetRotation(FQuat(rotator));

	FActorSpawnParameters param;
	param.Owner = OwnerCharacter;

	ACThrow* throwObject = OwnerCharacter->GetWorld()->SpawnActorDeferred<ACThrow>(
		Datas[0].ThrowClass, transform, OwnerCharacter, NULL,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	throwObject->OnThrowBeginOverlap.AddDynamic(this, &ACDoAction_Throw::OnThrowBeginOverlap);
	UGameplayStatics::FinishSpawningActor(throwObject, transform);
}

void ACDoAction_Throw::End_DoAction()
{
	State->SetIdleMode();
	Status->SetMove();
}

void ACDoAction_Throw::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Aim->Tick(DeltaSeconds);
}

void ACDoAction_Throw::OnAim()
{
	Aim->OnAim();
}

void ACDoAction_Throw::OffAim()
{
	Aim->OffAim();
}

void ACDoAction_Throw::OnThrowBeginOverlap(FHitResult InHitResult)
{
	FDamageEvent e;
	InHitResult.GetActor()->TakeDamage(Datas[0].Power, e, OwnerCharacter->GetController(), this);
}
