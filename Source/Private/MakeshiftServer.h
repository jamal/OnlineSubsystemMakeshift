#pragma once

class FMakeshiftServer
{
private:
	class FOnlineSubsystemMakeshift* MakeshiftSubsystem;
	class FSocket* Socket;

public:

	FMakeshiftServer(class FOnlineSubsystemMakeshift* InMakeshiftSubsystem);

	void Init();
	void Shutdown();

};

