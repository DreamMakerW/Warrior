// Wyy All Rights Reserved


#include "Components/Combat/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "WarriorGameplayTags.h"
#include "WarriorFunctionLibrary.h"

#include "WarriorDebugHelper.h"


void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	// 防止同一actor的重复判定
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}

	OverlappedActors.Add(HitActor);

	// TODO:: Implement block check
	bool bIsValidBlock = false;

	// 判断角色是否处于格挡状态
	const bool bIsPlayerBlocking = UWarriorFunctionLibrary::NativeDoesActorHaveTag(HitActor, WarriorGameplayTags::Player_Status_Blocking);
	const bool bIsMyAttackUnblockable = false;

	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		// TODO:: check if the block is valid
		bIsValidBlock = UWarriorFunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);
	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;


	if (bIsValidBlock)
	{
		// TODO:: Handle successful block
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			WarriorGameplayTags::Shared_Event_MeleeHit,
			EventData
		);
	}
}