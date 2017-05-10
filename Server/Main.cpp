// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Server.h"
#include "Task.h"


int _tmain(int argc, _TCHAR* argv[])
{
	boost::scoped_ptr<Server> pServer(new Server());
	boost::thread tConnect(boost::bind(&Server::Connect, pServer.get()));
	tConnect.join();
	if (!(pServer->pConnected))
	{
		return -1;
	}
	boost::thread tStart(boost::bind(&Server::Start, pServer.get()));
	tStart.join();

	return 0;
}

