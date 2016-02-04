// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "OnlineSubsystemMakeshiftPrivatePCH.h"
#include "OnlineSubsystemMakeshift.h"
#include "OnlineAsyncTaskManagerMakeshift.h"

#include "OnlineSessionInterfaceMakeshift.h"
#include "OnlineLeaderboardInterfaceMakeshift.h"
#include "OnlineIdentityMakeshift.h"
#include "VoiceInterfaceImpl.h"
#include "OnlineAchievementsInterfaceMakeshift.h"

IOnlineSessionPtr FOnlineSubsystemMakeshift::GetSessionInterface() const
{
	return SessionInterface;
}

IOnlineFriendsPtr FOnlineSubsystemMakeshift::GetFriendsInterface() const
{
	return nullptr;
}

IOnlinePartyPtr FOnlineSubsystemMakeshift::GetPartyInterface() const
{
	return nullptr;
}

IOnlineGroupsPtr FOnlineSubsystemMakeshift::GetGroupsInterface() const
{
	return nullptr;
}

IOnlineSharedCloudPtr FOnlineSubsystemMakeshift::GetSharedCloudInterface() const
{
	return nullptr;
}

IOnlineUserCloudPtr FOnlineSubsystemMakeshift::GetUserCloudInterface() const
{
	return nullptr;
}

IOnlineEntitlementsPtr FOnlineSubsystemMakeshift::GetEntitlementsInterface() const
{
	return nullptr;
};

IOnlineLeaderboardsPtr FOnlineSubsystemMakeshift::GetLeaderboardsInterface() const
{
	return LeaderboardsInterface;
}

IOnlineVoicePtr FOnlineSubsystemMakeshift::GetVoiceInterface() const
{
	return VoiceInterface;
}

IOnlineExternalUIPtr FOnlineSubsystemMakeshift::GetExternalUIInterface() const
{
	return nullptr;
}

IOnlineTimePtr FOnlineSubsystemMakeshift::GetTimeInterface() const
{
	return nullptr;
}

IOnlineIdentityPtr FOnlineSubsystemMakeshift::GetIdentityInterface() const
{
	return IdentityInterface;
}

IOnlineTitleFilePtr FOnlineSubsystemMakeshift::GetTitleFileInterface() const
{
	return nullptr;
}

IOnlineStorePtr FOnlineSubsystemMakeshift::GetStoreInterface() const
{
	return nullptr;
}

IOnlineEventsPtr FOnlineSubsystemMakeshift::GetEventsInterface() const
{
	return nullptr;
}

IOnlineAchievementsPtr FOnlineSubsystemMakeshift::GetAchievementsInterface() const
{
	return AchievementsInterface;
}

IOnlineSharingPtr FOnlineSubsystemMakeshift::GetSharingInterface() const
{
	return nullptr;
}

IOnlineUserPtr FOnlineSubsystemMakeshift::GetUserInterface() const
{
	return nullptr;
}

IOnlineMessagePtr FOnlineSubsystemMakeshift::GetMessageInterface() const
{
	return nullptr;
}

IOnlinePresencePtr FOnlineSubsystemMakeshift::GetPresenceInterface() const
{
	return nullptr;
}

IOnlineChatPtr FOnlineSubsystemMakeshift::GetChatInterface() const
{
	return nullptr;
}

IOnlineTurnBasedPtr FOnlineSubsystemMakeshift::GetTurnBasedInterface() const
{
    return nullptr;
}

bool FOnlineSubsystemMakeshift::Tick(float DeltaTime)
{
	if (!FOnlineSubsystemImpl::Tick(DeltaTime))
	{
		return false;
	}

	if (OnlineAsyncTaskThreadRunnable)
	{
		OnlineAsyncTaskThreadRunnable->GameTick();
	}

 	if (SessionInterface.IsValid())
 	{
 		SessionInterface->Tick(DeltaTime);
 	}

	if (VoiceInterface.IsValid())
	{
		VoiceInterface->Tick(DeltaTime);
	}

	return true;
}

bool FOnlineSubsystemMakeshift::Init()
{
	const bool bMakeshiftInit = true;
	
	if (bMakeshiftInit)
	{
		// Create the online async task thread
		OnlineAsyncTaskThreadRunnable = new FOnlineAsyncTaskManagerMakeshift(this);
		check(OnlineAsyncTaskThreadRunnable);
		OnlineAsyncTaskThread = FRunnableThread::Create(OnlineAsyncTaskThreadRunnable, *FString::Printf(TEXT("OnlineAsyncTaskThreadMakeshift %s"), *InstanceName.ToString()), 128 * 1024, TPri_Normal);
		check(OnlineAsyncTaskThread);
		UE_LOG_ONLINE(Verbose, TEXT("Created thread (ID:%d)."), OnlineAsyncTaskThread->GetThreadID());

 		SessionInterface = MakeShareable(new FOnlineSessionMakeshift(this));
		LeaderboardsInterface = MakeShareable(new FOnlineLeaderboardsMakeshift(this));
		IdentityInterface = MakeShareable(new FOnlineIdentityMakeshift(this));
		AchievementsInterface = MakeShareable(new FOnlineAchievementsMakeshift(this));
		VoiceInterface = MakeShareable(new FOnlineVoiceImpl(this));
		if (!VoiceInterface->Init())
		{
			VoiceInterface = nullptr;
		}
	}
	else
	{
		Shutdown();
	}

	return bMakeshiftInit;
}

bool FOnlineSubsystemMakeshift::Shutdown()
{
	UE_LOG_ONLINE(Display, TEXT("FOnlineSubsystemMakeshift::Shutdown()"));

	FOnlineSubsystemImpl::Shutdown();

	if (OnlineAsyncTaskThread)
	{
		// Destroy the online async task thread
		delete OnlineAsyncTaskThread;
		OnlineAsyncTaskThread = nullptr;
	}

	if (OnlineAsyncTaskThreadRunnable)
	{
		delete OnlineAsyncTaskThreadRunnable;
		OnlineAsyncTaskThreadRunnable = nullptr;
	}

	if (VoiceInterface.IsValid())
	{
		VoiceInterface->Shutdown();
	}
	
 	#define DESTRUCT_INTERFACE(Interface) \
 	if (Interface.IsValid()) \
 	{ \
 		ensure(Interface.IsUnique()); \
 		Interface = nullptr; \
 	}
 
 	// Destruct the interfaces
	DESTRUCT_INTERFACE(VoiceInterface);
	DESTRUCT_INTERFACE(AchievementsInterface);
	DESTRUCT_INTERFACE(IdentityInterface);
	DESTRUCT_INTERFACE(LeaderboardsInterface);
 	DESTRUCT_INTERFACE(SessionInterface);
	
	#undef DESTRUCT_INTERFACE
	
	return true;
}

FString FOnlineSubsystemMakeshift::GetAppId() const
{
	return TEXT("");
}

bool FOnlineSubsystemMakeshift::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
	return false;
}

bool FOnlineSubsystemMakeshift::IsEnabled()
{
	return true;
}

void FOnlineSubsystemMakeshift::QueueAsyncTask(FOnlineAsyncTask* AsyncTask)
{
    check(OnlineAsyncTaskThreadRunnable);
    OnlineAsyncTaskThreadRunnable->AddToInQueue(AsyncTask);
}