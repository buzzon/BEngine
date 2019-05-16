#pragma once

#include <stdexcept>
#include <iostream>
#include <string>

constexpr char * b_name = "BEngine";

/* Оставляет сообщение вида :
 [BEngine] : <message> */
void message(const std::string& message);

/* Оставляет сообщение вида :
 [BEngine] [ERROR] : <message> */
void error_message(const std::string& message);

/* Оставляет сообщение ErrorMessage и выдает исключение <message> */
void cause_exeption(const std::string& message);
