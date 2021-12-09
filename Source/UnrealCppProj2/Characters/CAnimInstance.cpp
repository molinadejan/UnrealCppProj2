#include "CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"


void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(character);

	speed = character->GetVelocity().Size2D();
	direction = CalculateDirection(character->GetVelocity(), character->GetControlRotation());

}
