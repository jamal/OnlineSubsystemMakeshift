// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "OnlineSubsystem.h"
#include "OnlineSubsystemImpl.h"
#include "OnlineSubsystemMakeshiftPackage.h"

/** Forward declarations of all interface classes */
typedef TSharedPtr<class FOnlineSessionMakeshift, ESPMode::ThreadSafe> FOnlineSessionMakeshiftPtr;
typedef TSharedPtr<class FOnlineProfileMakeshift, ESPMode::ThreadSafe> FOnlineProfileMakeshiftPtr;
typedef TSharedPtr<class FOnlineFriendsMakeshift, ESPMode::ThreadSafe> FOnlineFriendsMakeshiftPtr;
typedef TSharedPtr<class FOnlineUserCloudMakeshift, ESPMode::ThreadSafe> FOnlineUserCloudMakeshiftPtr;
typedef TSharedPtr<class FOnlineLeaderboardsMakeshift, ESPMode::ThreadSafe> FOnlineLeaderboardsMakeshiftPtr;
typedef TSharedPtr<class FOnlineVoiceImpl, ESPMode::ThreadSafe> FOnlineVoiceImplPtr;
typedef TSharedPtr<class FOnlineExternalUIMakeshift, ESPMode::ThreadSafe> FOnlineExternalUIMakeshiftPtr;
typedef TSharedPtr<class FOnlineIdentityMakeshift, ESPMode::ThreadSafe> FOnlineIdentityMakeshiftPtr;
typedef TSharedPtr<class FOnlineAchievementsMakeshift, ESPMode::ThreadSafe> FOnlineAchievementsMakeshiftPtr;

/**
 *	OnlineSubsystemMakeshift - Implementation of the online subsystem for Makeshift services
 */
class ONLINESUBSYSTEMMAKESHIFT_API FOnlineSubsystemMakeshift : 
	public FOnlineSubsystemImpl
{

public:

	virtual ~FOnlineSubsystemMakeshift()
	{
	}

	// IOnlineSubsystem

	virtual IOnlineSessionPtr GetSessionInterface() const override;
	virtual IOnlineFriendsPtr GetFriendsInterface() const override;
	virtual IOnlinePartyPtr GetPartyInterface() const override;
	virtual IOnlineGroupsPtr GetGroupsInterface() const override;
	virtual IOnlineSharedCloudPtr GetSharedCloudInterface() const override;
	virtual IOnlineUserCloudPtr GetUserCloudInterface() const override;
	virtual IOnlineEntitlementsPtr GetEntitlementsInterface() const override;
	virtual IOnlineLeaderboardsPtr GetLeaderboardsInterface() const override;
	virtual IOnlineVoicePtr GetVoiceInterface() const override;
	virtual IOnlineExternalUIPtr GetExternalUIInterface() const override;	
	virtual IOnlineTimePtr GetTimeInterface() const override;
	virtual IOnlineIdentityPtr GetIdentityInterface() const override;
	virtual IOnlineTitleFilePtr GetTitleFileInterface() const override;
	virtual IOnlineStorePtr GetStoreInterface() const override;
	virtual IOnlineEventsPtr GetEventsInterface() const override;
	virtual IOnlineAchievementsPtr GetAchievementsInterface() const override;
	virtual IOnlineSharingPtr GetSharingInterface() const override;
	virtual IOnlineUserPtr GetUserInterface() const override;
	virtual IOnlineMessagePtr GetMessageInterface() const override;
	virtual IOnlinePresencePtr GetPresenceInterface() const override;
	virtual IOnlineChatPtr GetChatInterface() const override;
    virtual IOnlineTurnBasedPtr GetTurnBasedInterface() const override;
	
	virtual bool Init() override;
	virtual bool Shutdown() override;
	virtual FString GetAppId() const override;
	virtual bool Exec(class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;

	// FTickerObjectBase
	
	virtual bool Tick(float DeltaTime) override;

	// FOnlineSubsystemMakeshift

	/**
	 * Is the Makeshift API available for use
	 * @return true if Makeshift functionality is available, false otherwise
	 */
	bool IsEnabled();

PACKAGE_SCOPE:

	/** Only the factory makes instances */
	FOnlineSubsystemMakeshift(FName InInstanceName) :
		FOnlineSubsystemImpl(InInstanceName),
		SessionInterface(NULL),
		VoiceInterface(NULL),
		LeaderboardsInterface(NULL),
		IdentityInterface(NULL),
		AchievementsInterface(NULL),
		OnlineAsyncTaskThreadRunnable(NULL),
		OnlineAsyncTaskThread(NULL)
	{}

	FOnlineSubsystemMakeshift() :
		SessionInterface(NULL),
		VoiceInterface(NULL),
		LeaderboardsInterface(NULL),
		IdentityInterface(NULL),
		AchievementsInterface(NULL),
		OnlineAsyncTaskThreadRunnable(NULL),
		OnlineAsyncTaskThread(NULL)
	{}

private:

	/** Interface to the session services */
	FOnlineSessionMakeshiftPtr SessionInterface;

	/** Interface for voice communication */
	FOnlineVoiceImplPtr VoiceInterface;

	/** Interface to the leaderboard services */
	FOnlineLeaderboardsMakeshiftPtr LeaderboardsInterface;

	/** Interface to the identity registration/auth services */
	FOnlineIdentityMakeshiftPtr IdentityInterface;

	/** Interface for achievements */
	FOnlineAchievementsMakeshiftPtr AchievementsInterface;

	/** Online async task runnable */
	class FOnlineAsyncTaskManagerMakeshift* OnlineAsyncTaskThreadRunnable;

	/** Online async task thread */
	class FRunnableThread* OnlineAsyncTaskThread;
};

typedef TSharedPtr<FOnlineSubsystemMakeshift, ESPMode::ThreadSafe> FOnlineSubsystemMakeshiftPtr;

