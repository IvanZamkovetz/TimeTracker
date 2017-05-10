#include "stdafx.h"
#include "Server.h"
#include "Task.h"
#include "Recognizer.h"

Server::Server()
{
	this->pConnected = FALSE;
	this->lpszPipeName = TEXT("\\\\.\\pipe\\mainpipe");
	this->pipeBufSize = 256;
	this->hPipe = INVALID_HANDLE_VALUE;
}
Server::Server(LPTSTR lpszPipeName, int pipeBufSize)
{
	this->pConnected = FALSE;
	this->lpszPipeName = lpszPipeName;
	this->pipeBufSize = pipeBufSize;
	this->hPipe = INVALID_HANDLE_VALUE;
}
Server::~Server()
{

}

int Server::Connect()
{
	std::cout << "Pipe Server: this is Connect thread" << std::endl;
	std::cout << "Pipe Server: Connect thread awaiting client connection on " << *lpszPipeName << std::endl;
	hPipe = CreateNamedPipe(
		this->lpszPipeName,             // pipe name 
		PIPE_ACCESS_DUPLEX,       // read/write access 
		PIPE_TYPE_MESSAGE |       // message type pipe 
		PIPE_READMODE_MESSAGE |   // message-read mode 
		PIPE_WAIT,                // blocking mode 
		PIPE_UNLIMITED_INSTANCES, // max. instances  
		this->pipeBufSize,                  // output buffer size 
		this->pipeBufSize,                  // input buffer size 
		0,                        // client time-out 
		NULL);                    // default security attribute 
	if (this->hPipe == INVALID_HANDLE_VALUE)
	{
		std::cout << "CreateNamedPipe failed, GLE=" << GetLastError() << std::endl;
		return -1;
	}

	this->pConnected = ConnectNamedPipe(hPipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);
	if (!(this->pConnected))
	{
		std::cout << "Connect client failed, GLE=%d.\n" << GetLastError() << std::endl;
		CloseHandle(this->hPipe);
		return -1;
	}
	std::cout << "Connect client succeed" << std::endl;

	return 0;
}
void Server::Start()
{
	std::cout << "Pipe Server: this is Start thread" << std::endl;

	this->pReadBufer.reset(new char[this->pipeBufSize]);
	this->pWriteBufer.reset(new char[this->pipeBufSize]);

	boost::shared_ptr<Task> pTask(new Task());
	boost::scoped_ptr<Recognizer> pRecognizer(new Recognizer(pTask, this->pReadBufer, this->pWriteBufer, this->pipeBufSize));

	while ((this->Read()) == 0)
	{
		pRecognizer->RecognizeCommand();
		pRecognizer->ExecuteCommand();
	}
}
void Server::Stop()
{

}

int Server::Read()
{
	BOOL readSuccess = FALSE;
	DWORD cbBytesRead = 0;
	DWORD lastError;

	readSuccess = ReadFile(
		this->hPipe,        // handle to pipe 
		this->pReadBufer.get(),    // buffer to receive data 
		this->pipeBufSize*sizeof(char), // size of buffer 
		&cbBytesRead, // number of bytes read 
		NULL);        // not overlapped I/O

	if (!readSuccess)
	{
		if (GetLastError() == ERROR_BROKEN_PIPE)
		{
			return -1;
		}
	}
	return 0;

}
int Server::Write()
{
	BOOL writeSuccess = FALSE;
	DWORD cbBytesWrite = 0;
	DWORD lastError;

	writeSuccess = WriteFile(
		this->hPipe,        // handle to pipe 
		this->pReadBufer.get(),    // buffer to receive data 
		this->pipeBufSize*sizeof(char), // size of buffer 
		&cbBytesWrite, // number of bytes read 
		NULL);        // not overlapped I/O

	if (!writeSuccess)
	{

		return -1;

	}
	return 0;
}