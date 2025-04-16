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

<details>

<summary>
    
### 6-14 Hit React Sound FX

</summary>

> 添加角色被攻击时的音效。

</details>

<details>

<summary>
    
### 6-15 Hero Block Ability

</summary>

> 增加角色格挡技能。
>
> 定义tag -> 处理input action时的回调函数（AWarriorHeroCharacter类中SetupPlayerInputComponent方法进行的绑定，绑定回调函数Input_AbilityInputReleased） -> 创建gameplay ability蓝图并选择好对应的标签 -> 创建input action -> 配置input config -> 因为格挡技能只有在装备武器时才能使用，所以将其指定为武器的ability，在BP_HeroAxe中搜索Weapon Data，添加格挡能力 -> 配置IMC_Axe，将输入与input action进行绑定

</details>

<details>

<summary>
    
### 6-16 Add Gameplay Cue To Owner

</summary>

> 创建格挡montage，设置为循环播放；GA蓝图中设置播放montage；当被攻击时可以取消格挡能力，所以要配置对应的tag。
>
> 调用Add GameplayCueWithParams To Owner节点，创建gameplay cue蓝图（我们希望当ability是激活状态时，gameplay cue也是激活状态，选择以GameplayCueNotify_Actor为父类蓝图），配置Class Defaults。
> 
> - 重写While Active方法（当gameplay cue被附件到owner时只会调用一次），播放声音和特效。
> 
> - 重写OnRemove方法，销毁component。

</details>

<details>

<summary>
    
### 6-17 Is Valid Block

</summary>

> 本节开始编写格挡判定逻辑，在UEnemyCombatComponent类的OnHitTargetActor方法中，首先需要判断是否是有效的格挡，而判断方法则是通过角色与敌人前向向量的点击进行判断，如果小于-0.1f，则被认为是一次有效的格挡。

</details>


<details>

<summary>
    
### 6-18 Notify Successful Block

</summary>

> 当格挡有效时，在C++中调用SendGameplayEventToActor函数，并发送Player_Event_SuccessfulBlock标签。在GA_Hero_Block蓝图中，则调用Wait Gameplay Event节点，通过event tag关联事件，从而收到事件通知。

</details>

<details>

<summary>
    
### 6-19 Handle Successful Block

</summary>

> 本讲主要是写格挡成功后的蓝图逻辑，主要实现了三个功能：朝向敌人，小距离后退，添加特效。

</details>

<details>

<summary>
    
### 6-20 Is Perfect Block

</summary>

> 在格挡能力蓝图中，通过时间判断是否为完美格挡。

</details>


<details>

<summary>
    
### 6-21 Notify Perfect Block

</summary>

> 当格挡为完美格挡时，通过Set Global Time Dilation节点增加子弹时间效果；创建GameplayCue，重写OnExecute函数，通过Execute GameplayCueWithParams On Owner节点生成特效。
>
> 本节遇到了一个卡了挺久的Bug：当完美格挡时，子弹时间一直没有恢复到正常流速。
>
> 原因：UWarriorAbilitySystemComponent的OnAbilityInputReleased函数中，松开按键时，会调用CancelAbilityHandle()，取消技能。在蓝图中，时间流速变慢后，有个delay节点，如果此时松开格挡键位，该技能就被取消掉了，也就是进入了end ability，并没有从delay节点正常执行下去，恢复正常的时间流速。

</details>


<details>

<summary>
    
### 6-22 Initiate Counterattack

</summary>

> 解决上节课中提到的Bug：在OnEndAbility事件之后，判断一下global time dilation是否为1，如果不是的话重新恢复为1。
>
> 实现完美格挡后终结技：设置计时器，如果0.3秒内进行攻击，则切换为处决攻击，本讲只是简单地将处决攻击变为轻/重击的最后一次攻击，然后通过标签判断当前攻击是否为处决攻击，是的话直接跳转到最后一次攻击。

</details>

<details>

<summary>
    
### 6-23 Set Up Target Lock Ability

</summary>

> 实现Target Lock需要解决的问题：
>
> - Toggleable Ability
> - Get Available Targets
> - Draw/Update Target Lock Widget
> - Switch Animation Poses
> - Switch Target
>
> 本节为锁定目标能力的准备工作：
>
> 首先创建C++类UHeroGameplayAbility_TargetLock，需要重写ActivateAbility与EndAbility函数（暂时只是调用super）；定义需要的标签；创建蓝图类。

</details>


<details>

<summary>
    
### 6-24 Toggle Target Lock

</summary>

> 本讲对锁定目标的输入策略进行了设置：首先是UWarriorAbilitySystemComponent类的OnAbilityInputPressed方法中，要对toggleable的能力进行判断，从而控制能力的激活与结束；然后配置DA_InputConfig，创建InputAction，配置IMC_Axe（只有装备武器时才能锁定敌人），再就是在BP_HeroAxe中进行能力的授予。

</details>


<details>

<summary>
    
### 6-25 Get Available Targets

</summary>

> 在一定范围内获取所有目标，简单讲就是调用UKismetSystemLibrary::BoxTraceMultiForObjects函数，填写相应的参数，将检测到的目标加入到TArray数组中。

</details>


<details>

<summary>
    
### 6-26 Get Nearest Target

</summary>

> 继续补充TryLockOnTarget的逻辑，如果没有可锁定的目标，需要取消目标锁定的能力（当调用CancelAbility方法后，会执行EndAbility方法）。
>
> 通过UGameplayStatics::FindNearestActor方法获取距离角色最近的actor。

</details>


<details>

<summary>
    
### 6-27 Draw Target Lock Widget

</summary>

> 绘制锁定图标：首先创建widget蓝图，之后创建UHeroGameplayAbility_TargetLock::DrawTargetLockWidget函数，CreateWidget创建实例，之后通过AddToViewport进行绘制。

</details>

<details>

<summary>
    
### 6-28 Set Target Lock Widget Position

</summary>

> 设置widget的位置：UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition可将3维空间的坐标投影到2D空间，再调用SetPositionInViewport将widget绘制到指定位置。
>
> 此时会发现widget与正确位置有一些偏差，原因是没有考虑widget本身的大小。DrawnTargetLockWidget->WidgetTree->ForEachWidget的入参传入一个匿名函数，可以获取到widget的宽度和高度。

</details>


<details>

<summary>
    
### 6-29 Execute Task On Tick

</summary>

> 我们需要解决的问题是：当角色移动时，绘制的widget位置失效，所以我们需要每一帧对widget的位置进行更新，但是gameplay ability并不支持tick函数。
>
> 解决方式：自定义ability task，重写TickTask函数，定义委托事件，在ability蓝图中调用ability task。

</details>


<details>

<summary>
    
### 6-30 On Target Lock Tick

</summary>

> 上一讲自定义了以tick形式执行任务的ability task，本讲就是在上一讲的基础上，声明了OnTargetLockTick函数，更新widget的位置，然后以tick的频率执行即可。

</details>

<details>

<summary>
    
### 6-31 Orient To Target While Target Lock

</summary>

> 继续补充OnTargetLockTick函数，使得锁定目标时，摄像机和角色始终朝向被锁定的敌人。（注意，此处通过设置controller的旋转，从而影响摄像机的旋转）

</details>

<details>

<summary>
    
### 6-32 Switch To Target Lock Poses

</summary>

> 创建持有武器锁定敌人移动的动画混合空间，并进行应用。

</details>

<details>

<summary>
    
### 6-33 Target Lock Walk Speed

</summary>

> 设置锁定敌人时的最大行走速度。
>
> 在混合空间中，混合动画容易抽动，勾选Wrap Input后效果好很多。

</details>


<details>

<summary>
    
### 6-34 Switch Target Input Action

</summary>

> 本讲开始实现锁定目标时的切换功能：定义了输入标签，在AWarriorHeroCharacter类中调用BindNativeInputAction进行绑定，创建input action，在input config中进行对应。

</details>

<details>

<summary>
    
### 6-35 Target Lock Mapping Context

</summary>

> 在UHeroGameplayAbility_TargetLock中设置一个UInputMappingContext*变量，存储锁定时的mapping context，然后创建函数分别装载和卸载mapping context。
>
> 在卸载mapping context之前，对controller是否存在做了一个判断，防止引起崩溃。

</details>

<details>

<summary>
    
### 6-36 Notify Switch Target

</summary>

> 在AWarriorHeroCharacter::Input_SwitchTargetTriggered方法中获取偏移量，在Input_SwitchTargetCompleted方法中，调用SendGameplayEventToActor函数触发事件。
>
> 之后在GA_Hero_TargetLock蓝图中，调用Wait Gameplay Event节点，通过tag监听事件。

</details>


<details>

<summary>
    
### 6-37 Handle Switch Target

</summary>

> 主要是逻辑的编写，通过叉积判断位置关系，然后取最近的敌人进行锁定。

</details>


<details>

<summary>
    
### 6-38 Hero Death

</summary>

> 创建GA_Hero_Death能力蓝图，创建montage，在DA_Hero里进行配置，以授予该能力。
>
> 为了在character死亡的情况下，停止敌人的攻击，在行为树中，检测一下target actor是否有dead标签。

</details>


<details>

<summary>
    
### 6-39 Tweaking Target Lock

</summary>

> 调整了一下锁定目标时摄像机的位置。

</details>


</details>

## Ranged Enemy

<details>
  <summary>Lesson list</summary>
  
<details>
  
<summary>
    
### 7-2 Ranged Enemy Starting Weapon

</summary>

> 创建新类型的敌人，需要指定mesh，animation等。同时为了使敌人在生成时手里带着武器，需要复制能力蓝图，并配置Data Asset授予能力。

</details>

<details>
  
<summary>
    
### 7-3 Glacer Starting Stats

</summary>

> 设置敌人的初始状态：在Curve Table中设置数值，在GE_Guardian_StartUp蓝图类（Gameplay Effect的子类）中配置Curve Table，之后在Data Asset(DA_Glacer)中配置GE_Guardian_StartUp。
>
> 其实gameplay effect与ability存储在UDataAsset_StartUpDataBase(Data Asset子类)中，在授予完能力之后，通过ApplyGameplayEffectToSelf方法应用effect。
>
> 查看effect是否生效：控制台输入showdebug abilitysystem，按page down键选到敌人即可。

</details>

<details>
  
<summary>
    
### 7-4 Glacer Hit React

</summary>

> 设置敌人的血量条、受击时的材质、死亡时的特效（包括武器）等。

</details>

<details>
  
<summary>
    
### 7-5 Ranged Behavior Tree

</summary>

> 修复当角色在墙边翻滚时，会移动到原点的问题：当无效命中时，impact point会是一个零向量，需要判断一下是否有效。
>
> 给敌人配置AI Controller，在AI Controller中配置行为树。

</details>


<details>
  
<summary>
    
### 7-6 Find Shooting Position

</summary>

> 编写AI控制逻辑，远程攻击的敌人首先要找到一个远离character的位置：修改行为树逻辑，判断与character之间的距离，执行EQS服务，给敌人寻找合适的位置，然后进行移动。
>
> 简单理解一下行为树，有以下常见的节点：
> > 根节点：行为树的入口，敌人行动逻辑的起点。
> >
> > 组合节点：控制子节点的执行顺序。
> > - Sequence: 按顺序（从左到右）执行子节点，直到失败。
> > - Selector: 按顺序（从左到右）执行子节点，直到成功。
> > - Parallel: 同时执行多个子节点，但启动顺序仍然为从左到右。
> > 装饰器：附加在节点上的逻辑判断，以决定是否执行该节点。
> >
> > 任务节点：具体执行的行为。
> >
> > 服务节点：在后台周期性运行的任务。（比如EQS）
> 
> 黑板主要是存储AI共享的数据，通过黑板键在节点之间传递数据。

</details>

<details>
  
<summary>
    
### 7-7 Project Ability

</summary>

> 创建能力蓝图、montage，配置DA_Glacer等，修改行为树逻辑，使得敌人向character发起攻击。

</details>

<details>
  
<summary>
    
### 7-8 Projectile Class

</summary>

> 创建Projectile类，添加相应的组件，并进行初始化。

</details>

<details>
  
<summary>
    
### 7-9 Spawning Projectile

</summary>

> 生成投射物，当然是需要根据敌人的动作进行生成的，所以在montage中添加notify(AN_SendGameplayEventToOwner)，在能力蓝图中调用Wait Gameplay Event节点进行监听，从而生成投射物。

</details>

<details>
  
<summary>
    
### 7-10 On Projectile Hit

</summary>

> 在投射物的C++代码中，通过AddUniqueDynamic绑定委托函数，从而在发生碰撞时进行调用，响应碰撞事件。

</details>

<details>
  
<summary>
    
### 7-11 Handle Projectile Hit

</summary>

> 在OnProjectileHit函数中处理碰撞逻辑，需要判断角色是否格挡成功，如果成功的话，调用SendGameplayEventToActor方法发送事件；否则进行伤害处理（后面进行实现）。
>
> 在头文件中声明BP_OnSpawnProjectileHitFX函数，在BP_Projectile_Base蓝图中重写该函数，生成声音和粒子特效，在BP_Projectile_Glacer中赋予具体的资源。

</details>

<details>
  
<summary>
    
### 7-12 Projectile Spec Handle

</summary>

> 创建HandleApplyProjectileDamage函数，以编写应用投射物伤害的游戏逻辑：在UWarriorFunctionLibrary类中创建了ApplyGameplayEffectSpecHandleToTargetActor函数，将指定的GameplayEffect应用到目标Actor，并返回是否成功应用。若成功应用，在HandleApplyProjectileDamage函数中触发受击反馈事件。

</details>

<details>
  
<summary>
    
### 7-13 Make Projectile Spec Handle

</summary>

> 上一讲中，我们通过meta = (ExposeOnSpawn = "true")将ProjectileDamageEffectSpecHandle属性暴露在对象的生成（Spawn）参数列表中，以便在蓝图中创建该对象时，动态传入该属性的初始值，本讲通过UWarriorEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle节点创建EffectSpecHandle，以携带伤害值等信息。

</details>

<details>
  
<summary>
    
### 7-14 Projectile Sound FX

</summary>

> 添加音效和粒子特效。

</details>

<details>
  
<summary>
    
### 7-15 Glacer Melee Ability

</summary>

> 制作武器拖尾效果。（其实就是添加notify state，在socket处添加粒子特效）
>
> 添加Glacer的近战能力，在DA_Glacer中授予，在行为树中通过task激活近战能力。

</details>

<details>
  
<summary>
    
### 7-16 Unblockable Attack

</summary>

> 设置Glacer的近战攻击为不可阻挡的，通过gameplay cue播放不可阻挡的特效提示。
>
> 之所以没有使用AnimNotifyState的方式，个人理解是gameplay cue通过gameplay tag进行触发，播放特效需要访问一些位置、旋转等数据，而AnimNotifyState只能访问蓝图动画中的变量。

</details>

</details>

## Boss Enemy

<details>
  
  <summary>Lesson list</summary>

<details>

<summary>
    
### 8-2 Set Up Boss Character

</summary>

> 设置boss蓝图以及用到的动画蓝图、混合空间等。

</details>

<details>

<summary>
    
### 8-3 Giant Starting Stats

</summary>

> 配置Boss的Gameplay Effect，Data Asset等文件。

</details>

<details>

<summary>
    
### 8-4 Boss Bar Widget

</summary>

> 制作boss的health bar，并通过委托来更新血量的变化。
>
> 总结一下委托的用法：
> > - 声明委托。
> >   - 声明委托类型、参数列表，然后声明一个委托变量，用来后续绑定委托函数。
> > - 绑定委托。
> >   - 绑定需要进行绑定的委托函数，动态委托可以在蓝图中进行绑定，本节就是在蓝图中进行了绑定。
> > - 触发委托。
> >   - 执行需要触发的委托函数。

</details>

<details>

<summary>
    
### 8-5 Draw Boss Bar To Screen

</summary>

> 通过能力蓝图绘制boss的血量条。

</details>

<details>

<summary>
    
### 8-6 Giant Hit React

</summary>

> 赋予boss受击能力。
>
> 生成材质实例以调整受击时显示的材质，调整完后分配给skeletal mesh，boss蓝图中的材质会相应更新。

</details>

<details>

<summary>
    
### 8-7 Giant Death
</summary>

> 给boss增加死亡能力，通过gameplay cue播放音效，并且播放粒子特效。

</details>

<details>

<summary>
    
### 8-8 Remove Boss Bar
</summary>

> 敌人死亡时，删除UI内容：在UEnemyUIComponent类中声明两个函数，RegisterEnemyDrawnWidget和RemoveEnemyDrawnWidgetsIfAny，在绘制血条的能力蓝图中注册组件，在boss角色蓝图的死亡事件中对UI组件进行删除。

</details>

<details>

<summary>
    
### 8-9 Giant Behavior Tree
</summary>

> 创建boss的AI Controller和Behavior Tree（其实也是复制过来的）。

</details>

<details>

<summary>
    
### 8-10 Giant Melee Abilitye

</summary>

> 给boss添加近战功能，另外为了使得boss攻击时面向character，在montage中采用了motion warping的方式。 修改行为树，简单测试近战功能。

</details>

<details>

<summary>
    
### 8-11 Hand Collision Box

</summary>

> 给boss添加了近战功能后却没有伤害，是因为之前都是用武器进行攻击，而boss用手进行攻击。本节主要在AWarriorEnemyCharacter类中创建LeftHandCollisionBox和RightHandCollisionBox，进行初始化，并绑定委托函数。

</details>

<details>

<summary>
    
### 8-12 Post Edit Change Property

</summary>

> 上一讲生成了LeftHandCollisionBox和RightHandCollisionBox，但是SetupAttachment的时候遇到了问题：每个角色的骨骼名称不一样，怎么确定绑定到哪个骨骼上呢？
>
> 解决方案：声明一个FName变量，设置为EditDefaultsOnly，存储骨骼名称，然后重写PostEditChangeProperty函数，当属性变化时，也就是在蓝图中赋予当前角色的骨骼名称时，会调用该函数，此时进行绑定即可。

</details>

<details>

<summary>
    
### 8-13 Toggle Box Collision

</summary>

> 总结一下敌人攻击触发的流程（以LeftHandCollisionBox为例）：
> > - 在montage中添加了ANS_ToggleWeaponCollision，会调用UPawnCombatComponent::ToggleWeaponCollision函数。
> > - ToggleWeaponCollision函数触发UEnemyCombatComponent::ToggleBodyCollisionBoxCollision，启用碰撞。
> > - 在进行初始化的时候，LeftHandCollisionBox是没有碰撞的，但是绑定了委托函数OnBodyCollisionBoxBeginOverlap。
> > - OnBodyCollisionBoxBeginOverlap函数会判断hitpawn是否为敌对的，如果是的话调用EnemyCombatComponent->OnHitTargetActor。
> > - OnHitTargetActor对格挡逻辑进行了判断，如果hero没有格挡/格挡无效，调用SendGameplayEventToActor，触发tag相关的gameplay event。
> > - GA_Enemy_MeleeAttack_Base蓝图中wait gameplay event监听到相关事件，触发handle apply damage节点，从而继续后面的伤害流程。

</details>

<details>

<summary>
    
### 8-14 Giant Second Melee Ability

</summary>

> 添加第二种近战攻击。
>
> 将第一种近战攻击设置为不可阻挡。
>
> 不可阻挡提示offset优化。

</details>

<details>

<summary>
    
### 8-15 Giant Combo

</summary>

> 添加连招：其实就是配置一堆的notify与notifystate。
>
> 通过socket控制粒子特效生成的位置。

</details>

<details>

<summary>
    
### 8-16 Wait Spawn Enemies

</summary>

> 本节开始给boss添加召唤的能力，增加了UAbilityTask_WaitSpawnEnemies这样一个ability task。
>
> 介绍一下ability task：
>  - 默认情况下ability是同步执行的，也就是说当gameplay ability的activate函数被调用时，如果没有使用ability task或者手动分帧逻辑（Timer, AsyncTask等），所有代码都会在同一帧内完成。
>  - Ability task的作用是“跨帧”，核心理念是将异步操作封装为任务，允许ability逻辑暂停等待某些条件，并在后续帧中继续执行。

</details>

<details>

<summary>
    
### 8-17 Summon Ability

</summary>

> 走一遍增加新技能的流程，创建montage并添加FX。

</details>

<details>

<summary>
    
### 8-18 Listen For Gameplay Event

</summary>

> 下面要生成enemies，分为三步：
> - Listen for Gameplay Event
> - Async Load
> - Spawn Enemies
>
> 本节主要是讲监听事件，在UAbilityTask_WaitSpawnEnemies类中重写Activate和OnDestroy函数，在Activate中绑定回调函数。
>
> Montage中添加AN_SendGameplayEventToOwner，发送对应的tag。
>
> tag匹配后，触发绑定的回调函数。

</details>

<details>

<summary>
    
### 8-19 Async Load And Spawn Enemies

</summary>

> 召唤敌人第二部——异步加载，使用UAssetManager进行异步加载，绑定了另外的回调函数OnEnemyClassLoaded，此函数中生成敌人。

</details>

<details>

<summary>
    
### 8-20 Fix Facing Rotation

</summary>

> 修复使用召唤技能时，boss和grunting的朝向问题。

</details>

<details>

<summary>
    
### 8-21 Stop Spawning Enemies

</summary>

> 停止生成敌人：在黑板中添加一个bool变量，当生成敌人后，进行设置，并在行为树的节点中添加装饰器以判断是否可以使用召唤技能。

</details>

<details>

<summary>
    
### 8-22 Enemy Entry FX

</summary>

> 在项目第一次启动时，因为数据加载问题，会导致一些不正确的情况发生：比如敌人生成的瞬间手里没有武器，显示不正确的health bar。
>
> 通过设置widget的可见性解决health bar问题，在BP_EnemyCharacter_Base的begin play事件中，使用特效。

</details>

<details>

<summary>
    
### 8-23 Enemy Entry Montage

</summary>

> 在BP_EnemyCharacter_Base的BeginPlay事件中，设置一个montage数组变量，让子类填充montage并播放。
>
> 添加grunting和boss的入场montage。

</details>

<details>

<summary>
    
### 8-24 Check Current Health Percent

</summary>

> 创建一个新的装饰器节点，当boss血量低于某个值的时候，使用召唤技能。同时在编辑器中创建了枚举。
>
> 击败召唤出来的grunting后，会发现有个小问题，就是boss的朝向不太对。（没太明白这个问题的原因和解决方式，留待以后解决吧）

</details>

</details>

## Hero Special Abilities

<details>
  
  <summary>Lesson list</summary>

<details>

<summary>
    
### 9-3 Rage Ability Tags

</summary>

> 定义愤怒能力需要用到的input tag, ability tag, status tag。

</details>

<details>

<summary>
    
### 9-4 Rage Ability Blueprint

</summary>

> 增加Rage能力，配置输入操作。

</details>

<details>

<summary>
    
### 9-5 Rage Anim Montage

</summary>

> 在使用rage技能时，给技能添加activating标签，并配置其他能力蓝图的Activation Blocked Tags，以防止rage被其他技能打断；montage播放完毕以后要移除该标签。
>
> 创建rage技能的montage。

</details>

<details>

<summary>
    
### 9-6 Rage Gameplay Cue

</summary>

> 设置了一下敌人武器材质中的参数，使其出现更丝滑。
>
> Rage Gameplay Cue流程：
> - 在montage中添加notify，发送事件，在GA_Hero_Rage中使用wait gameplay event进行监听，监听到事件后则添加gameplay cue，设置tag。
> - 创建新的gameplay cue，配置tag以进行匹配。
>   - 重写While Active函数，播放粒子特效和声音。
>   - 重写On Remove函数，移除粒子特效。 

</details>

<details>

<summary>
    
### 9-7 Activation Condition

</summary>

> UWarriorAttributeSet中修改PostGameplayEffectExecute函数，根据rage数值添加/移除标签。修改蓝图，配置Activation Required Tags = "Player.Status.Rage.Full"；当检测到Player_Status_Rage_None标签时，取消能力。
>
> 实现无敌功能：打开GE_Shared_DealDamage，在Gameplay Effect处添加新的元素，Target Tag Reqs选择Target Tag Requirements Gameplay Effect Component，Must Not Have Tags配置Shared.Status.Invincible。
> > Gameplay Effect就我目前的理解来讲，就是对attribute进行修改时需要用到的类。我们在此类中配置如何影响属性，之后在其他地方（比如能力蓝图）应用gameplay effect，从而达到修改属性的作用。

</details>

<details>

<summary>
    
### 9-8 Consume Rage

</summary>

> 本节实现愤怒技能开启时，持续消耗rage量的功能：首先创建一个gameplay effect，配置好对应内容，之后在能力蓝图中进行应用/移除即可实现该功能。

</details>

<details>

<summary>
    
### 9-9 Set Up Rage Slash

</summary>

> 愤怒技能开启后，对攻击进行强化，本课选用的方式是生成一个投射物：创建蓝图，添加粒子特效及音效。

</details>

<details>

<summary>
    
### 9-10 Spawn Rage Slash

</summary>

> 在近战技能蓝图中生成slash，生成之前需要检查一下是否处于愤怒技能启用的时刻，然后自定义事件在蓝图中实现具体的功能。
> > 之所以自定义事件而不是自定义蓝图，是因为事件是**异步**的，可以在多个游戏帧上执行，包含需要跨越帧的操作；而函数是**同步**的，被调用时会立即执行完所有指令并返回结果，不会跨越多个游戏帧。像是ability task和delay这种节点，与异步操作和事件管理相关，因此选择了自定义事件。
>
> 子类中实现自定义事件，其实也就是生成具体的slash，值得一提的是，此处需要在axe上增加一个新的插槽，通过这个插槽位置来控制slash生成的位置。
>
> 在montage中发送事件。

</details>

<details>

<summary>
    
### 9-11 On Rage Slash Begin Overlap

</summary>

> 我们不想让slash碰到敌人后立即消失，而是可以穿透攻击多个敌人：修改ProjectileDamagePolicy属性（这是我们在AWarriorProjectileBase中定义的枚举）为OnBeginOverlap，此时发现slash不会碰撞后就消失，但也无法造成伤害，此时需要我们完善AWarriorProjectileBase类中的回调函数OnProjectileBeginOverlap，补充伤害逻辑。

</details>

<details>

<summary>
    
### 9-12 Rage Slash For All Attacks

</summary>

> 给剩余的轻攻击和重攻击增加rage slash功能。

</details>

<details>

<summary>
    
### 9-13 Gain Rage

</summary>

> 通过攻击增加rage：首先创建一个gameplay effect，之后在近战能力蓝图（比如GA_Hero_LightAttackMaster）中，在攻击成功时调用一下apply gameplay effect to owner节点。

</details>

<details>

<summary>
    
### 9-14 Special Weapon Ability Tags

</summary>

> 本节开始增加特殊武器技能：首先是声明和定义tags，然后创建能力蓝图，并配置相应tag，之后是输入绑定，此次不一样的地方在于，特殊武器能力需要多个键位联动触发，比如alt + 鼠标左键，因此需要创建一个input action作为trigger，并在mapping context中进行设置。

</details>

<details>

<summary>
    
### 9-15 Grant Special Weapon Ability

</summary>

> 在WarriorStructTypes中创建FWarriorHeroSpecialAbilitySet，并在FWarriorHeroWeaponData中添加武器特殊能力数组，并在UWarriorAbilitySystemComponent::GrantHeroWeaponAbilities能进行能力的授予（该函数在GA_Hero_EquipAxe蓝图中被调用）。

</details>

<details>

<summary>
    
### 9-16 Light Ability Montage

</summary>

> 添加特殊技能的montage。

</details>

<details>

<summary>
    
### 9-17 Light Ability Damage

</summary>

> 添加伤害处理流程。（自行实现的！）

</details>

<details>

<summary>
    
### 9-18 Cooldown Gameplay Effect

</summary>

> 在能力蓝图details面板的最下方有cooldown的设置，需要创建一个cooldown的gameplay effect，配置相关内容，应用到能力蓝图上。

</details>

<details>

<summary>
    
### 9-19 Ability Icon Widget

</summary>

> 添加技能冷却图标，本节主要是创建Ability Icon Slot并绘制在Hero Overlay上面。

</details>

<details>

<summary>
    
### 9-20 On Ability Icon Updated

</summary>

> UHeroUIComponent创建新的委托类型，更新特殊技能的图标。
>
> 在BP_HeroAxe蓝图中遍历特殊技能，进行广播。
>
> 创建图标实例。

</details>

<details>

<summary>
    
### 9-21 Listen For Ability Icon Change

</summary>

> 我们在UHeroUIComponent中声明了委托类型OnAbilityIconSlotUpdated，之后在TPWBP_AbilityIconSlot蓝图中，调用Bind Event to On Ability Icon Slot Updated，顾名思义也就是给委托变量绑定事件，通过事件实现当角色装备武器时，显示轻攻击特殊技能的icon逻辑。那么什么时候委托函数会执行呢？GA_Hero_EquipAxe蓝图中调用节点Call On Ability Icon Slot Updated。
> 
> 卸下装备时，icon消失的逻辑也是同理。

</details>

<details>

<summary>
    
### 9-22 Notify Ability Cooldown

</summary>

> 在UHeroUIComponent中声明新的委托类型FOnAbilityCooldownBeginDelegate，之后能力蓝图中调用Call On Ability Cooldown Begin，再就是在TPWBP_AbilityIconSlot蓝图中绑定事件，显示冷却时间。（整体实现逻辑与上一讲差不多）

</details>

<details>

<summary>
    
### 9-23 Custom Latent Action

</summary>

> 下一步需要实现实时更新冷却时间的功能，可以通过event tick实现，但是据说计算逻辑会比较复杂。于是打算通过自定义latent action的方式解决问题。（delay节点时机上也是建立在latent action的基础上的，顺便也解开了我的疑惑，原来右上角时钟的图标表示是latent action）
>
> 本节主要讲解UWarriorFunctionLibrary类中如何将CountDown函数声明为Latent Action。

</details>

<details>

<summary>
    
### 9-24 Count Down Action Class

</summary>

> 本节在上一讲的基础上，创建Native Class——FWarriorCountDownAction以构建Latent Action。

</details>

<details>

<summary>
    
### 9-25 Construct Count Down Action

</summary>

> 编写UWarriorFunctionLibrary::CountDown逻辑，在LatentActionManager中检索/创建/取消FWarriorCountDownAction。

</details>

<details>

<summary>
    
### 9-26 Count Down Logic

</summary>

> 在FWarriorCountDownAction类中，重写父类FPendingLatentAction中的UpdateOperation函数，该函数每次tick都会调用，通过重写该函数实现倒计时逻辑。

</details>

<details>

<summary>
    
### 9-27 Update Cooldown

</summary>

> 在相关widget蓝图中，调用我们定义的count down节点，从而实现更新冷却时间及材质的功能。

</details>

<details>

<summary>
    
### 9-28 Resume Cooldown

</summary>

> 在UWarriorHeroGameplayAbility类中创建函数GetAbilityRemainingCooldownByTag，创建FGameplayEffectQuery，并通过GetAbilitySystemComponentFromActorInfo()->GetActiveEffectsTimeRemainingAndDuration()取得剩余的时间。在GA_Hero_EquipAxe中编写该节点相关逻辑，并调用委托事件，触发TPWBP_AbilityIconSlot中的OnAbilityCooldownBegin事件，使得再次装备武器时显示技能剩余冷却时间。

</details>

<details>

<summary>
    
### 9-29 Heavy Ability

</summary>

> 添加重攻击的特殊技能，配置输入操作，授予技能，并设置技能图标材质。

</details>

<details>

<summary>
    
### 9-30 Heavy Ability Montage

</summary>

> 创建重攻击特殊技能需要的montage。

</details>

<details>

<summary>
    
### 9-31 Heavy Ability Damage

</summary>

> 本讲开始讲解AOE伤害的实现逻辑，首先定义AOE相关标签，然后在UWarriorGameplayAbility类中定义ApplyGameplayEffectSpecHandleToHitResults方法，遍历每一个检测到的结果，如果是敌对的pawn，则调用SendGameplayEventToActor函数，给pawn发送受击事件通知。

</details>

<details>

<summary>
    
### 9-31 Heavy Ability Damage

</summary>

> 本讲开始讲解AOE伤害的实现逻辑，首先定义AOE相关标签，然后在UWarriorGameplayAbility类中定义ApplyGameplayEffectSpecHandleToHitResults方法，遍历每一个检测到的结果，如果是敌对的pawn，则调用SendGameplayEventToActor函数，给pawn发送受击事件通知。

</details>

<details>

<summary>
    
### 9-32 Apply AOE Damage

</summary>

> Bug Fixed: UDataAsset_HeroStartUpData类中FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant)这句代码编译的时候总是报错error C2665，应该是没有包含正确头文件导致的，所以添加了AbilitySystem/Abilities/WarriorHeroGameplayAbility.h头文件。
>
> 在montage中发送事件通知，能力蓝图中接收该通知，并在该通知以后通过box进行检测，对检测到的结果调用ApplyGameplayEffectSpecHandleToHitResults方法，对敌人造成【范围】伤害

</details>

<details>

<summary>
    
### 9-33 Commit Ability Cooldown

</summary>

> 给重攻击特殊技能设置冷却：基于之前逻辑的基础上，创建Gameplay Effect，在技能蓝图Cooldowns处选择创建的effect；在播放完蓝图之后，调用CommitAbility节点（确认技能的执行条件是否满足），并对委托事件进行广播，根据冷却时间更新icon的显示。

</details>

<details>

<summary>
    
### 9-34 Stone Class

</summary>

> 讲解恢复物品的功能逻辑：创建了基类AWarriorPickUpBase，设置USphereComponent属性，绑定委托函数；并派生子类AWarriorStoneBase。

</details>

<details>

<summary>
    
### 9-35 BP Stone

</summary>

> 创建stone蓝图类。

</details>

<details>

<summary>
    
### 9-36 Pick Up Ability

</summary>

> 为了便于检查和遍历，该能力通过C++类实现，先声明了需要重写的函数，定义相关标签，创建蓝图类配置标签，最后在DA_Hero中授予该能力。

</details>

<details>

<summary>
    
### 9-37 On Stone Begin Overlap

</summary>

> 在子类AWarriorStoneBase中重写函数OnPickUpCollisionSphereBeginOverlap以激活角色拾取石头的能力。

</details>

<details>

<summary>
    
### 9-38 Collect Stones

</summary>

> 在UHeroGameplayAbility_PickUpStones中创建CollectStones函数，通过UKismetSystemLibrary::BoxTraceMultiForObjects进行检测，在一定范围内搜索角色附近的石头：如果有的话，加入TArray数组；没有的话，则取消角色的拾取能力。
>
> Note: 重点在于BoxTraceMultiForObjects这个函数的参数怎么填写。

</details>

<details>

<summary>
    
### 9-39 Consume Stone Input

</summary>

> 绑定输入：当我们按下E键的时候，触发相关逻辑。因为并不是直接触发能力蓝图，所以在DA_InputConfig中添加为NativeInputActions，并在AWarriorHeroCharacter::SetupPlayerInputComponent中绑定Input_PickUpStonesStarted函数，发送gameplay event给actor。（其他输入绑定流程参照以前的操作）之后在能力蓝图中调用wait gameplay event节点，等待事件通知。

</details>

<details>

<summary>
    
### 9-40 Consume Stones

</summary>

> 接收到事件通知以后，调用ConsumeStones函数，遍历检测到的stone，调用AWarriorStoneBase::Consume方法，通过该方法施加gameplay effect。另外想要添加音效等逻辑，在AWarriorStoneBase类中定义BP_OnStoneConsumed方法，标记为BlueprintImplementableEvent，在蓝图中实现，并且在Consume方法中进行调用。

</details>

<details>

<summary>
    
### 9-41 On Stone Consumed

</summary>

> 在BP_StoneBase中编写蓝图逻辑，生成粒子特效和音效，并在子类中配置对应资源。创建gameplay effect之后也需要进行相应的配置。
>
> 对同时捡起多个石头时播放多次音效做了优化处理。

</details>

<details>

<summary>
    
### 9-42 Input Key Widget

</summary>

> 创建拾取石头时显示键位的UI，并设置为隐藏。

</details>

<details>

<summary>
    
### 9-43 Broadcast Display Input Key

</summary>

> 为了能够在正确的时机显示拾取键位的UI，我们选择在UHeroGameplayAbility_PickUpStones中激活或者结束能力式进行控制。为此，需要在UHeroUIComponent中创建委托变量，在UHeroGameplayAbility_PickUpStones中进行广播。

</details>

<details>

<summary>
    
### 9-44 Listen For Display Input Key

</summary>

> 绑定委托事件，在WBP_HeroOverlay中编写UI的显示逻辑，相对于硬编码的方式，本讲在蓝图中获取了MappingContext中配置的键位，以进行动态显示。

</details>

<details>

<summary>
    
### 9-45 Spawn Stone Ability

</summary>

> 生成恢复用的石头道具，作为敌人的一种能力，创建对应的标签和能力蓝图，进行能力的授予和激活。
>
> 因为选择在敌人死亡后生成道具，所以选择在BP_EnemyCharacter_Base蓝图中通过标签激活能力。（如果没有相应的能力，则不会进行激活）

</details>

<details>

<summary>
    
### 9-46 Spawn Stone Logic

</summary>

> 在GA_Enemy_SpawnStone_Base中编写道具的生成逻辑：通过line trace，检测到敌人位置对应的地面，并随机一个位置；通过概率判定生成哪一类道具or是否生成，异步加载资源，进行类型转换后生成道具。
>
> 值得注意的一点是，之前在BP_EnemyCharacter_Base蓝图中尝试激活能力之后直接对actor进行了销毁，而GA_Enemy_SpawnStone_Base中需要异步加载资源，很可能没加载完actor就被销毁，导致无法生成道具，此处尝试了一个比较简单直接的解决方式——调用delay节点。（个人感觉这种方法并不是很好，可以进一步探究有什么其他的方式）

</details>

<details>

<summary>
    
### 9-47 Glacer Spawn Stone Chance

</summary>

> 为Glacer添加死亡后生成道具的能力。

</details>

</details>

## Survival Game Mode
<details>
<summary>Lesson list</summary>

<details>

<summary>
    
### 10-3 Survival Game Mode Class

</summary>
    
> 创建新的GameMode，创建枚举类型和委托，重写函数，在SetCurrentCurrentSurvialGameModeState中对委托事件进行广播；生成GameMode蓝图类，并做对应的设置（修改Player Controller Class & Default Pawn Class），在World Settings中选对应的GameMode。

</details>

<details>

<summary>
    
### 10-4 Enemy Wave Spawner Table Row

</summary>
    
> 在EWarriorSurvialGameModeState中创建了两个结构体：FWarriorEnemyWaveSpawnerInfo与FWarriorEnemyWaveSpawnerTableRow。创建Data Table，存放相关信息。

</details>

<details>

<summary>
    
### 10-5 Wave Progression Logic

</summary>
    
> 在Gamemode中编写游戏生存模式不同状态的转换逻辑。

</details>

<details>

<summary>
    
### 10-6 Wave Count Down Widget

</summary>
    
> 制作倒计时需要用的widget，通过动画控制文字的显示效果；在event graph中播放动画，并且通过之前创建的count down函数更新text显示的秒数。

</details>

<details>

<summary>
    
### 10-7 Drawing Wave Count Down Widget

</summary>
    
> 在gamemode蓝图中显示widget，更改显示的文本，并调用widget中的函数start count down，传入参数控制倒计时时间。

</details>

<details>

<summary>
    
### 10-8 Wave Info Widget

</summary>
    
> 创建显示当前是轮次的widget。另外在AWarriorBaseGameMode类中启用tick能力，并且当actor实例化时，默认自动激活tick。

</details>

<details>

<summary>
    
### 10-9 Pre Load Next Wave Enemies

</summary>
    
> 本节开始讲解敌人的生成逻辑，主要包括三部分：预加载敌人类型，在关卡中生成敌人，处理敌人生成数量。
>
> 首先是如何预加载敌人类型，在AWarriorSurvivalGameMode中创建PreLoadNextWaveEnemies函数，获取到Data Table中当前轮次需要生成的敌人类型，并进行异步加载。

</details>

<details>

<summary>
    
### 10-10 Try Spawn Wave Enemies

</summary>
    
> 讲解敌人的生成代码，也就是gamemode中的TrySpawnWaveEnemies函数：获取关卡中的target points，遍历敌人类型，随机化生成位置，生成敌人等。【本节内容很重要】

</details>

<details>

<summary>
    
### 10-11 On Enemy Destroyed

</summary>
    
> 当敌人被消灭之后，如果还有剩余的敌人，并没有继续生成。要解决这个问题，可以通过OnDestroyed绑定委托函数，从而继续生成敌人。

</details>

<details>

<summary>
    
### 10-12 On Wave Completed

</summary>
    
> 当前轮次结束时，显示widget；在Data Table中配置第二轮次的敌人。

</details>

<details>

<summary>
    
### 10-13 Playtesting Game Mode

</summary>
    
> 测试游戏模式，发现一个问题：glacer入场的时候立即播放动画。修改了行为树Observer aborts，等待3秒。

</details>

<details>

<summary>
    
### 10-14 Register Spawned Enemies

</summary>
    
> 解决另一个问题：当boss召唤guardian之后，boss死亡显示当前轮次结束。该问题的原因是gamemode并不知道boss的召唤能力，因此创建RegisterSpawnedEnemies函数，将生成的敌人注册到gamemode中，增加CurrentSpawnedEnemiesCounter的数量，并调用委托函数；同时在召唤能力的蓝图中调用RegisterSpawnedEnemies节点。

</details>

<details>

<summary>
    
### 10-15 Notify Last Wave

</summary>
    
> 最后一波时用UI进行提示。

</details>

<details>

<summary>
    
### 10-16 On Player Died

</summary>
    
> 在角色死亡能力中调用gamemode变化时的委托事件，从而通知gamemode角色已经死亡。

</details>

<details>

<summary>
    
### 10-17 Game Difficulty

</summary>
    
> 创建新的枚举类表示游戏的难度，在hero和enemy的角色类中，通过游戏难度调整AbilityApplyLevel，从而在调用GiveToAbilitySystemComponent函数时传入不同的参数，以影响技能和gameplay effect的数值，进而影响游戏难度。

</details>

<details>

<summary>
    
### 10-18 Verify Game Difficulty

</summary>
    
> 验证调整游戏难度是否有效。

</details>

</details>

## In-Game Widgets
<details>
<summary>Lesson list</summary>

<details>

<summary>
    
### 11-2 Template Button Widget

</summary>
    
> 创建button模板。

</details>

<details>

<summary>
    
### 11-3 Pause Menu Template Button

</summary>
    
> 创建暂停按钮的模板，在按钮的OnClicked事件中，创建Event Dispatchers，将事件转发给其他widget。 

</details>

<details>

<summary>
    
### 11-4 Lose Screen

</summary>
    
> 制作失败界面，并在关卡蓝图中创建该界面进行展示。

</details>

<details>

<summary>
    
### 11-5 Lose Screen Animation

</summary>
    
> 制作失败界面的动画效果，并在事件蓝图中播放动画。

</details>

<details>

<summary>
    
### 11-6 Drawing Lose Screen

</summary>
    
> 在gamemode中，编写当角色死亡时绘制失败屏幕的逻辑。

</details>

<details>

<summary>
    
### 11-7 Warrior Game Instance

</summary>
    
> 在编写重新尝试按钮的逻辑时，希望访问一些全局变量，所以考虑使用游戏实例：它是一个全局对象，与游戏的生命周期相同。创建UWarriorGameInstance类，并在函数库中返回游戏实例，同时在项目设置中配置游戏实例生成的蓝图子类。

</details>

<details>

<summary>
    
### 11-8 Get Game Level By Tag

</summary>
    
> 在UWarriorGameInstance中创建结构体FWarriorGameLevelSet，以及需要用到的变量及函数。

</details>

<details>

<summary>
    
### 11-9 Open Level

</summary>
    
> 在GameInstance蓝图中配置关卡和标签，在widget按钮事件中获取game instance，通过tag确定想要打开的关卡。

</details>

<details>

<summary>
    
### 11-10 Toggle Input Mode

</summary>
    
> 解决上节课遗留下的问题：重新开始游戏后，无法控制角色移动了。为此创建了UWarriorFunctionLibrary::ToggleInputMode函数，设置输入模式，当重新开始游戏后，调用该节点。

</details>

<details>

<summary>
    
### 11-11 Win Screen Widget

</summary>
    
> 创建win screen widget。

</details>

<details>

<summary>
    
### 11-12 Drawing Win Screen

</summary>
    
> 在gamemode中绘制win screen。

</details>

<details>

<summary>
    
### 11-13 Pause Menu Widget

</summary>
    
> 创建暂停屏幕，在事件蓝图中编写widget创建时的暂停逻辑。

</details>

<details>

<summary>
    
### 11-14 Drawing Pause Menu

</summary>
    
> 绑定输入映射，按Esc时显示暂停屏幕。（在编辑器中需要按Shift + Esc）

</details>

<details>

<summary>
    
### 11-15 Main Menu Map

</summary>
    
> 制作主菜单，创建了一个新的level，保存为map，加入相关元素并更换gamemode。

</details>

<details>

<summary>
    
### 11-16 Main Menu Button Template

</summary>
    
> 制作主菜单button的widget模板。

</details>

<details>

<summary>
    
### 11-17 Main Menu Widget

</summary>
    
> 制作主菜单widget，并在gamemode中生成。

</details>

<details>

<summary>
    
### 11-18 Main Menu Animation and Logic

</summary>
    
> 给主菜单添加动画，并添加按钮逻辑；同时给之前创建的screen添加跳转到主菜单的逻辑。

</details>

</details>
