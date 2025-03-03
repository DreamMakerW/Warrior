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
> 检测到物体以后，下一步就是进行通知以便就行后续的伤害处理，HeroCombatComponent中重写了OnHitTargetActor，进行伤害检测，在此函数中调用函数UAbilitySystemBlueprintLibrary::SendGameplayEventToActor()。在GA_LightAttack中定义了WaitGameplayEvent节点负责监听（选择了同一个标签），当SendGameplayEventToActor调用以后，该事件会被激活，执行后续伤害处理流程。

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


<details>
<summary>

### 4-24 Modify Health Attribute
  
</summary>

> 重载PostGameplayEffectExecute函数，通过Data.EvaluatedData.Attribute与其他属性进行匹配，修改对应的属性。
>
> 本节遇到一个问题就是GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName)没有生效，而其他的Getter和Setter都是正常的，应该是跟宏里面static有关。

</details>

<details>
<summary>

### 4-25 Hit React Ability
  
</summary>

> 从本节开始，下面几节主要做一些所谓的“打击感”。
>
> 首先是受击反馈，这也是一种ability，敌人的ability流程是：Ability Tags -> Gameplay Ability Blueprint（先创建基类蓝图，写逻辑，子类蓝图填数据） -> Anim Montage -> Grant Ability（DA里选择对应能力蓝图）。

</details>

<details>
<summary>

### 4-26 Trigger Hit React Ability
  
</summary>

> 之前已经授予了能力，下一步是怎么“触发”的问题，很明显，在角色进行攻击的时候触发敌人的受击动画，所以在GA_Hero_LightAttackMaster蓝图中使用了蓝图库中的方法Send Gameplay Event To Actor，此方法被调用后，触发GA_Enemy_HitReact_Base事件，从而调整敌人面向的方向以及播放蒙太奇。

</details>

<details>
<summary>

### 4-27 Material Hit FX
  
</summary>

> 修改重击蓝图，使得重击能够触发受击动画。
>
> 修改enemy的材质，并通过参数对enemy材质进行控制，在GA_Enemy_HitReact_Base蓝图中，在角色被击中时修改参数，从而使得enemy呈现出不同的样子。

</details>

<details>
<summary>

### 4-28 Hit Pause
  
</summary>

> 实现了“卡肉”效果。Hit pause也是作为主角的一种ability，实现流程与之前基本一致，而hit pause则是通过event进行触发的，enemy的受击动画，通过在蓝图中调用Send Gameplay Event To Actor进行触发，而hit pause这里则在C++中调用了SendGameplayEventToActor函数进行触发。

</details>

<details>
<summary>

### 4-29 Camera Shake
  
</summary>

> GA_Hero_HitPause蓝图中加入相机抖动节点，创建相机抖动蓝图。

</details>


<details>
<summary>

### 4-30 Hit React Sound
  
</summary>

> 在敌人的montage中添加受击音效。
>
> 为了解决同时击中多个敌人导致同时播放多个音效的问题，创建Sound Concurrency资产，控制同时播放的音效数量。

</details>

<details>
<summary>

### 4-31 Gameplay Cues
  
</summary>

> 斧头的击中音效不要放在montage里，因为我们想要的是只有在斧头击中目标以后才播放击中音效。
>
> 本节使用了Gameplay Cue来播放音效。

</details>

<details>
<summary>

### 4-32 Enemy Death Ability
  
</summary>

> Enemy Death Process：Attribute Set(Add tag to actor) → Play Death Montage(Triggered on tag added) → Death FX(Material FX / Particle FX)
>
> 本节首先完成了死亡能力的授予，与其他ability流程一样，只不过触发ability变成了通过tag触发。
>
> 在GA_Enemy_Death_Base蓝图中播放montage和执行gameplay cue播放声音。

</details>


<details>
<summary>

### 4-33 BP Death Interface
  
</summary>

> 解决enemy死亡以后动画恢复至idle的问题，需要停用动画，关闭碰撞等。
>
> 怎么从EndAbility调用BP_Enemy_Character_Base中的逻辑？可以选择Cast to或者使用蓝图接口，本节创建了蓝图接口以实现通信。

</details>

<details>
<summary>

### 4-34 Dissolve Material FX
  
</summary>

> 给enemy和enemy weapon添加死亡后慢慢消失的效果，也就是在BP_EnemyCharacter_Base中修改材质参数，缓慢溶解的过程使用timeline来实现。
>
> 之前一直不是很清楚texture, material, anim, montage, mesh, skeleton的区别，这里说一下自己的浅见：
> > texture & material: texture是基元，提供纹理信息，而material则是综合texture及算法实现的效果，比如溶解效果的实现。
> > 
> > anim & montage: 同样anim是基元，montage在anim的基础上，进行动画的逻辑控制、动画混合等。
> > 
> > mesh & skeleton: mesh是3D模型的集合结构，决定了物体的形状，而skeleton是由骨骼和关节组成的层级结构，驱动mesh变形以实现动画。

</details>


<details>
<summary>

### 4-35 Dissolve Niagara FX
  
</summary>

> 使用Spawn System Attached给死亡后的enemy添加粒子特效，首先在蓝图接口中将Niagara作为函数的输入，之后在蓝图中进行加载。添加完后的粒子效果有个问题，就是颜色与enemy溶解时材质的颜色不一致，所以获取enmey的材质，找到其颜色参数，赋予niagara相关参数即可。

</details>

<details>
<summary>

### 4-36 Pawn UI Component
  
</summary>

> 创建PawnUIComponent及其子类，创建PawnUIInterface接口，以便查找PawnUIComponent，使WarriorBaseCharacter及子类实现该接口。

</details>

<details>
<summary>

### 4-37 Broadcast Value Change
  
</summary>

> AttributeSet中获取UIComponent，而UIComponent中定义了**委托函数**，当属性发生变化时，AttributeSet中获取的UIComponent则会进行广播。

</details>

<details>
<summary>

### 4-38 Listen For Broadcasting
  
</summary>

> 创建WarriorWidgetBase基类，该类重载NativeOnInitialized函数，此函数通过IPawnUIInterface接口获得HeroUIComponent，调用BP_OnOwningHeroUIComponentInitialized函数（此函数在Widget蓝图中被重写，绑定血量修改时的事件）。
>
> 角色蓝图中添加了Widget，之后触发Widget蓝图中NativeOnInitialized函数，子类中重载了调用BP_OnOwningHeroUIComponentInitialized函数，则会对其进行调用。
>
> 注意，此时在AttributeSet中，我们通过接口进行了广播，它并不知道Widget的存在；而反观WarriorWidgetBase类，借助于基类中的蓝图接口，它的子类蓝图也只是绑定了委托事件，并不知道AttributeSet的存在。

</details>

<details>
<summary>

### 4-39 Enemy Init Created Widget
  
</summary>

> 与上一节的内容差不多，为enemy创建widget相关逻辑。

</details>

<details>
<summary>

### 4-40 Template Widgets
  
</summary>

> 创建UI模板部件。

</details>

<details>
<summary>

### 4-41 Set Status Bar Fill Color
  
</summary>

> 在蓝图中编写状态条的颜色逻辑。

</details>

<details>
<summary>

### 4-43 Hero Overlay Widget
  
</summary>

> 创建角色UI的canvas（少用，用多了影响性能），排列之前创建的模板部件。
>
> WBP_HeroOverlay蓝图中重写WarriorWidgetBase类中的BP_OnOwningHeroUIComponentInitialized函数，将委托事件赋予函数逻辑，从而在进行广播的时候修改状态条。
>
> 将创建widget作为能力蓝图赋予角色。

</details>

<details>
<summary>

### 4-44 Enemy Health Widget Component
  
</summary>

> 创建敌人的health bar，在AWarriorEnemyCharacter类的构造函数中创建WidgetComponent，在BeingPlay()中调用UWarriorWidgetBase类中的InitEnemyCreatedWidget函数，使得health bar实时显示enemy血量。

</details>

<details>
<summary>

### 4-45 Hide Enemy Health Bar
  
</summary>

> 在WBP_DefaultEnemyHealthBar蓝图中编写health bar的隐藏逻辑，比如一开始是隐藏的，一定时间后不被攻击会隐藏，血量清空后会隐藏。注意初始化的时候会调用一次OnCurrentHealthChanged_Event节点。

</details>

<details>
<summary>

### 4-46 Update Weapon Icon
  
</summary>

> 实现装备/卸载武器时变换图标的功能：图标作为weapon data的一种资源，在装备/卸载武器的ability中，触发广播，对应的委托事件则负责更新图标。

</details>

<details>
<summary>

### 4-47 Final Tweaking
  
</summary>

> 解决切换武器图标时一闪而过的白色背景问题，导致该问题发生的原因为图片是异步加载的，在加载完以前就执行了后续流程。解决方式未创建了一个手动加载资源的自定义事件（也可以采用delay的方式解决）。
>
> 调整UI显示。

</details>

  
</details>


## Enemy AI

<details>
  <summary>Lesson list</summary>

  <details>
<summary>

### 5-3 Crowd Following Component
  
</summary>

> 躲避算法分为两种：RVO Avoidance与Detour Crowd Avoidance，从表现上来看Detour Crowd Avoidance更好一些。
>
> 创建AWarriorAIController，在初始化方法中设置PathFollowingComponent为UCrowdFollowingComponent，以启用Detour Crowd Avoidance；创建敌人AI蓝图。

</details>


<details>
<summary>

### 5-4 AI Perception
  
</summary>

> 实现AI的perception功能，创建EnemyPerceptionComponent与AISenseConfig_Sight，设置相关属性。创建另一个新函数，以便绑定到委托事件。

</details>

<details>
<summary>

### 5-5 Generic Team ID
  
</summary>

> 设置TeamID以分辨不同的阵营，原理是实现IGenericTeamAgentInterface接口，重写其中函数。

</details>



<details>
<summary>

### 5-6 Behavior Tree
  
</summary>

> 使用行为树来控制enemy的行为逻辑，创建黑板，其中的key对应的value通过C++进行配置，OnEnemyPerceptionUpdated是绑定的委托事件，当敌人感知到actor的时候，则对key进行设置。
>
> 为了能够运行行为树，需要在AIController中重写OnPosses函数，执行Run Behavior Tree节点。

</details>

<details>
<summary>

### 5-7 Configure AI Avoidance
  
</summary>

> 为了拥有更好的avoidance质量，需要设置一些参数，分为两部分：
>
> > 其中一部分参数并没有暴露给蓝图，可以在C++中创建一些暴露给蓝图的变量，通过这些变量设置参数。
> > 
> > 另外一部分参数通过Project Settings - Crowd Manager来进行设置。

</details>

<details>
<summary>

### 5-8 Behavior Tree Node Types
  
</summary>

> 讲解了行为树中的四种节点类型：composite node, decorator node, service node, task node。
>
> 创建service node，可通过蓝图/C++实现service逻辑。

</details>

<details>
<summary>

### 5-9 Observer Aborts
  
</summary>

> 设置selector节点下不同分支的中止策略。

</details>

<details>
<summary>

### 5-10 Orient To Target Actor
  
</summary>

> 通过C++的方式编写自定义Service，父类可以选择BTService或者BTService_BlackboardBase，BTService类基本需要从头开始编写，而BTService_BlackboardBase类中有一些初始代码。
>
> 重写TickNode函数，实现enemy面向角色的功能。

</details>

<details>
<summary>

### 5-11 Environment Query System
  
</summary>

> 简单介绍了EQS的各种概念以及使用。

</details>

<details>
<summary>

### 5-12 Custom Query Context
  
</summary>

> 修复enemy同时感知角色和test pawn的问题。
>
> 通过蓝图自定义context，使得item生成在角色周围，EQS负责生成item，过滤item；在行为树中运行EQS任务，将过滤出来的点存到黑板的键值中，MoveTo节点又从中获取位置，从而控制enemy移动。

</details>

<details>
<summary>

### 5-13 Toggle Strafing State
  
</summary>

> 通过蓝图自定义task处理敌人的strafing状态：设置旋转，最大行走速度，添加标签等。
>
> > 注意：对于自定义蓝图的行为树节点，默认是存在于世界中的实例，意味着变量的值在不同的execution中可以被保存，只适用于蓝图，而不能适用于C++（因为没有被实例化）。

</details>


<details>
<summary>

### 5-14 Calculate Direction
  
</summary>

> UWarriorCharacterAnimInstance类中声明了新的变量LocomotionDirection，并在NativeThreadSafeUpdateAnimation函数中进行更新。在ABP_Enemy_Base中引入该变量，同时声明一个新的blend space变量，通过该变量控制blend space动画的播放效果。（主要是展示了C++中变量与blend space的配合）

</details>

<details>
<summary>

### 5-15 Strafing Blend Space
  
</summary>

> 创建enemy的blend space，通过horizontal axis和vertical axis两个轴变量来控制动画表现。

</details>


<details>
<summary>

### 5-16 Compute Success Chance
  
</summary>

> 通过蓝图自定义行为树中的装饰器节点，以计算敌人有多大的概率发起攻击。

</details>

<details>
<summary>

### 5-17 Dot Product Test
  
</summary>

> 敌人在选择位置的时候，周围生成的点都是可选的，想要过滤掉敌人前方的一些点：原理上点积可以比较两个向量之间的角度，所以在EQS查询中增加了Dot测试以进行过滤。

</details>

<details>
<summary>

### 5-18 Enemy Melee Ability
  
</summary>

> 授予敌人ability的流程：创建ability基类蓝图 -> 创建ability子类蓝图 -> 配置DA_Guardian。

</details>

<details>
<summary>

### 5-19 Activate Ability By Tag
  
</summary>

> 激活enemy能力：
>
> > 1.在UWarriorAbilitySystemComponent类中定义函数TryActivateAbilityByTag，通过标签激活能力。
> >
> > 2.创建BTTask_ActivateAbilityByTag蓝图，重写父类蓝图中定义的OnEnemyExecuteTask函数，获取ability system component，调用定义的TryActivateAbilityByTag函数，以激活能力。
> >
> > 3.在行为树中执行该任务（行为树需要配置给AI Controller）。

</details>


<details>
<summary>

### 5-20 Is Target Pawn Hostile

</summary>

> 给montage添加notify state，使得武器碰撞到角色时启用碰撞。
>
> 判断是否为地图pawn，UWarriorFunctionLibrary类中创建函数IsTargetPawnHostile，通过GenericTeamId判断是否为敌对。
>
> UEnemyCombatComponent类中重写OnHitTargetActor委托函数。

</details>


<details>
<summary>

### 5-21 Notify Melee Hit

</summary>

> 重写OnHitTargetActor，避免单次挥动武器，多次判定。
>
> > 借助于SendGameplayEventToActor函数，调用事件（GA_Enemy_MeleeAttack_Base蓝图中的Wait Gameplay Event节点）。

</details>

<details>
<summary>

### 5-22 Make Enemy Damage Effect Spec Handle

</summary>

> 为了能够应用伤害，在C++中创建MakeEnemyDamageEffectSpecHanlde函数，返回FGameplayEffectSpecHandle，以供调用ApplyEffectSpecHandleToTarget节点。

</details>

<details>
<summary>

### 5-23 Apply Enemy Damage

</summary>

> MakeEnemyDamageEffectSpecHandle中有个入参是InDamageScalableFloat，在蓝图中提升为了变量，为其指定curve table。

</details>

<details>
<summary>

### 5-24 Motion Warping

</summary>

> 解决enemy朝向问题：采用Motion Warping插件。
>
> 在C++中创建UMotionWarpingComponent，之后在montage中设置notify state，设置参数（注意动画要启用root motion）。

</details>

<details>
<summary>

### 5-25 Update Motion Warp Target

</summary>

> 继续上一节的工作，我们需要enemy更新它的朝向，但是又不必每帧更新，可以采取自定义BTService的方式实现，重写蓝图中Receive Tick AI事件。从黑板中获取键TargetActor，同时这个名称与notify state中Warp Target Name要一致。

</details>

<details>
<summary>

### 5-26 Construct Native BT Task

</summary>

> 解决另外一个问题：当角色处于敌人正后方时，敌人先播放攻击动画再转身。
>
> 以BTTaskNode节点为父节点，创建自定义蓝图节点。
>
> 值得注意的是：C++创建的Behavior task默认不会在世界中进行实例化，所以对于那些没有实例化的节点，一般来说变量的值也无法保存。
> >
> > 如果要重用变量中的值：需要创建结构体，重写GetInstanceMemorySize函数，重写后会为结构体分配内存，之后就可以从该结构体中取值了。

</details>


<details>
<summary>

### 5-27 Rotate Enemy In Task

</summary>

> 重写ExecuteTask及TickTask函数，在ExecuteTask中返回InProgress，由TickTask函数处理剩余部分逻辑，以实现转向。

</details>

<details>
<summary>

### 5-28 Melee Attack Branch

</summary>

> 根据之前创建的节点，配置enemy的行为树。

</details>


<details>
<summary>

### 5-29 Does Actor Have Tag Decorator

</summary>

> 本节要解决的问题是，敌人在撤回原来的位置时，如果受到攻击，仍然继续往回撤，此时敌人应该进行反击。
>
> 想要通过添加装饰器节点来解决该问题，当敌人受到攻击时，添加tag表示敌人的状态。行为树中检测tag的节点并不能中断其他分支，于是考虑自定义BTDecorator节点，重写PerformConditionCheckAI函数。

</details>

<details>
<summary>

### 5-30 Duration Gameplay Effect

</summary>

> 上节课提到要给敌人添加tag表示受到攻击。
>
> 怎么添加：通过持续性的gameplay effect进行添加。
>
> 何时添加：在敌人受到攻击时添加，也就是在敌人hit react的ability中添加此标签。

</details>

<details>
<summary>

### 5-31 Should Abort All Logic

</summary>

> 当角色hp为0的时候，enemy应该停止攻击：为行为树创建新的装饰器节点，使用蓝图重写PerformConditionCheckAI逻辑，通过dead标签检测actor是否死亡。

</details>

<details>
<summary>

### 5-32 Guardian Attack Sound FX

</summary>

> 在enemey的montage中添加喊叫和攻击的音效，另外通过tag在ability中播放命中敌人时的gameplay cue。
>
> 目前总结下来，montage添加的音效是和动画相关的，而gameplay cue添加的音效是和逻辑相关的。

</details>

</details>

## Hero Combat Abilities

<details>
<summary>Lesson list</summary>

<details>

<summary>
    
### 6-3 Two-Key Input Action

</summary>

> 给角色添加翻滚的能力，首先回顾一下添加角色能力的流程：Ability Tags -> Gameplay Ability Blueprint -> Anim Montage -> Ability Input Action -> Grant Ability。
>
> 翻滚需要按方向键 + 空格键，在配置InputAction的时候，要选择与IA_Move协同触发。之后
> - 配置InputConfig，将InputAction与InputTag对应。
> 
> - 配置MappingContext，将InputAction与用户输入绑定。、


</details>

<details>

<summary>
    
### 6-4 Get Last Movement Input

</summary>

> 通过Motion Warping扭曲角色动画，使得角色朝运动方向翻滚。
>
> 流程：
>  - 在montage中添加notify state，设置warp target name，注意要取消warping translation的对勾（否则角色会瞬移）。
>  - 在ability通过Get Last Movement Input Vector获取角色移动向量（也就是角色在翻滚瞬间的朝向），通过Add or Update Warp Target from Location and Rotation变形角色动画。


</details>


<details>

<summary>
    
### 6-5 Rolling Distance

</summary>

> 控制翻滚的距离，实现方式同样也是通过motion warping，需要注意的时候，此次添加notify state的时候要勾选warping translation，取消勾选warp rotation，其他与变形翻滚朝向做法差不多。
>
> 值得一提的是调用了line trace for objects节点绘制线条，以供调试。


</details>


<details>

<summary>
    
### 6-6 Get Value At Level

</summary>

> 上一讲中，翻滚方式是通过硬编码控制的，本讲对其进行了优化：设置一个ScalableFloat变量，选择对应的Curve Table。
>
> 为了从ScalableFloat变量中获取float值，在UWarriorFunctionLibrary类中声明了一个辅助函数以实现此功能。


</details>

<details>

<summary>
    
### 6-7 Rolling Sound FX

</summary>

> 添加翻滚音效。


</details>


<details>

<summary>
    
### 6-8 Hero Hit React Ability

</summary>

> 创建受击能力蓝图和montage。


</details>


<details>

<summary>
    
### 6-9 Trigger Hero Hit React

</summary>

> 授予角色受击能力，之后就是能力的激活：在GA_Enemy_MeleeAttack_Base中，通过Send Gameplay Event to Actor节点激活受击能力（应该是在蓝图Class Defaults的Ability Triggers中进行了对应）。

</details>


<details>

<summary>
    
### 6-10 Hero Hit FX

</summary>

> 创建材质实例，当角色被攻击时，在能力蓝图中修改材质的参数，从而显示不一样的颜色。

</details>


<details>

<summary>
    
### 6-11 Compute Hit React Direction

</summary>

> 计算受击方向：首先取得两个向量——角色的前向向量与角色到敌人的向量，通过点击计算两个向量之间的角度，但结果都是正的，不能分清左右关系；再通过叉积判断左右关系。
>
> 注意：虚幻中叉积是符合左手法则的。

</details>

<details>

<summary>
    
### 6-12 Hit React Tags

</summary>

> 计算受击方向后，返回不同的标签以说明敌人的方位。

</details>

<details>

<summary>
    
### 6-13 Switch On Gameplay Tags

</summary>

> 上一讲的函数返回的是不同的标签，为了根据不同的标签选择不同的montage，首先把montage提升为变量，然后调用Swithc on Gameplay Tag节点，根据不同的标签赋予montage变量不同的值，从而播放不同的动画。
>
> 另外有一个问题就是动画效果不太明显，似乎是混合导致的，解决方式是将UpperPose单独存储起来，当角色没有进行移动时，播放该pose。

</details>





</details>
