class Recognizer
{
private:
	boost::scoped_ptr<std::vector<std::string>> pParsedCommand;
	

public:
	boost::shared_ptr<Task> pTask;
	boost::shared_ptr<char[]> pReadBufer;
	boost::shared_ptr<char[]> pWriteBufer;

	int pipeBufSize;

	Recognizer();
	Recognizer(boost::shared_ptr<Task> pTask, boost::shared_ptr<char[]> pReadBufer, boost::shared_ptr<char[]> pWriteBufer, int pipeBufSize);
	virtual ~Recognizer();

	void RecognizeCommand();
	void ExecuteCommand();

	void Split(const std::string &s, char delim);
	
};