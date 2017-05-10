class Server
{
private:

public:
	boost::shared_ptr<char[]> pReadBufer;
	boost::shared_ptr<char[]> pWriteBufer;
	
	BOOL  pConnected;
	LPTSTR lpszPipeName;
	int pipeBufSize;
	HANDLE hPipe;

	Server();
	Server(LPTSTR lpszPipeName, int pipeBufSize);
	virtual ~Server();

	int Connect();
	void MainProc(boost::shared_ptr<Task> &pTask);
	void Disconnect();

	int Read();
	int Write();

};