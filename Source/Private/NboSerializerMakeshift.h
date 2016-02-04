// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "NboSerializer.h"
#include "OnlineSubsystemMakeshiftTypes.h"

/**
 * Serializes data in network byte order form into a buffer
 */
class FNboSerializeToBufferMakeshift : public FNboSerializeToBuffer
{
public:
	/** Default constructor zeros num bytes*/
	FNboSerializeToBufferMakeshift() :
		FNboSerializeToBuffer(512)
	{
	}

	/** Constructor specifying the size to use */
	FNboSerializeToBufferMakeshift(uint32 Size) :
		FNboSerializeToBuffer(Size)
	{
	}

	/**
	 * Adds Makeshift session info to the buffer
	 */
 	friend inline FNboSerializeToBufferMakeshift& operator<<(FNboSerializeToBufferMakeshift& Ar, const FOnlineSessionInfoMakeshift& SessionInfo)
 	{
		check(SessionInfo.HostAddr.IsValid());
		// Skip SessionType (assigned at creation)
		Ar << SessionInfo.SessionId;
		Ar << *SessionInfo.HostAddr;
		return Ar;
 	}

	/**
	 * Adds Makeshift Unique Id to the buffer
	 */
	friend inline FNboSerializeToBufferMakeshift& operator<<(FNboSerializeToBufferMakeshift& Ar, const FUniqueNetIdString& UniqueId)
	{
		Ar << UniqueId.UniqueNetIdStr;
		return Ar;
	}
};

/**
 * Class used to write data into packets for sending via system link
 */
class FNboSerializeFromBufferMakeshift : public FNboSerializeFromBuffer
{
public:
	/**
	 * Initializes the buffer, size, and zeros the read offset
	 */
	FNboSerializeFromBufferMakeshift(uint8* Packet,int32 Length) :
		FNboSerializeFromBuffer(Packet,Length)
	{
	}

	/**
	 * Reads Makeshift session info from the buffer
	 */
 	friend inline FNboSerializeFromBufferMakeshift& operator>>(FNboSerializeFromBufferMakeshift& Ar, FOnlineSessionInfoMakeshift& SessionInfo)
 	{
		check(SessionInfo.HostAddr.IsValid());
		// Skip SessionType (assigned at creation)
		Ar >> SessionInfo.SessionId; 
		Ar >> *SessionInfo.HostAddr;
		return Ar;
 	}

	/**
	 * Reads Makeshift Unique Id from the buffer
	 */
	friend inline FNboSerializeFromBufferMakeshift& operator>>(FNboSerializeFromBufferMakeshift& Ar, FUniqueNetIdString& UniqueId)
	{
		Ar >> UniqueId.UniqueNetIdStr;
		return Ar;
	}
};