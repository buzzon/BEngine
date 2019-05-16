#include "Message.h"

void message(const std::string& message)
{
	std::cout << "[" << b_name << "] : "<< message << " \n";
}

void error_message(const std::string& message) {
	std::cout << "[" << b_name << "] [ERROR] : " << message << " \n";
}

void cause_exeption(const std::string& message) {
	error_message(message);
	system("pause");
	throw std::invalid_argument(message);
}
