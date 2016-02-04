// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "OnlineAsyncTaskManager.h"

/**
 *	Makeshift version of the async task manager to register the various Makeshift callbacks with the engine
 */
class FOnlineAsyncTaskManagerMakeshift : public FOnlineAsyncTaskManager
{
protected:

	/** Cached reference to the main online subsystem */
	class FOnlineSubsystemMakeshift* MakeshiftSubsystem;

public:

	FOnlineAsyncTaskManagerMakeshift(class FOnlineSubsystemMakeshift* InOnlineSubsystem)
		: MakeshiftSubsystem(InOnlineSubsystem)
	{
	}

	~FOnlineAsyncTaskManagerMakeshift() 
	{
	}

	// FOnlineAsyncTaskManager
	virtual void OnlineTick() override;
};
