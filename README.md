# Warrior

## Melee Combo System
<details>
  <summary>Lesson list</summary>

  <details>

  <summary>
    
### 3-5 Hero Hero Gameplay Ability

  </summary>
    
> 本节主要内容是在以下两个文件中创建辅助函数（查找角色、控制器、组件等），以供蓝图调用
> - WarriorGameplayAbility
> - WarriorHeroGameplayAbility
  </details>

<details>
  <summary>
    
### 3-6 Ability Input Action

   </summary>
  
> 本节课主要是重复了Input Binding流程的前三个流程
> 
>> 全流程：Native Gameplay Tags -> Input Config Data Asset -> Custom Input Component -> Binding Inputs -> Assign Assets in Editor
>
> Native Gameplay Tags: 声明及定义GameplayTag
> 
> Input Cofig Data Asset: 创建了一个新的数组存储AbilityInputAction
> 
> Custome Input Component: 为绑定action创建了模板函数

</details>

<details>
  <summary>
    
### 3-7 Hero Ability Set

  </summary>

> Hero Character需要把标签传给Ablity System Component，通过标签激活对应的Ability，因此在UDataAsset_HeroStartUpData类里创建了一个结构体，维护标签与ability的关系，并重写了将能力赋予ASC的方法，这样在WarriorHeroCharacter的PossessedBy函数中就会调用子类的GiveToAbilitySystemComponent方法。
</details>

<details>
  <summary>
    
### 3-8 Binding Ability Input

  </summary>
  
> 在Input Component中将Ability与tag绑定，在Hero Character中，调用绑定方法并定义回调函数，回调函数负责触发技能。
</details>

<details>
  <summary>
    
### 3-10 Wait for Gameplay Event

  </summary>
  
> 这两节课主要是创建动画，创建了动画通知用的蓝图，传递标签，并定义了新的标签，供发送通知时使用。（标签主要是用来识别武器的）
</details>

<details>
  <summary>
    
### 3-13 Link Anim Layer

  </summary>
  
> 不同的武器会有不同的动画，为了避免创建复杂的动画图表，采用了分层的概念创建动画。
</details>

<details>
  <summary>
    
### 3-14 Default Weapon Ability

  </summary>
  
> 设置了能力蓝图中，能力标签对其他标签的屏蔽。
> 
> 角色在装备武器时，要链接动画图层，有不同的能力：卸下装备，轻攻击，重攻击等，重新绑定输入映射上下文。
> 
> 角色在卸下装备时，需要卸载动画图层，移除授予的能力，移除输入映射等。
> 
> 这些跟武器相关，所以将这些内容维护在AWarriorHeroWeapon类中，简而言之，我们在捡起武器的同时，也捡起了一套“系统”。
</details>

<details>
  <summary>
    
### 3-15 Grant Weapon Ability

  </summary>
  
> UWarriorAbilitySystemComponent类里添加了GrantHeroWeaponAbilities方法，根据武器关联的能力进行授予。
>
> 设置蓝图。
>
> （不知道为什么少了3-14节的几个资源，已补充）
</details>

<details>
  <summary>
    
### 3-16 Handle Unequip Axe

  </summary>
  
> 卸载武器时，需要unlinke anim class layers，删除mapping context以及清空授权的能力。
>
> UWarriorAbilitySystemComponent负责授权能力以及移除授权能力，已授权的FGameplayAbilitySpecHandle被保存在武器类中。
>
> 补充了3-15结尾遗留部分代码。
</details>

<details>
  <summary>
    
### Stop & Summarize

  </summary>
  
> 前面这部分主要内容是围绕着输入-技能展开的，抛开动画暂且不论，仅输入-技能而言，大概逻辑是mapping context将action与input tag对应起来，而mapping context被存储在data asset中；input component中定义了绑定函数，将action，tag与回调函数进行关联，hero character的possesedby函数加载data asset，setupplayerinputcomponent中则启用了input component中的绑定函数，回调函数也在hero character中被定义，但其真正的实现OnAbilityInputPressed则在WarriorAbilitySystemComponent中，该函数根据标签遍历可激活的技能列表（GetActivatableAbilities()返回的是【可激活】的技能，可激活也就是被授予的技能，区别于【已激活】），如果标签匹配则激活对应技能TryActivateAbility，此时会触发对应蓝图中Activate Ability事件，执行后续逻辑，比如播放montage，设置anim class layer，mapping context，授予能力等等。
> ![Image](README_Img/Chapter3_StopAndSummarize.png)
  </details>


<details>
  <summary>

### 3-17 Light Attack Ability

  </summary>

>讲解了轻攻击能力的配置流程，前面框架搭好以后，流程就是：
>
>定义tag -> 创建action -> Input config中将input tag与action绑定 -> 修改mapping context，将aciton与输入进行映射 -> 创建能力蓝图，设置标签 -> 在武器中修改weapon data，配置input tag与ability
>
>注意：能力蓝图中设置的是ability tag，而其他地方没有记错的话设置的是input tag，Weapon data中将input tag与能力蓝图绑定，也就与ability tag进行了关联。
</details>

<details>
<summary>

### 3-18 Combo Logic

</summary>

> 本节重点是在GA_Hero_LightAttackMaster中创建了连击的逻辑，连续攻击增加计数，超过一定时间进行重置。
> 
> GA_Hero_LightAttack_Axe中则维护了montage的映射。
>
> 注意，montage中的slot可以视作一个“动画播放通道”，以控制不同部位的动画。

</details>

<details>

<summary>

### 3-20 Heavy Attack Logic

</summary>

> 本节与上一节的内容同轻攻击。
  
</details>

<details>

<summary>

### 3-21 Warrior Function Library

</summary>

> 因为连击系统与动画是独立的，现在需要实现这样的功能：轻击3之后可以直接跳转到重击2，就需要进行通信。
>
> 本节创建了一个函数库以供后续使用，比如获取ASC组件，添加标签，移除标签，检测actor是否有标签等。
  
</details>

<details>

<summary>

### 3-22 Jump To Finisher
  
</summary>

> 在轻击和重击的功能蓝图中进行了轻击3->重击2的功能实现，主要思路就是通过Ability System Component添加标签，以识别能否进行跳转。
  
</details>

<details>

<summary>

### 3-23 Slow Motion and Sound FX
  
</summary>

> 基于AnimNotifyState类创建蓝图，重载函数以控制时间流速。
>
> 给montage添加慢动作及音效。
  
</details>

<details>

<summary>

### Bug Fixed
  
</summary>

> 上一节重击1的montage未保存。
>
> 修理了几处bug：之前定义event.unequip.axe标签时多打了空格，修复后导致人物不能正常收回武器，需要在收回武器的能力蓝图和montage中重新选择标签。

</details>

<details>

<summary>

### 3-24 Section Wrap Up
  
</summary>

> 注释调试代码，在FWarriorHeroAbilitySet这个结构体中，AbilityToGrant的类型换为更具体的子类UWarriorHeroGameplayAbility，删除部分无用资源。

</details>


</details>


## Hero Combat

<details>
  <summary>Lesson list</summary>

<details>

<summary>

### 4-3 Set Up Enemy Character
  
</summary>

> 前期准备，创建Enemy的C++类：character，startup data，gameplay ability，combat component。

</details>

<details>

<summary>

### 4-4 Gruntling Guardian
  
</summary>

> 创建动画蓝图，在创建模板动画蓝图的时候，并不需要指定骨骼。

</details>

<details>

<summary>

### 4-5 Asynchronous Loading
  
</summary>

> 主角因为只有一个，在加载start up data的时候是同步加载的，及时阻塞游戏进程，也很快就加载完了；而敌人数量可能是不定的，所以本节采用了异步加载的方式，在进行异步加载的时候还应用了lambda函数。
>
> 回顾一下start up data，该类主要是为了存储ablity而存在的，我们加载start up data也是为了授予主角/敌人能力的，注意，授予能力 ！= 激活能力。

</details>

<details>

<summary>

### 4-6 Spawn Enemy Weapon
  
</summary>

> 给敌人生成武器，创建游戏能力蓝图BP_Guardian_SpawnWeapon，需要设置tag，创建武器类，设置socket等。
</details>

<details>

<summary>

### 4-7 Attribute Set
  
</summary>

> 给角色设置血量，攻击力等属性。通过宏创建辅助函数。
>
> 点击~，在控制台输入showdebug abilitysystem后会显示设置的属性。
</details>

<details>
<summary>

### 4-8 Gameplay Effect
  
</summary>

> 上一节设置了AttributeSet，而Gameplay Effect的作用则是修改属性值。
>
> 本节同时也建立了Curve Table，有点类似于Excel表格填表。
</details>

<details>
<summary>

### 4-9 Apply Gameplay Effect To Self
  
</summary>

> 创建好Gameplay Effect以后，下一步就是怎么应用的问题，首先在UDataAsset_StartUpDataBase中保存UGameplayEffect，之后在GiveToAbilitySystemComponent函数中应用Gameplay Effect。
>
> 注意在DA_Hero中，给StartUpGameplayEffects进行赋值时，有先后顺序，先是MaxHealth，再是CurrentHealth。
</details>


<details>
<summary>

### 4-10 Init Enemy Attributes
  
</summary>

> 跟角色设置属性以及Gameplay Effect的流程差不多，在控制台输出调试信息的时候page down切换到敌人身上，也没有正确显示，于是修改了DefaultGame.ini文件。
</details>

<details>
<summary>

### 4-11 Pawn Combat Interface
  
</summary>

> 为了做伤害检测，首先需要处理武器的碰撞，而碰撞实际跟动画有关，需要设置ANS_ToggleWeaponCollision，因为AnimNotifyState有明确的起止点，以便启用/禁用武器碰撞。
>
> 为了能够启用武器碰撞，首先要获取武器，而武器可以在PawnCombatComponent中被获取，所以可以在PawnCombatComponent中设置一个ToggleCollision函数。
>
> 那么问题是怎么获取PawnCombatComponent？我们可以访问的是HeroCombatComponent/EnemyCombatComponent，对于启用/禁用碰撞而言，我们只需要访问基类PawnCombatComponent即可。
>
>> 1.用FindComponentByClass()获取组件。
>> 
>> 2.BaseCharacter实现自定义的IPawnCombatInterface接口，该接口中只有一个纯虚函数GetPawnCombatComponent()，HeroCharacter/EnemyCharacter需要覆盖虚函数并返回自己的CombatComponent。

</details>

<details>
<summary>

### 4-12 Toggle Weapon Collision
  
</summary>

> 在PawnCombatComponent中创建ToggleWeaponCollision以启用/禁用碰撞，在AnimNotifyState类中进行调用，并在montage中确定AnimNotifyState的起止点。

</details>

<details>
<summary>

### 4-13 On Weapon Begin Overlap
  
</summary>

> 本节主要内容为hit流程，在WeaponBase类有WeaponCollisionBox，将BeginOverlap与EndOverlap与WeaponCollisionBox进行绑定，对碰撞的物体进行检测。
>
> UPawnCombatComponent则用来处理武器碰撞，创建ToggleWeaponCollision函数待完善。

</details>

<details>
<summary>

### 4-14 On Target Interacted
  
</summary>

> 声明委托类型，在进行碰撞时或者碰撞结束后，调用委托绑定的回调函数。
>
> ![Image](README_Img/4-14.png)

</details>


<details>
<summary>

### 4-15 Notify Melee Hit
  
</summary>

> 确保每次攻击时，只攻击一次：在PawnCombatComponent创建一个AAcotr*数组，当检测到对象时加入数组，之后如果再次检测到同一个actor，则直接跳过。
>
> 检测到物体以后，下一步就是进行通知以便就行后续的伤害处理，HeroCombatComponent中重写了OnHitTargetActor，进行伤害检测，在次函数中调用函数UAbilitySystemBlueprintLibrary::SendGameplayEventToActor()。在GA_LightAttack中定义了WaitGameplayEvent节点负责监听（选择了同一个标签），当SendGameplayEventToActor调用以后，该事件会被激活，执行后续伤害处理流程。

</details>

<details>
<summary>

### 4-16 Set Up Attack Montages
  
</summary>

> 为其他轻攻击、重攻击添加ANS通知；为重攻击添加WaitGameplayEvent节点，检测事件。

</details>


<details>
<summary>

### 4-17 Make Gameplay Effect Spec Handle
  
</summary>

> 前面做了hit检测，后续自然就是进行伤害处理，如何通过gameplay effect影响attribute set，流程如图所示：
>
> ![Image](README_Img/4-17.png)
>
> 本节主要是在UWarriorHeroGameplayAbility类中创建了MakeHeroDamageEffectSpecHandle函数，返回FGameplayEffectSpecHandle以供后续使用。

</details>

<details>
<summary>

### 4-18 Hero Damage Info
  
</summary>

> 上一节课的补充，为MakeHeroDamageEffectSpecHandle准备入参，创建Effect Class，tag，获取base damage等。

</details>

<details>
<summary>

### 4-19 Apply Effect Spec Handle To Target
  
</summary>

> 创建好gameplay effect spec handle以后，下一步就是将handle应用于目标：在UWarriorGameplayAbility创建了相关函数，重点是调用UAbilitySystemComponent::ApplyGameplayEffectSpecToTarget函数。

</details>

<details>
<summary>

### 4-20 Capture Relevant Attributes
  
</summary>

> 为了能够进行伤害计算，需要对attributes进行捕获，本节课提供了两种方式进行捕获：一种是较慢的方式，另一种则是通过宏相对而言较快的方式进行捕获。

</details>

<details>
<summary>

### 4-21 Retrieve Hero Damage Info
  
</summary>

> 上节课对attributes进行了捕获，这节课主要是重载UGameplayEffectExecutionCalculation下的Execute_Implementation函数，以取得attributes的值。

</details>

<details>
<summary>

### 4-22 Calculate Final Damage Done
  
</summary>

> 在Execute_Implementation函数中编写**伤害计算逻辑**。

</details>

<details>
<summary>

### 4-23 Set Up Heavy Attacks For Damage
  
</summary>

> 在蓝图中修改heavy attck的逻辑，使得gameplay effect能够作用于attributes。
>
> 至此，前面流程图中Gameplay Effect Execution Calculation环节也就结束了。

</details>

  
</details>

