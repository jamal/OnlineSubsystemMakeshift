#include "OnlineSubsystemMakeshiftPrivatePCH.h"
#include "MakeshiftServer.h"
#include "OnlineSubsystemMakeshift.h"
#include "Networking.h"

FMakeshiftServer::FMakeshiftServer(FOnlineSubsystemMakeshift* InMakeshiftSubsystem)
{
	MakeshiftSubsystem = InMakeshiftSubsystem;
}

void FMakeshiftServer::Init()
{
	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);

	if (SocketSubsystem != nullptr)
	{
		FString SocketDescription("MakeshiftServerSocket");

		FIPv4Endpoint Endpoint(FIPv4Address(192, 168, 1, 205), 9915);
		UE_LOG_ONLINE(Warning, TEXT("Connecting to %s"), *Endpoint.ToString());
		//Socket = FTcpSocketBuilder(*SocketName).BoundToEndpoint(Endpoint).Build();

		bool Error = true;
		Socket = SocketSubsystem->CreateSocket(NAME_Stream, *SocketDescription, true);
		if (Socket != nullptr)
		{
			Error = !Socket->Connect(*SocketSubsystem->CreateInternetAddr(Endpoint.GetAddress().GetValue(), Endpoint.GetPort()));
		}

		if (Error)
		{
			UE_LOG_ONLINE(Warning, TEXT("Failed to connect to %s"), *Endpoint.ToString());
		}
		else
		{
			int32 sent;
			char data[] = "hello there";
			Socket->Send(reinterpret_cast<const uint8 *>(data), 5, sent);
			UE_LOG_ONLINE(Warning, TEXT("Sent %d bytes"), sent);
		}
	}
}

void FMakeshiftServer::Shutdown()
{
	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	if (SocketSubsystem != nullptr && Socket != nullptr)
	{
		SocketSubsystem->DestroySocket(Socket);
	}
}