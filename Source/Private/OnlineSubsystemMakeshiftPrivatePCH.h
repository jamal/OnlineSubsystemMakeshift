// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "OnlineSubsystemMakeshiftModule.h"
#include "OnlineSubsystemModule.h"
#include "OnlineSubsystem.h"
#include "ModuleManager.h"

#define INVALID_INDEX -1

/** FName declaration of Makeshift subsystem */
#define MAKESHIFT_SUBSYSTEM FName(TEXT("Makeshift"))
/** URL Prefix when using Makeshift socket connection */
#define MAKESHIFT_URL_PREFIX TEXT("Makeshift.")

/** pre-pended to all NULL logging */
#undef ONLINE_LOG_PREFIX
#define ONLINE_LOG_PREFIX TEXT("MAKESHIFT: ")
