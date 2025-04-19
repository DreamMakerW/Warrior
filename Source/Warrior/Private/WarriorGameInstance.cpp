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
    // 加载屏幕至少加载时间
    LoadingScreenAttributes.MinimumLoadingScreenDisplayTime = 2.f;
    LoadingScreenAttributes.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();

    // 通过该方式加载loading screen，确保loading screen运行在不同的线程上
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
