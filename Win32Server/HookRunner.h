typedef IHook *(*lpCreateFn)();
typedef void(*lpDeletefn)();

class HookRunner
{

public:
	HINSTANCE hDLL;
	lpCreateFn createHookInstance;
	lpDeletefn deleteHookInstance;
	IHook* pIHook;

	BOOL dllLoaded;

	HookRunner();

	IHook* RunHook();
	void StopHook();
};