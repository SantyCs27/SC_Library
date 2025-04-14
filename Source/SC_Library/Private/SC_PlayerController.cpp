// Copyright Santiago Cañas. All Rights Reserved.


#include "SC_PlayerController.h"
#include "Runtime/Slate/Public/Framework/Application/SlateApplication.h"
#include "Runtime/Slate/Public/Framework/Application/NavigationConfig.h"

ASC_PlayerController::ASC_PlayerController()
{
}

void ASC_PlayerController::BeginPlay()
{
	// Navigation W A S D

	Super::BeginPlay();
	FSlateApplication::Get().GetNavigationConfig().Get().KeyEventRules.Emplace(EKeys::A, EUINavigation::Left);
	FSlateApplication::Get().GetNavigationConfig().Get().KeyEventRules.Emplace(EKeys::S, EUINavigation::Down);
	FSlateApplication::Get().GetNavigationConfig().Get().KeyEventRules.Emplace(EKeys::W, EUINavigation::Up);
	FSlateApplication::Get().GetNavigationConfig().Get().KeyEventRules.Emplace(EKeys::D, EUINavigation::Right);

	// Loses Focus

	FSlateApplication::Get().OnApplicationActivationStateChanged()
		.AddUObject(this, &ASC_PlayerController::OnWindowFocusChanged);
}



// Loses Focus

void ASC_PlayerController::OnWindowFocusChanged_Implementation(bool bIsFocused)
{
}
