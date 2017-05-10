#include "stdafx.h"

Task::Task()
{
	this->_key = "inextremo88";
}
Task::Task(IHook *pIHook)
{
	this->_pIHook = pIHook;
	this->_key = "inextremo88";

}
Task::~Task()
{
}
std::string Task::GetHash(std::string& userId, std::string& taskId, std::string& currentTime)
{
	std::string hash;
	if (!(this->_pIHook->GetEvent()))
	{
		hash.clear();
		return hash;
	}
	this->_pIHook->ResetEvent();
	hash = this->Encrypt(userId, taskId, currentTime);
	return hash;
}

std::string Task::Encrypt(std::string& userId, std::string& taskId, std::string& currentTime)
{
	int maxLength = userId.length() > taskId.length() ? userId.length() : taskId.length();
	maxLength = maxLength > currentTime.length() ? maxLength : currentTime.length();
	maxLength = maxLength > this->_key.length() ? maxLength : this->_key.length();

	char *encryptedChars = new char[maxLength + 1];
	const char *keyChars = this->_key.c_str();
	const char *userIdChars = userId.c_str();
	const char *taskIdChars = taskId.c_str();
	const char *currentTimeChars = currentTime.c_str();

	for (int i = 0; i < maxLength; i++)
	{
		encryptedChars[i] = 1;
		if (i < userId.length())
		{
			encryptedChars[i] *= userIdChars[i];
		}
		if (i < taskId.length())
		{
			encryptedChars[i] *= taskIdChars[i];
		}
		if (i < currentTime.length())
		{
			encryptedChars[i] *= currentTimeChars[i];
		}
		if (i < this->_key.length())
		{
			encryptedChars[i] *= keyChars[i];
		}
		if (i > 0)
		{
			encryptedChars[i] += encryptedChars[i - 1];
		}
	}
		encryptedChars[maxLength] = 0;
		return std::string(encryptedChars);
	
}
