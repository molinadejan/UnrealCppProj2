#include "CActionData.h"
#include "Global.h"
#include "CAttachment.h"
#include "CEquipment.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

void UCActionData::BeginPlay(ACharacter* InOwnerCharacter)
{
	FTransform transform;

	Attachment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>
		(AttachmentClass, transform, InOwnerCharacter);

	Attachment->SetActorLabel(InOwnerCharacter->GetActorLabel() + "_Attachment");

	UGameplayStatics::FinishSpawningActor(Attachment, transform);

	Equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>
		(EquipmentClass, transform, InOwnerCharacter);

	Equipment->AttachToComponent(InOwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));

	Equipment->SetActorLabel(InOwnerCharacter->GetActorLabel() + "_Equipment");

	Equipment->SetData(EquipmentData);

	UGameplayStatics::FinishSpawningActor(Equipment, transform);

	Equipment->OnEquipmentDelegate.AddDynamic(Attachment, &ACAttachment::OnEquip);
	Equipment->OnUnEquipmentDelegate.AddDynamic(Attachment, &ACAttachment::OnUnEquip);
}
