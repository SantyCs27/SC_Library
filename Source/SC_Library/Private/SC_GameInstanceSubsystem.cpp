// Copyright Santiago Cañas. All Rights Reserved.


#include "SC_GameInstanceSubsystem.h"
#include "Runtime/Slate/Public/Framework/Application/SlateApplication.h"

void USC_GameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	auto& SlateApplication = FSlateApplication::Get();
	SlateApplication.OnApplicationActivationStateChanged().AddUObject(this, &ThisClass::OnWindowFocusChanged);
}

bool USC_GameInstanceSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (IsRunningDedicatedServer())
	{
		return false;
	}

	return Super::ShouldCreateSubsystem(Outer);
}

bool USC_GameInstanceSubsystem::IsApplicationWindowActive() const
{
	return bIsApplicationWindowActive;
}

void USC_GameInstanceSubsystem::OnWindowFocusChanged(bool bIsActive)
{
	bIsApplicationWindowActive = bIsActive;
	OnApplicationWindowStateChanged.Broadcast(bIsApplicationWindowActive);
}