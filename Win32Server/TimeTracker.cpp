#include "stdafx.h"


TimeTracker::TimeTracker()
{
}
TimeTracker::TimeTracker(HWND hWnd)
{
	this->hWnd = hWnd;
}
TimeTracker::~TimeTracker()
{
}

BOOL TimeTracker::InitTrack()
{
	this->pServer.reset(new Server());
	boost::thread tConnect(boost::bind(&Server::Connect, pServer.get()));
	tConnect.join();
	if (!(pServer->pConnected))
	{
		MessageBox(
			NULL,
			TEXT("Named pipe connect failed"),
			NULL,
			MB_OK
			);
		return FALSE;
	}

	this->pHookRunner.reset(new HookRunner());
	IHook *pIHook = pHookRunner->RunHook();
	if (pIHook == NULL)
	{
		MessageBox(
			NULL,
			TEXT("Run hook failed"),
			NULL,
			MB_OK
			);
		pServer->Disconnect();
		return FALSE;
	}
	this->pTask.reset(new Task(pIHook));
}
void TimeTracker::RunTrack()
{
	boost::thread tMainProc(&Server::MainProc, pServer.get(), this->pTask);
	tMainProc.join();

	this->pServer->Disconnect();
	this->pHookRunner->StopHook();

	WPARAM wParam = NULL, lParam = NULL;

	LRESULT rez = SendMessage(
		this->hWnd,
		WM_DESTROY,
		wParam,
		lParam
		);
}