// Copyright Santiago Cañas. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "SC_GameViewportClient.generated.h"


DECLARE_DYNAMIC_DELEGATE(FOnUserWindowCloseRequested);

static FOnUserWindowCloseRequested UserWindowCloseRequested;

UCLASS(BlueprintType, Category = "A_SC_Library|GameViewportClient")
class SC_LIBRARY_API USC_GameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()
	
	virtual bool WindowCloseRequested() override;

public:

	UFUNCTION(BlueprintCallable, Category = "A_SC_Library|GameViewportClient")
	static void SetAllowWindowClose(bool bAllowWindowClose);

	UFUNCTION(BlueprintCallable, Category = "A_SC_Library|GameViewportClient")
	static bool GetAllowWindowClose();

	UFUNCTION(BlueprintCallable, Category = "A_SC_Library|GameViewportClient")
	static void BindOnUserWindowCloseRequested(FOnUserWindowCloseRequested OnUserWindowCloseRequested);

private:
	static bool bAllowWindowClosing;

};
