#pragma once

#include <stdexcept>
#include <iostream>
#include <string>

#define BName "BEngine"

/* Оставляет сообщение вида :
[BEngine] : <message>*/
void Message(std::string message);

/* Оставляет сообщение вида :
[BEngine] [ERROR] : <message>*/
void ErrorMessage(std::string message);

/* Оставляет сообщение ErrorMessage и выдает исключение <message> */
void CauseExeption(std::string message);
