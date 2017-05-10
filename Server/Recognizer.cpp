#include "stdafx.h"
#include "Task.h"
#include "Recognizer.h"

Recognizer::Recognizer()
{
	this->pParsedCommand.reset(new std::vector<std::string>());

}
Recognizer::Recognizer(boost::shared_ptr<Task> pTask, boost::shared_ptr<char[]> pReadBufer, boost::shared_ptr<char[]> pWriteBufer, int pipeBufSize)
{
	this->pParsedCommand.reset(new std::vector<std::string>());

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
	std::string command(this->pReadBufer.get());
	this->pParsedCommand->clear();

	this->Split(command, ';');

	std::cout << command << std::endl;
	for (auto it = this->pParsedCommand->begin(); it != this->pParsedCommand->end(); it++)
	{
		std::cout << *it << std::endl;
	}
}
void Recognizer::ExecuteCommand()
{
	auto it = this->pParsedCommand->begin();
	if (*it == "a")
	{
		this->pTask->TimeController();
	}
}
void Recognizer::Split(const std::string &s, char delim) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		this->pParsedCommand->push_back(item);
	}
}
