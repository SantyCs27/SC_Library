// Copyright Santiago Cañas. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
// Another App Instance
#include "HAL/FileManager.h"
#include "Runtime/ApplicationCore/Public/Windows/WindowsPlatformApplicationMisc.h"

#include "SC_LibraryBPLibrary.generated.h"


/***** Display Switching Functions *****/

USTRUCT(BlueprintType)
struct FDisplayInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Something")
	FString Name;

	UPROPERTY(BlueprintReadOnly, Category = "Something")
	FString ID;

	UPROPERTY(BlueprintReadOnly, Category = "Something")
	int32 NativeWidth = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Something")
	int32 NativeHeight = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Something")
	FIntPoint MaxResolution = FIntPoint(ForceInitToZero);

	UPROPERTY(BlueprintReadOnly, Category = "Something")
	bool bIsPrimary = false;

	UPROPERTY(BlueprintReadOnly, Category = "Something")
	int32 DPI = 0;

	// Default constructor
	FDisplayInfo()
	{
		Name = FString("");
		ID = FString("");
		NativeWidth = 0;
		NativeHeight = 0;
		MaxResolution = FIntPoint(ForceInitToZero);
		bIsPrimary = false;
		DPI = 0;
	}

	// Custom constructor
	FDisplayInfo(const FString& InName, const FString& InID, int32 InNativeWidth, int32 InNativeHeight, const FIntPoint& InMaxResolution, bool InIsPrimary, int32 InDPI) : Name(InName), ID(InID), NativeWidth(InNativeWidth), NativeHeight(InNativeHeight), MaxResolution(InMaxResolution), bIsPrimary(InIsPrimary), DPI(InDPI)
	{
	}
};


/***** RAM *****/

USTRUCT(BlueprintType)
struct FMemInfoSC
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly, Category = "Memory Info")
	int32 PhysicalMemoryUsedInGb;

	UPROPERTY(BlueprintReadOnly, Category = "Memory Info")
	int32 PhysicalMemoryAvailableInGb;

	UPROPERTY(BlueprintReadOnly, Category = "Memory Info")
	int32 TotalMemoryInGb;

};


/***** CPU *****/

USTRUCT(BlueprintType)
struct FCPUInfoSC
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "CPU Info")
	float CPUUsage;
};

UCLASS()
class USC_LibraryBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()


	/***** Another App Instance *****/

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "AnotherAppInstance"), Category = "A_SC_Library|General")
	static void AnotherAppInstance(bool Enabled = true);



	/***** Display Switching Functions *****/

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetDisplayCount"), Category = "A_SC_Library|Display")
	static int GetDisplayCount();

	UFUNCTION(BlueprintCallable, Category = "A_SC_Library|Display")
	static TArray<FDisplayInfo> GetAllDisplays();

	UFUNCTION(BlueprintPure, Category = "A_SC_Library|Display")
	static int32 GetPrimaryMonitor();

	UFUNCTION(BlueprintCallable, Category = "A_SC_Library|Display")
	static bool SetActiveDisplay(int32 DisplayIndex);



	/***** Minimize, Maximize And Restore Window *****/

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MinimizeWindow"), Category = "A_SC_Library|Window")
	static void MinimizeWindow();

	UFUNCTION(BlueprintCallable, Category = "A_SC_Library|Window")
	static void MaximizeWindow();

	UFUNCTION(BlueprintCallable, Category = "A_SC_Library|Window")
	static void RestoreWindow();



	/***** GPU *****/

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetPrimaryGraphicsCardName"), Category = "A_SC_Library|GPU")
	static FString GetPrimaryGraphicsCardName();

	UFUNCTION(BlueprintCallable, Category = "A_SC_Library|GPU")
	static int UsedVRAM();

	UFUNCTION(BlueprintCallable, Category = "A_SC_Library|GPU")
	static int AvailableVRAM();

	UFUNCTION(BlueprintCallable, Category = "A_SC_Library|GPU")
	static int32 TotalVRAM();



	/***** RAM *****/

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetRamSize"), Category = "A_SC_Library|RAM")
	static int32  GetRamSize();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "A_SC_Library|RAM")
	static FMemInfoSC GetMemoryInformation();



	/***** Sound *****/

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetCurrentAudioOutputDevice"), Category = "A_SC_Library|Audio")
	static FString GetCurrentAudioOutputDevice();

	UFUNCTION(BlueprintCallable, Category = "A_SC_Library|Audio")
	static void GetAllAudioOutputDevices(TArray<FString>& OutAudioDeviceNames);



	/***** CPU *****/

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "GetCPUUsage"), Category = "A_SC_Library|CPU")
	static float GetCPUUsage();



	/***** Project Settings *****/

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetProjectName"), Category = "A_SC_Library|ProjectSettings|Get")
	static FString GetProjectName();

	UFUNCTION(BlueprintPure, Category = "A_SC_Library|ProjectSettings|Get")
	static FString GetProjectVersion();

	UFUNCTION(BlueprintPure, Category = "A_SC_Library|ProjectSettings|Get")
	static FText GetProjectDisplayedTitle();

	UFUNCTION(BlueprintPure, Category = "A_SC_Library|ProjectSettings|Get")
	static bool GetAllowClose();

	UFUNCTION(BlueprintPure, Category = "A_SC_Library|ProjectSettings|Get")
	static bool GetAllowMaximize();

	UFUNCTION(BlueprintPure, Category = "A_SC_Library|ProjectSettings|Get")
	static bool GetAllowMinimize();

	UFUNCTION(BlueprintPure, Category = "A_SC_Library|ProjectSettings|Get")
	static bool GetAllowWindowResize();

	UFUNCTION(BlueprintPure, Category = "A_SC_Library|ProjectSettings|Get")
	static bool GetBorderlessWindow();

	UFUNCTION(BlueprintPure, Category = "A_SC_Library|ProjectSettings|Get")
	static bool GetWindowPreserveAspectRatio();

	UFUNCTION(BlueprintCallable, Category = "A_SC_Library|ProjectSettings|Set")
	static void SetProjectName(const FString& ProjectName);

	UFUNCTION(BlueprintCallable, Category = "A_SC_Library|ProjectSettings|Set")
	static void SetProjectVersion(const FString& ProjectVersion);

	UFUNCTION(BlueprintCallable, Category = "A_SC_Library|ProjectSettings|Set")
	static void SetProjectDisplayedTitle(const FText& ProjectDisplayedTitle);

	UFUNCTION(BlueprintCallable, Category = "A_SC_Library|ProjectSettings|Set")
	static void SetAllowClose(bool AllowClose);

	UFUNCTION(BlueprintCallable, Category = "A_SC_Library|ProjectSettings|Set")
	static void SetAllowMaximize(bool AllowMaximize);

	UFUNCTION(BlueprintCallable, Category = "A_SC_Library|ProjectSettings|Set")
	static void SetAllowMinimize(bool AllowMinimize);

	UFUNCTION(BlueprintCallable, Category = "A_SC_Library|ProjectSettings|Set")
	static void SetAllowWindowResize(bool AllowWindowResize);

	UFUNCTION(BlueprintCallable, Category = "A_SC_Library|ProjectSettings|Set")
	static void SetBorderlessWindow(bool BorderlessWindow);

	UFUNCTION(BlueprintCallable, Category = "A_SC_Library|ProjectSettings|Set")
	static void SetWindowPreserveAspectRatio(bool WindowPreserveAspectRatio);



	/***** Windows Foreground *****/

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetWindowAlwaysOnTop"), Category = "A_SC_Library|Window")
	static bool SetWindowAlwaysOnTop(bool bOnTop);

	UFUNCTION(BlueprintPure, Category = "A_SC_Library|Window")
	static bool GetWindowAlwaysOnTop();



	/***** Windows *****/

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetMainWindowPos"), Category = "A_SC_Library|Window")
	static FVector2D GetMainWindowPos();

	UFUNCTION(BlueprintCallable, Category = "A_SC_Library|Window")
	static void SetMainWindowPosition(FVector2D InNewPosition);



	/***** Blueprint Compiler *****/

#if WITH_EDITOR

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CompileBlueprint"), Category = "A_SC_Library|General|Compiler")
	static void CompileBlueprint(FString BlueprintPath, bool& bOutSuccess, FString& OutInfoMessage);



	/***** Get Selected Paths *****/

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetContentBrowserList"), Category = "A_SC_Library|General|Path")
	static void GetContentBrowserList(TArray<FString>& GetFolders, TArray<FAssetData>& GetAssetPath, TArray<FString>& GetPathViewFolders);



	/***** Save Assets *****/

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SaveAsset"), Category = "A_SC_Library|General|SaveAssets")
	static void SaveAsset(FString AssetPath, bool& bOutSuccess, FString& OutInfoMessage);

	UFUNCTION(BlueprintCallable, Category = "A_SC_Library|General|SaveAssets")
	static void MarkAssetModified(FString AssetPath, bool& bOutSuccess, FString& OutInfoMessage);

	UFUNCTION(BlueprintCallable, Category = "A_SC_Library|General|SaveAssets")
	static TArray<UObject*> GetModifiedAssets(bool& bOutSuccess, FString& OutInfoMessage);

	UFUNCTION(BlueprintCallable, Category = "A_SC_Library|General|SaveAssets")
	static void SaveAllModifiedAsset(bool bPrompt, bool& bOutSuccess, FString& OutInfoMessage);
#endif


};
