// Wyy All Rights Reserved


#include "WarriorGameInstance.h"
#include "MoviePlayer.h"
#include "WarriorDebugHelper.h"

void UWarriorGameInstance::Init()
{
    Super::Init();

    FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &ThisClass::OnPreLoadMap);
    FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &ThisClass::OnDestinationWorldLoaded);

}


void UWarriorGameInstance::OnPreLoadMap(const FString& MapName)
{
    FLoadingScreenAttributes LoadingScreenAttributes;
    LoadingScreenAttributes.bAutoCompleteWhenLoadingCompletes = true;
    // ������Ļ���ټ���ʱ��
    LoadingScreenAttributes.MinimumLoadingScreenDisplayTime = 2.f;
    LoadingScreenAttributes.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();

    // ͨ���÷�ʽ����loading screen��ȷ��loading screen�����ڲ�ͬ���߳���
    GetMoviePlayer()->SetupLoadingScreen(LoadingScreenAttributes);
}

void UWarriorGameInstance::OnDestinationWorldLoaded(UWorld* LoadedWorld)
{
    // close the loading screen
    GetMoviePlayer()->StopMovie();
}

TSoftObjectPtr<UWorld> UWarriorGameInstance::GetGameLevelByTag(FGameplayTag InTag) const
{
    for (const FWarriorGameLevelSet& GameLevelSet : GameLevelSets)
    {
        if (!GameLevelSet.IsValid()) continue;
        if (GameLevelSet.LevelTag == InTag)
        {
            return GameLevelSet.Level;
        }
    }
    return TSoftObjectPtr<UWorld>();
}
