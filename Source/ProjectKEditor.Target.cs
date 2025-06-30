// Copyright (c) 2025, AlphaCentauriGames. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectKEditorTarget : TargetRules
{
	public ProjectKEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "ProjectK" } );
	}
}
