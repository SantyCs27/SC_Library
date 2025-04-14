// Copyright Santiago Cañas. All Rights Reserved.

using UnrealBuildTool;

public class SC_Library : ModuleRules
{
	public SC_Library(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        bUseUnity = false;

        PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add other public dependencies that you statically link with here ...
			}
			);
        if ((Target.IsInPlatformGroup(UnrealPlatformGroup.Windows)))
        {
            // Uses DXGI to query GPU hardware
            // This is what will allow us to get GPU usage statistics at runtime
            PublicSystemLibraries.Add("DXGI.lib");
        }


        PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "Core",
                "CoreUObject",
                "RHI",
                "MoviePlayer",
                "UMG",
                "Engine",
                "Slate",
                "SlateCore",
                "ApplicationCore",
                "EngineSettings",
                "InputCore"
				// ... add private dependencies that you statically link with here ...	
			}
			);
        if (Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd" });
        }


        DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
