
class IHook
{

public:
	virtual BOOL SetHooks() = 0;
	virtual void RemoveHooks() = 0;

	virtual BOOL GetEvent() = 0;
	virtual void ResetEvent() = 0;

};