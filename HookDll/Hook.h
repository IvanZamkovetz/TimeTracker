
class Hook : public IHook
{

public:
	static HMODULE Hook::hThisDll;
	static HHOOK Hook::keyBoard;
	static HHOOK Hook::mouse;
	static BOOL Hook::event;

	BOOL SetHooks();
	void RemoveHooks();

	BOOL GetEvent();
	void ResetEvent();
	static LRESULT CALLBACK SetEvent(int nCode, WPARAM wParam, LPARAM lParam);
};