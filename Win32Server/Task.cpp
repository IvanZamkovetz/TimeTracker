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
	//hash algorithm
	return std::string("encryptedChars");
	
}
