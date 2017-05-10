
class Task
{

private:
	
	std::string _key;
	IHook *_pIHook;
public:
	
	Task();
	Task(IHook *pIHook);
	virtual ~Task();

	std::string GetHash(std::string& userId, std::string& taskId, std::string& currentTime);
	std::string Encrypt(std::string& userId, std::string& taskId, std::string& currentTime);
};