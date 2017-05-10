// HookDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "HookDll.h"

Hook * pHook;

extern "C" {
	__declspec(dllexport) IHook* CreateHookInstance()
	{
		if (pHook == NULL)
		{
			pHook = new Hook();
			return static_cast<IHook *>(pHook);
		}
		return static_cast<IHook *>(pHook);
	}
	__declspec(dllexport) void DeleteHookInstance()
	{
		if (pHook != NULL)
		{
			delete(pHook);
			return;
		}
		return;
	}
}