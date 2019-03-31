#pragma once

#include <stdexcept>
#include <iostream>
#include <string>

#define BName "BEngine"

/* ��������� ��������� ���� :
[BEngine] : <message>*/
void Message(std::string message);

/* ��������� ��������� ���� :
[BEngine] [ERROR] : <message>*/
void ErrorMessage(std::string message);

/* ��������� ��������� ErrorMessage � ������ ���������� <message> */
void CauseExeption(std::string message);
