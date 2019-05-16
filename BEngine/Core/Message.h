#pragma once

#include <stdexcept>
#include <iostream>
#include <string>

constexpr char * b_name = "BEngine";

/* ��������� ��������� ���� :
 [BEngine] : <message> */
void message(const std::string& message);

/* ��������� ��������� ���� :
 [BEngine] [ERROR] : <message> */
void error_message(const std::string& message);

/* ��������� ��������� ErrorMessage � ������ ���������� <message> */
void cause_exeption(const std::string& message);
