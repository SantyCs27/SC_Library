// Copyright Santiago Cañas. All Rights Reserved.


#include "SC_GameInstance.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "MoviePlayer.h"

void USC_GameInstance::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &USC_GameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &USC_GameInstance::EndLoadingScreen);
}

void USC_GameInstance::BeginLoadingScreen_Implementation(const FString& InMapName)
{
	if (!IsRunningDedicatedServer())
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;

		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), LoadingScreenWidget);
		LoadingScreen.WidgetLoadingScreen = Widget->TakeWidget();

		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
}

void USC_GameInstance::EndLoadingScreen_Implementation(UWorld* InLoadedWorld)
{

}
