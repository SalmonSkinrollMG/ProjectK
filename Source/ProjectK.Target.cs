// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectKTarget : TargetRules
{
	public ProjectKTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "ProjectK" } );
	}
}
