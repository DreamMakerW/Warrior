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
> Input Cofig Data Asset: 创建了一个新的数组存储AbilityInputAction
> Custome Input Component: 为绑定action创建了模板函数
