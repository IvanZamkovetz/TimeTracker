
class TimeTracker
{
public:
	HWND hWnd;
	boost::shared_ptr<Server> pServer;
	boost::shared_ptr<HookRunner> pHookRunner;
	boost::shared_ptr<Task> pTask;

	TimeTracker();
	TimeTracker(HWND hWnd);
	virtual ~TimeTracker();
	BOOL InitTrack();
	void RunTrack();

};