// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "OnlineSubsystemMakeshiftPrivatePCH.h"
#include "OnlineSubsystemMakeshift.h"
#include "ModuleManager.h"

IMPLEMENT_MODULE(FOnlineSubsystemMakeshiftModule, OnlineSubsystemMakeshift);

/**
 * Class responsible for creating instance(s) of the subsystem
 */
class FOnlineFactoryMakeshift : public IOnlineFactory
{
public:

	FOnlineFactoryMakeshift() {}
	virtual ~FOnlineFactoryMakeshift() {}

	virtual IOnlineSubsystemPtr CreateSubsystem(FName InstanceName)
	{
		FOnlineSubsystemMakeshiftPtr OnlineSub = MakeShareable(new FOnlineSubsystemMakeshift(InstanceName));
		if (OnlineSub->IsEnabled())
		{
			if(!OnlineSub->Init())
			{
				UE_LOG_ONLINE(Warning, TEXT("Makeshift API failed to initialize!"));
				OnlineSub->Shutdown();
				OnlineSub = NULL;
			}
		}
		else
		{
			UE_LOG_ONLINE(Warning, TEXT("Makeshift API disabled!"));
			OnlineSub->Shutdown();
			OnlineSub = NULL;
		}

		return OnlineSub;
	}
};

void FOnlineSubsystemMakeshiftModule::StartupModule()
{
	MakeshiftFactory = new FOnlineFactoryMakeshift();

	// Create and register our singleton factory with the main online subsystem for easy access
	FOnlineSubsystemModule& OSS = FModuleManager::GetModuleChecked<FOnlineSubsystemModule>("OnlineSubsystem");
	OSS.RegisterPlatformService(MAKESHIFT_SUBSYSTEM, MakeshiftFactory);
}

void FOnlineSubsystemMakeshiftModule::ShutdownModule()
{
	FOnlineSubsystemModule& OSS = FModuleManager::GetModuleChecked<FOnlineSubsystemModule>("OnlineSubsystem");
	OSS.UnregisterPlatformService(MAKESHIFT_SUBSYSTEM);
	
	delete MakeshiftFactory;
	MakeshiftFactory = NULL;
}
