// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class OnlineSubsystemMakeshift : ModuleRules
{
	public OnlineSubsystemMakeshift(TargetInfo Target)
	{
		Definitions.Add("ONLINESUBSYSTEMMAKESHIFT_PACKAGE=1");

		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"Core", 
				"CoreUObject", 
				"Engine", 
				"Sockets", 
				"OnlineSubsystem", 
				"OnlineSubsystemUtils",
				"Json"
			}
			);
	}
}
