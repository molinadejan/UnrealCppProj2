#include "CDoAction_Throw.h"
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

	CheckFalse(State->IsIdleMode());
	State->SetActionMode();
	
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage,
		Datas[0].PlayRatio,
		Datas[0].StartSection);

	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Throw::Begin_DoAction()
{

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
