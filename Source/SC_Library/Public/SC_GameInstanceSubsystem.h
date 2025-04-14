// Copyright Santiago Cañas. All Rights Reserved.

#pragma once


#include "Subsystems/GameInstanceSubsystem.h"
#include "SC_GameInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SC_LIBRARY_API USC_GameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
		FOnApplicationWindowStateChangedSignature,
		bool, bIsActive);

public:
	//~UGameInstanceSubsystem Interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	//~End of UGameInstanceSubsystem Interface

	UFUNCTION(BlueprintPure, Category = "A_SC_Library|SlateSub")
	bool IsApplicationWindowActive() const;

private:
	void OnWindowFocusChanged(bool bIsActive);

public:
	UPROPERTY(BlueprintAssignable, Category = "A_SC_Library|SlateSub")
	FOnApplicationWindowStateChangedSignature OnApplicationWindowStateChanged;

public:
	bool bIsApplicationWindowActive = false;

};
