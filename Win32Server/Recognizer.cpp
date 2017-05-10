#include "stdafx.h"

Recognizer::Recognizer()
{
	this->_pParsedRequest.reset(new std::vector<std::string>());

}
Recognizer::Recognizer(boost::shared_ptr<Task> pTask, boost::shared_ptr<char[]> pReadBufer, boost::shared_ptr<char[]> pWriteBufer, int pipeBufSize)
{
	this->_pParsedRequest.reset(new std::vector<std::string>());

	this->pTask = pTask;
	this->pWriteBufer = pWriteBufer;
	this->pReadBufer = pReadBufer;
	this->pipeBufSize = pipeBufSize;
}
Recognizer::~Recognizer()
{
}

void Recognizer::RecognizeCommand()
{
	std::string request(this->pReadBufer.get());
	this->_pParsedRequest->clear();

	this->Split(request, ';');
}
void Recognizer::ExecuteCommand()
{
	std::string reply = "";

	auto it = this->_pParsedRequest->begin();
	if (it == this->_pParsedRequest->end())//
	{
		strcpy_s(this->pWriteBufer.get(), this->pipeBufSize, reply.c_str());
		return;
	}
	if (*it == "GetHash" && (this->_pParsedRequest->size() == 4))
	{
		std::string userId = *++it;
		std::string taskId = *++it;
		std::string currentTime = *++it;

		reply = this->pTask->GetHash(userId, taskId, currentTime);
		strcpy_s(this->pWriteBufer.get(), this->pipeBufSize, reply.c_str());
		return;
	}
}
void Recognizer::Split(const std::string &s, char delim) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		this->_pParsedRequest->push_back(item);
	}
}
