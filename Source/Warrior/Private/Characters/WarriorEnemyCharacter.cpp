// Wyy All Rights Reserved


#include "Characters/WarriorEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "Engine/AssetManager.h"
#include "DataAssets/StartUpData/DataAsset_EnemyStartUpData.h"

#include "WarriorDebugHelper.h"

AWarriorEnemyCharacter::AWarriorEnemyCharacter()
{
	// 设置角色在被放置到场景中或生成时自动由 AI 控制器接管，无需玩家手动控制
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// 禁止角色随控制器的旋转而旋转（俯仰、翻滚、偏航）。角色的朝向不再跟随鼠标/手柄输入
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// 关闭控制器对角色旋转的直接控制，移动方向不再受控制器输入影响
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	// 角色自动朝向移动方向旋转，使移动更自然（如第三人称角色跑向目标时自动转身）
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// 设置角色旋转速率为每秒绕 Yaw 轴（垂直轴）旋转 180 度，Pitch 和 Roll 不旋转，确保平滑转向。
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	// 设置角色停止移动时的减速度，松开移动键后快速停止
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>("EnemyCombatComponent");
}

void AWarriorEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	/* 异步加载数据 */
	InitEnemyStartUpData();
}

void AWarriorEnemyCharacter::InitEnemyStartUpData()
{
	if (CharacterStartUpData.IsNull())
	{
		return;
	}

	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
				if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(WarriorAbilitySystemComponent);
					Debug::Print(TEXT("Enemy Start Up Data Loaded!"), FColor::Green);
				}
			}
		)
	);
}
