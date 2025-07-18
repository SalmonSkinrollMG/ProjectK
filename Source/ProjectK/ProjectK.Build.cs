// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

using UnrealBuildTool;

public class ProjectK : ModuleRules
{
	public ProjectK(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" , "UMG" , "EnhancedInput" , "GameplayAbilities" });

		PrivateDependencyModuleNames.AddRange(new string[] { "GameplayTags" , "GameplayTasks" , "NavigationSystem" , "Niagara"});
		
		//PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
