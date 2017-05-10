#include "stdafx.h"

HMODULE Hook::hThisDll = NULL;
HHOOK Hook::keyBoard = NULL;
HHOOK Hook::mouse = NULL;
BOOL Hook::event = FALSE;

BOOL Hook::SetHooks()
{
	if (Hook::hThisDll == NULL)
	{
		return FALSE;
	}
	Hook::keyBoard = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)Hook::SetEvent, Hook::hThisDll, NULL);// WH_MOUSE_LL
	if (Hook::keyBoard == NULL)
	{
		MessageBox(
			NULL,
			TEXT("SetHooks failed"),
			NULL,
			MB_OK
			);
		return FALSE;
	}
	return TRUE;
}
void Hook::RemoveHooks()
{
	UnhookWindowsHookEx(Hook::keyBoard);
}

BOOL Hook::GetEvent()
{
	return Hook::event;
}
void Hook::ResetEvent()
{
	Hook::event = FALSE;
}
LRESULT CALLBACK Hook::SetEvent(int nCode, WPARAM wParam, LPARAM lParam)
{
	Hook::event = TRUE;

	return	CallNextHookEx(
		Hook::keyBoard,
		nCode,
		wParam,
		lParam
		);
}