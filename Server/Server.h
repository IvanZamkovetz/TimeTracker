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
	void Start();
	void Stop();

	int Read();
	int Write();
};