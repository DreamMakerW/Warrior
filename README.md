# Warrior

## Melee Combo System
### 3-5 Hero Hero Gameplay Ability
> 本节主要内容是在以下两个文件中创建辅助函数（查找角色、控制器、组件等），以供蓝图调用
> - WarriorGameplayAbility
> - WarriorHeroGameplayAbility

### 3-6 Ability Input Action
> 本节课主要是重复了Input Binding流程的前三个流程
> 
>> 全流程：Native Gameplay Tags -> Input Config Data Asset -> Custom Input Component -> Binding Inputs -> Assign Assets in Editor
>
> Native Gameplay Tags: 声明及定义GameplayTag
> 
> Input Cofig Data Asset: 创建了一个新的数组存储AbilityInputAction
> 
> Custome Input Component: 为绑定action创建了模板函数

### 3-7 Hero Ability Set
> Hero Character需要把标签传给Ablity System Component，通过标签激活对应的Ability，因此在UDataAsset_HeroStartUpData类里创建了一个结构体，维护标签与ability的关系，并重写了将能力赋予ASC的方法，这样在WarriorHeroCharacter的PossessedBy函数中就会调用子类的GiveToAbilitySystemComponent方法。

### 3-8 Binding Ability Input
> 在Input Component中将Ability与tag绑定，在Hero Character中，调用绑定方法并定义回调函数。
