// Wyy All Rights Reserved


#include "Components/Combat/PawnCombatComponent.h"
#include "Items/Weapons/WarriorWeaponBase.h"

#include "WarriorDebugHelper.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWarriorWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	// ����ǩ�Ƿ��Ѿ�����
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("A tag named %s has already been added as carried weapon"), *InWeaponTagToRegister.ToString());
	// ��������Ƿ���Ч
	check(InWeaponToRegister);

	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);

	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}

	// const FString WeaponString = FString::Printf(TEXT("A weapon named: %s has been registered using the tag %s"), *InWeaponToRegister->GetName(), *InWeaponTagToRegister.ToString());
	// Debug::Print(WeaponString);
}

AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if (CharacterCarriedWeaponMap.Contains(InWeaponTagToGet))
	{
		if (AWarriorWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet))
		{
			// CharacterCarriedWeaponMap.Find()����ֵ������AWarriorWeaponBase* const*
			// AWarriorWeaponBase* const*��һ������ָ�룬���ָ��ָ����ǳ���ָ�룬��AWarriorWeaponBase* const
			// constĬ����������ߣ������������ָ��ָ��ĵ�ַ�ǹ̶����ɸ��ĵģ�ָ������ݿɱ�
			// �˴�ֱ�ӷ�����*FoundWeapon����Ϊ�ڽ���ֵ������ʱ�򶥲�const�ɺ��ԣ���Ϊ���ص�ֻ��һ��ֵ��*FoundWeapon������Ȼ��const��
			return *FoundWeapon;
		}
	}
	return nullptr;
}

AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}
	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}
