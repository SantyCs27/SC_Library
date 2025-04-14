// Copyright Santiago Cañas. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SC_GameInstance.generated.h"


UCLASS()
class SC_LIBRARY_API USC_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (DisplayName = "BeginLoadingScreen"), Category = "A_SC_Library|Loading")
	void BeginLoadingScreen(const FString& MapName);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (DisplayName = "EndLoadingScreen"), Category = "A_SC_Library|Loading")
	void EndLoadingScreen(UWorld* InLoadedWorld);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "A_SC_Library|Loading")
	TSubclassOf<class UUserWidget> LoadingScreenWidget;

};
