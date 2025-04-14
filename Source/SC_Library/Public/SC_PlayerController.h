// Copyright Santiago Cañas. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SC_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SC_LIBRARY_API ASC_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASC_PlayerController();

	virtual void BeginPlay() override;

	/***** Loses Focus *****/

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (DisplayName = "Loses Focus"), Category = "A_SC_Library|General")
	void OnWindowFocusChanged(bool bIsFocused);

};
