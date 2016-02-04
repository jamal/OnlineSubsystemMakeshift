// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "OnlineSubsystemMakeshiftPrivatePCH.h"
#include "OnlineAsyncTaskManagerMakeshift.h"
#include "OnlineSubsystemMakeshift.h"

void FOnlineAsyncTaskManagerMakeshift::OnlineTick()
{
	check(MakeshiftSubsystem);
	check(FPlatformTLS::GetCurrentThreadId() == OnlineThreadId || !FPlatformProcess::SupportsMultithreading());
}

