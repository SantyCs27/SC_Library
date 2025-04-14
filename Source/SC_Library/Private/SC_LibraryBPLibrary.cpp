// Copyright Santiago Cañas. All Rights Reserved.

#include "SC_LibraryBPLibrary.h"
#include "SC_Library.h"

#include "Engine/Engine.h"
#include "Runtime/Engine/Classes/GameFramework/GameUserSettings.h"
#include "Windows/WindowsHWrapper.h"
#include "Engine/GameViewportClient.h"

// Display
#include "GenericPlatform/GenericApplication.h"
#include "Widgets/SWindow.h"
#include "Runtime/Core/Public/Misc/CommandLine.h"

// Audio
#include <mmdeviceapi.h>
#include "Runtime/Engine/Public/AudioDevice.h"

#include <Functiondiscoverykeys_devpkey.h>
#include <mmsystem.h>

// Get Selected Paths and Save Assets
#if WITH_EDITOR
#include "Editor/UnrealEd/Public/FileHelpers.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"

// Blueprint Compiler
#include "Kismet2/KismetEditorUtilities.h"
#include "Kismet2/CompilerResultsLog.h"
#endif

// Project Settings
#include "GeneralProjectSettings.h"


THIRD_PARTY_INCLUDES_START
#include "Windows/AllowWindowsPlatformTypes.h"
#include "dxgi1_4.h"
#include "Windows/HideWindowsPlatformTypes.h"
THIRD_PARTY_INCLUDES_END


USC_LibraryBPLibrary::USC_LibraryBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

// Another App Instance

void USC_LibraryBPLibrary::AnotherAppInstance(bool bEnabled)
{
#if !UE_EDITOR	

	const UGeneralProjectSettings& ProjectSettings = *GetDefault<UGeneralProjectSettings>();
	const FString LockFilePath = FPlatformProcess::UserTempDir() + ProjectSettings.ProjectID.ToString();
	if (!IFileManager::Get().CreateFileWriter(*LockFilePath, 0) && bEnabled)
	{
		FPlatformApplicationMisc::RequestMinimize();
		FPlatformMisc::RequestExit(0);
	}
#endif
}



// Display Switching Functions

int USC_LibraryBPLibrary::GetDisplayCount()
{
	FDisplayMetrics Displays;
	FDisplayMetrics::RebuildDisplayMetrics(Displays);

	return Displays.MonitorInfo.Num();
}

TArray<FDisplayInfo> USC_LibraryBPLibrary::GetAllDisplays()
{
	TArray<FDisplayInfo> AllDisplays;

	FDisplayMetrics Displays;
	FDisplayMetrics::RebuildDisplayMetrics(Displays);

	for (const FMonitorInfo& Monitor : Displays.MonitorInfo)
	{
		AllDisplays.Add(FDisplayInfo(Monitor.Name, Monitor.ID, Monitor.NativeWidth, Monitor.NativeHeight, Monitor.MaxResolution, Monitor.bIsPrimary, Monitor.DPI));
	}

	return AllDisplays;
}

int32 USC_LibraryBPLibrary::GetPrimaryMonitor()
{
	FDisplayMetrics Display;
	FDisplayMetrics::RebuildDisplayMetrics(Display);

	int32 MonitorNumber = 0;
	FParse::Value(FCommandLine::Get(), TEXT("monitor="), MonitorNumber);

	int32 MonitorIndex = INDEX_NONE;
	if (MonitorNumber == 0)
	{
		for (int32 Index = 0; Index < Display.MonitorInfo.Num(); Index++)
		{
			if (Display.MonitorInfo[Index].bIsPrimary)
			{
				MonitorIndex = Index;
				break;
			}
		}
	}
	else
	{
		MonitorIndex = MonitorNumber - 1;
	}

	return MonitorIndex;
}

bool USC_LibraryBPLibrary::SetActiveDisplay(int32 DisplayIndex)
{
	FDisplayMetrics Displays;
	FDisplayMetrics::RebuildDisplayMetrics(Displays);

	if (DisplayIndex > Displays.MonitorInfo.Num())
	{
		// Non existing diplay
		return false;
	}

	const FMonitorInfo TargetMonitor = Displays.MonitorInfo[DisplayIndex];
	//TargetMonitor.WorkArea.
	FVector2D WindowPosition(static_cast<float>(TargetMonitor.WorkArea.Left), static_cast<float>(TargetMonitor.WorkArea.Top));

	if (GEngine && GEngine->GameViewport)
	{
		//Display switching
		TSharedPtr<SWindow> GWindow = GEngine->GameViewport->GetWindow();
		GWindow->MoveWindowTo(WindowPosition);

		//Setting resolution
		UGameUserSettings* UserSettings = GEngine->GameUserSettings;
		UserSettings->SetScreenResolution(FIntPoint(TargetMonitor.NativeWidth, TargetMonitor.NativeHeight));
		UserSettings->ApplyResolutionSettings(false);

	}
	return true;
}



// Minimize, Maximize And Restore Window

void USC_LibraryBPLibrary::MinimizeWindow()
{
	// Check if the Unreal Engine and its GameViewport are valid.
	if (GEngine && GEngine->GameViewport)
	{
		// Retrieve the native window handle.
		HWND WindowHandle = (HWND)GEngine->GameViewport->GetWindow()->GetNativeWindow()->GetOSWindowHandle();

		ShowWindow(WindowHandle, SW_MINIMIZE);
	}
}

void USC_LibraryBPLibrary::MaximizeWindow()
{
	// Check if the Unreal Engine and its GameViewport are valid.
	if (GEngine && GEngine->GameViewport)
	{
		// Retrieve the native window handle.
		HWND WindowHandle = (HWND)GEngine->GameViewport->GetWindow()->GetNativeWindow()->GetOSWindowHandle();

		ShowWindow(WindowHandle, SW_MAXIMIZE);
	}
}

void USC_LibraryBPLibrary::RestoreWindow()
{
	// Check if the Unreal Engine and its GameViewport are valid.
	if (GEngine && GEngine->GameViewport)
	{
		// Retrieve the native window handle.
		HWND WindowHandle = (HWND)GEngine->GameViewport->GetWindow()->GetNativeWindow()->GetOSWindowHandle();

		ShowWindow(WindowHandle, SW_RESTORE);
	}
}



// Graphics Card

FString USC_LibraryBPLibrary::GetPrimaryGraphicsCardName()
{
#if PLATFORM_WINDOWS

	FString GraphicsCardName = "Unknown";
	DISPLAY_DEVICE DisplayDevice;
	DisplayDevice.cb = sizeof(DisplayDevice);
	if (EnumDisplayDevices(nullptr, 0, &DisplayDevice, 0))
	{
		GraphicsCardName = DisplayDevice.DeviceString;
	}
	return GraphicsCardName;

#else
	return FString("None");
#endif
}

int USC_LibraryBPLibrary::UsedVRAM()
{
	IDXGIFactory4* pFactory;
	CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void**)&pFactory);

	IDXGIAdapter3* adapter;
	pFactory->EnumAdapters(0, reinterpret_cast<IDXGIAdapter**>(&adapter));

	DXGI_QUERY_VIDEO_MEMORY_INFO videoMemoryInfo;
	adapter->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &videoMemoryInfo);

	size_t usedVRAM = videoMemoryInfo.CurrentUsage / 1024 / 1024;

	return usedVRAM;
}

int USC_LibraryBPLibrary::AvailableVRAM()
{
	IDXGIFactory4* pFactory;
	CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void**)&pFactory);

	IDXGIAdapter3* adapter;
	pFactory->EnumAdapters(0, reinterpret_cast<IDXGIAdapter**>(&adapter));

	DXGI_QUERY_VIDEO_MEMORY_INFO videoMemoryInfo;
	adapter->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &videoMemoryInfo);

	size_t availableVRAM = videoMemoryInfo.AvailableForReservation / 1024 / 1024;

	return availableVRAM;
}

int32 USC_LibraryBPLibrary::TotalVRAM()
{
#if PLATFORM_WINDOWS
	int32 GraphicsRAMSizeMB = 0;
	IDXGIFactory* DXGIFactory;
	if (SUCCEEDED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&DXGIFactory)))
	{
		IDXGIAdapter* Adapter;
		if (SUCCEEDED(DXGIFactory->EnumAdapters(0, &Adapter)))
		{
			DXGI_ADAPTER_DESC AdapterDesc;
			if (SUCCEEDED(Adapter->GetDesc(&AdapterDesc)))
			{
				GraphicsRAMSizeMB = static_cast<int32>(AdapterDesc.DedicatedVideoMemory / (1024 * 1024));
			}
			Adapter->Release();
		}
		DXGIFactory->Release();
	}
	return GraphicsRAMSizeMB;
#else
	return 0;
#endif
}



// RAM

int32 USC_LibraryBPLibrary::GetRamSize()
{
#if PLATFORM_WINDOWS
	MEMORYSTATUSEX MemoryStatus;
	MemoryStatus.dwLength = sizeof(MemoryStatus);
	GlobalMemoryStatusEx(&MemoryStatus);
	int32 RAMSizeInMB = FMath::RoundToInt(MemoryStatus.ullTotalPhys / (1024.0f * 1024.0f));
	return RAMSizeInMB;
#else

	return 0;
#endif
}

FMemInfoSC USC_LibraryBPLibrary::GetMemoryInformation()
{
	FMemInfoSC MemoryInformation;
#if PLATFORM_WINDOWS

	MemoryInformation.PhysicalMemoryUsedInGb = FPlatformMemory::GetStats().UsedPhysical >> 20;
	MemoryInformation.PhysicalMemoryAvailableInGb = FPlatformMemory::GetStats().AvailablePhysical >> 20;
	MemoryInformation.TotalMemoryInGb = FPlatformMemory::GetStats().TotalPhysical >> 20;

	return MemoryInformation;

#else
	return 0;
#endif
}



// Sound

FString USC_LibraryBPLibrary::GetCurrentAudioOutputDevice()
{
#if PLATFORM_WINDOWS


	IMMDeviceEnumerator* pEnumerator = NULL;
	IMMDevice* pDevice = NULL;
	IPropertyStore* pProps = NULL;
	LPWSTR pwszID = NULL;
	HRESULT hr = CoInitialize(NULL);
	if (SUCCEEDED(hr))
	{
		hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pEnumerator);
	}
	if (SUCCEEDED(hr))
	{
		hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
	}
	if (SUCCEEDED(hr))
	{
		hr = pDevice->GetId(&pwszID);
	}
	if (SUCCEEDED(hr))
	{
		hr = pDevice->OpenPropertyStore(STGM_READ, &pProps);
	}
	if (SUCCEEDED(hr))
	{
		PROPVARIANT varName;
		PropVariantInit(&varName);
		hr = pProps->GetValue(PKEY_Device_FriendlyName, &varName);
		if (SUCCEEDED(hr))
		{
			FString SpeakerName = FString(varName.pwszVal);
			CoTaskMemFree(pwszID);
			PropVariantClear(&varName);
			pProps->Release();
			pDevice->Release();
			pEnumerator->Release();
			return SpeakerName;
		}
	}
	if (pwszID != NULL)
	{
		CoTaskMemFree(pwszID);
	}
	if (pProps != NULL)
	{
		pProps->Release();
	}
	if (pDevice != NULL)
	{
		pDevice->Release();
	}
	if (pEnumerator != NULL)
	{
		pEnumerator->Release();
	}
	return FString();
#else
	return FString("None");
#endif
}

void USC_LibraryBPLibrary::GetAllAudioOutputDevices(TArray<FString>& OutAudioDeviceNames)
{
	FAudioDeviceHandle audioDevice = FAudioDevice::GetMainAudioDevice();
	if (audioDevice.IsValid())
	{
		audioDevice->GetAudioDeviceList(OutAudioDeviceNames);
	}
}



// CPU

float USC_LibraryBPLibrary::GetCPUUsage()
{
#if PLATFORM_WINDOWS

	return FWindowsPlatformTime::GetCPUTime().CPUTimePct;

#else
	return 0;
#endif
}



// Project Settings

FString USC_LibraryBPLibrary::GetProjectName()
{
	const UGeneralProjectSettings& ProjectSettings = *GetDefault<UGeneralProjectSettings>();
	return ProjectSettings.ProjectName;
}

FString USC_LibraryBPLibrary::GetProjectVersion()
{
	const UGeneralProjectSettings& ProjectSettings = *GetDefault<UGeneralProjectSettings>();
	return ProjectSettings.ProjectVersion;
}

FText USC_LibraryBPLibrary::GetProjectDisplayedTitle()
{
	const UGeneralProjectSettings& ProjectSettings = *GetDefault<UGeneralProjectSettings>();
	return ProjectSettings.ProjectDisplayedTitle;
}

bool USC_LibraryBPLibrary::GetAllowClose()
{
	const UGeneralProjectSettings& ProjectSettings = *GetDefault<UGeneralProjectSettings>();
	return ProjectSettings.bAllowClose;
}

bool USC_LibraryBPLibrary::GetAllowMaximize()
{
	const UGeneralProjectSettings& ProjectSettings = *GetDefault<UGeneralProjectSettings>();
	return ProjectSettings.bAllowMaximize;
}

bool USC_LibraryBPLibrary::GetAllowMinimize()
{
	const UGeneralProjectSettings& ProjectSettings = *GetDefault<UGeneralProjectSettings>();
	return ProjectSettings.bAllowMinimize;
}

bool USC_LibraryBPLibrary::GetAllowWindowResize()
{
	const UGeneralProjectSettings& ProjectSettings = *GetDefault<UGeneralProjectSettings>();
	return ProjectSettings.bAllowWindowResize;
}

bool USC_LibraryBPLibrary::GetBorderlessWindow()
{
	const UGeneralProjectSettings& ProjectSettings = *GetDefault<UGeneralProjectSettings>();
	return ProjectSettings.bUseBorderlessWindow;
}

bool USC_LibraryBPLibrary::GetWindowPreserveAspectRatio()
{
	const UGeneralProjectSettings& ProjectSettings = *GetDefault<UGeneralProjectSettings>();
	return ProjectSettings.bUseBorderlessWindow;
}

void USC_LibraryBPLibrary::SetProjectName(const FString& ProjectName)
{
	UGeneralProjectSettings* ProjectSettings = GetMutableDefault<UGeneralProjectSettings>();
	ProjectSettings->ProjectName = ProjectName;
	ProjectSettings->SaveConfig();
}

void USC_LibraryBPLibrary::SetProjectVersion(const FString& ProjectVersion)
{
	UGeneralProjectSettings* ProjectSettings = GetMutableDefault<UGeneralProjectSettings>();
	ProjectSettings->ProjectVersion = ProjectVersion;
	ProjectSettings->SaveConfig();
}

void USC_LibraryBPLibrary::SetProjectDisplayedTitle(const FText& ProjectDisplayedTitle)
{
	UGeneralProjectSettings* ProjectSettings = GetMutableDefault<UGeneralProjectSettings>();
	ProjectSettings->ProjectDisplayedTitle = ProjectDisplayedTitle;
	ProjectSettings->SaveConfig();
}

void USC_LibraryBPLibrary::SetAllowClose(bool AllowClose)
{
	UGeneralProjectSettings* ProjectSettings = GetMutableDefault<UGeneralProjectSettings>();
	ProjectSettings->bAllowClose = AllowClose;
	ProjectSettings->SaveConfig();
}

void USC_LibraryBPLibrary::SetAllowMaximize(bool AllowMaximize)
{
	UGeneralProjectSettings* ProjectSettings = GetMutableDefault<UGeneralProjectSettings>();
	ProjectSettings->bAllowMaximize = AllowMaximize;
	ProjectSettings->SaveConfig();
}

void USC_LibraryBPLibrary::SetAllowMinimize(bool AllowMinimize)
{
	UGeneralProjectSettings* ProjectSettings = GetMutableDefault<UGeneralProjectSettings>();
	ProjectSettings->bAllowMinimize = AllowMinimize;
	ProjectSettings->SaveConfig();
}

void USC_LibraryBPLibrary::SetAllowWindowResize(bool AllowWindowResize)
{
	UGeneralProjectSettings* ProjectSettings = GetMutableDefault<UGeneralProjectSettings>();
	ProjectSettings->bAllowWindowResize = AllowWindowResize;
	ProjectSettings->SaveConfig();
}

void USC_LibraryBPLibrary::SetBorderlessWindow(bool BorderlessWindow)
{
	UGeneralProjectSettings* ProjectSettings = GetMutableDefault<UGeneralProjectSettings>();
	ProjectSettings->bUseBorderlessWindow = BorderlessWindow;
	ProjectSettings->SaveConfig();
}

void USC_LibraryBPLibrary::SetWindowPreserveAspectRatio(bool WindowPreserveAspectRatio)
{
	UGeneralProjectSettings* ProjectSettings = GetMutableDefault<UGeneralProjectSettings>();
	ProjectSettings->bShouldWindowPreserveAspectRatio = WindowPreserveAspectRatio;
	ProjectSettings->SaveConfig();
}



// Windows Foreground

bool USC_LibraryBPLibrary::SetWindowAlwaysOnTop(bool bOnTop)
{
	HWND ParentWindow = (HWND)GEngine->GameViewport->GetWindow()->GetNativeWindow()->GetOSWindowHandle();
	if (bOnTop)
	{
		SetWindowPos(ParentWindow, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
	else
	{
		SetWindowPos(ParentWindow, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
	return bOnTop;
}

bool USC_LibraryBPLibrary::GetWindowAlwaysOnTop()
{
	HWND ParentWindow = (HWND)GEngine->GameViewport->GetWindow()->GetNativeWindow()->GetOSWindowHandle();
	if (GetWindowLong(ParentWindow, GWL_EXSTYLE) & WS_EX_TOPMOST)
	{
		return true;
	}

	else
	{
		return false;
	}
}



// Windows

FVector2D USC_LibraryBPLibrary::GetMainWindowPos()
{
	return GEngine->GameViewport->GetWindow().ToSharedRef().Get().GetPositionInScreen();
}

void USC_LibraryBPLibrary::SetMainWindowPosition(FVector2D InNewPosition)
{
	GEngine->GameViewport->GetWindow().ToSharedRef().Get().MoveWindowTo(InNewPosition);
}



#if WITH_EDITOR
// Blueprint Compiler

void USC_LibraryBPLibrary::CompileBlueprint(FString BlueprintPath, bool& bOutSuccess, FString& OutInfoMessage)
{

	// Load Blueprint Asset
	UBlueprint* Blueprint = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), nullptr, *BlueprintPath));

	if (Blueprint == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Compile Blueprint Failed - Path doesn't lead to a valid Bleprint. '%s'"), *BlueprintPath);
		return;
	}

	// Compile Blueprint
	FCompilerResultsLog Result;
	FKismetEditorUtilities::CompileBlueprint(Blueprint, EBlueprintCompileOptions::SkipSave, &Result);

	// Format The Results
	FString Logs = Result.Messages.Num() > Result.NumWarnings + Result.NumErrors ? "\n--- Logs ---" : "";
	FString Warnings = Result.NumWarnings > 0 ? "\n--- Warnings ---" : "";
	FString Errors = Result.NumErrors > 0 ? "\n--- Errors ---" : "";

	for (TSharedRef<FTokenizedMessage> Message : Result.Messages)
	{
		switch (Message.Get().GetSeverity())
		{
		default:
		case EMessageSeverity::Type::Info:
			Logs += "\n" + Message.Get().ToText().ToString();
			break;
		case EMessageSeverity::Type::Warning:
		case EMessageSeverity::Type::PerformanceWarning:
			Warnings += "\n" + Message.Get().ToText().ToString();
			break;
		case EMessageSeverity::Type::Error:
			Errors += "\n" + Message.Get().ToText().ToString();
			break;
		}
	}

	// Return The Result

	bOutSuccess = Result.NumErrors == 0;
	FString SuccededOrFailed = bOutSuccess ? "Succeded" : "Failed";
	FString Messages = Logs + Warnings + Errors;
	OutInfoMessage = FString::Printf(TEXT("Compile Blueprint %s - '%s' %s"), *SuccededOrFailed, *BlueprintPath, *Messages);

}



// Get Selected Paths

void USC_LibraryBPLibrary::GetContentBrowserList(TArray<FString>& GetFolders, TArray<FAssetData>& GetAssetPath, TArray<FString>& GetPathViewFolders)
{

	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	IContentBrowserSingleton& ContentBrowserSingleton = ContentBrowserModule.Get();
	ContentBrowserSingleton.GetSelectedFolders(GetFolders);
	ContentBrowserSingleton.GetSelectedAssets(GetAssetPath);
	ContentBrowserSingleton.GetSelectedPathViewFolders(GetPathViewFolders);

}



// Save Assets

void USC_LibraryBPLibrary::SaveAsset(FString AssetPath, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Load Blueprint Asset
	UObject* Asset = StaticLoadObject(UObject::StaticClass(), nullptr, *AssetPath);

	if (Asset == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Save Asset Failed - Asset is not valid '%s'"), *AssetPath);
		return;
	}

	// Get The Package From The Asset
	UPackage* Package = Asset->GetPackage();

	if (Package == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Save Asset Failed - Package is not valid '%s'"), *AssetPath);
		return;
	}

	// Save The Packgage
	bOutSuccess = UEditorLoadingAndSavingUtils::SavePackages({ Package }, false);
	OutInfoMessage = FString::Printf(TEXT("Save Asset %s - '%s'"), *FString(bOutSuccess ? "Successded" : "Failed"), *AssetPath);
	return;

}

void USC_LibraryBPLibrary::MarkAssetModified(FString AssetPath, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Load The Asset
	UObject* Asset = StaticLoadObject(UObject::StaticClass(), nullptr, *AssetPath);

	if (Asset == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Mark Asset Failed - Asset is not valid '%s'"), *AssetPath);
		return;
	}

	// Get The Package From The Asset
	UPackage* Package = Asset->GetPackage();

	if (Package == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Mark Asset Failed - Package is not valid '%s'"), *AssetPath);
		return;
	}

	// Mark The Packgage As Modified
	bOutSuccess = Package->MarkPackageDirty();
	OutInfoMessage = FString::Printf(TEXT("Mark Asset %s - '%s'"), *FString(bOutSuccess ? "Successded" : "Failed"), *AssetPath);
	return;

}

TArray<UObject*> USC_LibraryBPLibrary::GetModifiedAssets(bool& bOutSuccess, FString& OutInfoMessage)
{
	// Retrive a List Of All The Modified Packages
	TArray<UPackage*> ModifiedPackages = TArray<UPackage*>();
	FEditorFileUtils::GetDirtyContentPackages(ModifiedPackages);

	// Asume The Process Is a Success Until We Detect An Error
	bOutSuccess = false;
	OutInfoMessage = FString::Printf(TEXT("Get Modified Assets Successded"));

	// Convert The Packages List To An Assets List
	TArray<UObject*> ModifiedAssets = TArray<UObject*>();

	for (UPackage* Package : ModifiedPackages)
	{
		// Get The Asset From Package
		UObject* Asset = Package->FindAssetInPackage();

		if (Asset != nullptr)
		{
			ModifiedAssets.Add(Asset);
		}
		else
		{
			if (bOutSuccess)
			{
				bOutSuccess = false;
				OutInfoMessage = FString::Printf(TEXT("Get Modified Assets Failed - Packages with invalid assets: "));
			}
			OutInfoMessage += FString::Printf(TEXT("'%s' , "), *Package->GetName());
		}
	}

	// Return The Assets
	return ModifiedAssets;

}

void USC_LibraryBPLibrary::SaveAllModifiedAsset(bool bPrompt, bool& bOutSuccess, FString& OutInfoMessage)
{
	if (bPrompt)
	{
		bOutSuccess = UEditorLoadingAndSavingUtils::SaveDirtyPackagesWithDialog(true, true);
	}
	else
	{
		bOutSuccess = UEditorLoadingAndSavingUtils::SaveDirtyPackages(true, true);
	}

	OutInfoMessage = FString::Printf(TEXT("Save All Modified Assets %s"), *FString(bOutSuccess ? "Success" : "Failed"));

}
#endif

