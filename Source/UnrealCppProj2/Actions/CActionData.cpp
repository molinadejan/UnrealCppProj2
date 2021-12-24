#include "CActionData.h"
#include "Global.h"
#include "CAttachment.h"
#include "CEquipment.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "CDoAction.h"

void UCActionData::BeginPlay(ACharacter* InOwnerCharacter)
{
    FTransform transform;

    if (!!AttachmentClass)
    {
        Attachment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>
            (AttachmentClass, transform, InOwnerCharacter);

        Attachment->SetActorLabel(InOwnerCharacter->GetActorLabel() + "_Attachment");

        UGameplayStatics::FinishSpawningActor(Attachment, transform);
    }

    if (!!EquipmentClass)
    {
        Equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>
            (EquipmentClass, transform, InOwnerCharacter);

        Equipment->AttachToComponent(InOwnerCharacter->GetMesh(),
            FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));

        Equipment->SetActorLabel(InOwnerCharacter->GetActorLabel() + "_Equipment");

        Equipment->SetData(EquipmentData);
        Equipment->SetColor(EquipmentColor);

        UGameplayStatics::FinishSpawningActor(Equipment, transform);

        if (!!AttachmentClass)
        {
            Equipment->OnEquipmentDelegate.AddDynamic(Attachment, &ACAttachment::OnEquip);
            Equipment->OnUnEquipmentDelegate.AddDynamic(Attachment, &ACAttachment::OnUnEquip);
        }
    }

    if (!!DoActionClass)
    {
        DoAction = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACDoAction>
            (DoActionClass, transform, InOwnerCharacter);

        DoAction->AttachToComponent(InOwnerCharacter->GetMesh(),
            FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));

        DoAction->SetActorLabel(InOwnerCharacter->GetActorLabel() + "_DoAction");

        DoAction->SetDatas(DoActionDatas);

        UGameplayStatics::FinishSpawningActor(DoAction, transform);

        if(!!Attachment)
        {
            Attachment->OnAttachmentBeginOverlap.AddDynamic(DoAction, &ACDoAction::OnAttachmentBeginOverlap);
            Attachment->OnAttachmentEndOverlap.AddDynamic(DoAction, &ACDoAction::OnAttachmentEndOverlap);

            Attachment->OnAttachmentCollision.AddDynamic(DoAction,
                &ACDoAction::OnAttachmentCollision);

            Attachment->OffAttachmentCollision.AddDynamic(DoAction,
                &ACDoAction::OffAttachmentCollision);
        }
    }
}
