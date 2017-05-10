#include "stdafx.h"


HookRunner::HookRunner()
{
	this->pIHook = NULL;
	this->hDLL = LoadLibrary(TEXT("HookDll.dll"));
	this->createHookInstance = (lpCreateFn)GetProcAddress(hDLL, "CreateHookInstance");
	this->deleteHookInstance = (lpDeletefn)GetProcAddress(hDLL, "DeleteHookInstance");
	if ((hDLL == NULL) || (createHookInstance == NULL) || (deleteHookInstance == NULL))
	{
		this->dllLoaded = FALSE;
	}
	this->dllLoaded = TRUE;
}

IHook* HookRunner::RunHook()
{
	
	if (this->dllLoaded = FALSE)
	{
		if (this->hDLL != NULL)
		{
			FreeLibrary(this->hDLL);
		}
		MessageBox(
			NULL,
			TEXT("LoadDll or Procedures failed"),
			NULL,
			MB_OK
			);
		return NULL;
	}
	this->pIHook = createHookInstance();
	if (this->pIHook == NULL)
	{
		MessageBox(
			NULL,
			TEXT("CreateHookInstance failed"),
			NULL,
			MB_OK
			);
		FreeLibrary(this->hDLL);
		return NULL;
	}
	if ((this->pIHook->SetHooks()) == FALSE)
	{
		MessageBox(
			NULL,
			TEXT("SetHooks failed"),
			NULL,
			MB_OK
			);
		this->pIHook = NULL;
		this->deleteHookInstance();
		FreeLibrary(this->hDLL);
		return NULL;
	}
	return this->pIHook;
}
void HookRunner::StopHook()
{
	if (this->pIHook != NULL)
	{
		this->pIHook->RemoveHooks();
		this->pIHook = NULL;
		this->deleteHookInstance();
		FreeLibrary(this->hDLL);

	}
}

