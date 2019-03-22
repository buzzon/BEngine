#include "Message.h"

void Message(std::string message)
{
	std::cout << "[" << BName << "] : "<< message << " \n";
}

void ErrorMessage(std::string message) {
	std::cout << "[" << BName << "] [ERROR] : " << message << " \n";
}

void CauseExeption(std::string message) {
	ErrorMessage(message);
	system("pause");
	throw std::invalid_argument(message);
}
