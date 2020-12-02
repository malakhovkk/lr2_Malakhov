#pragma once
#include <regex>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>



inline bool isNotNegativeFloat(const std::string& s)
{
    const std::regex digit_regex("^[\+]?[0-9]+(\,[0-9])?[0-9]*");
    return regex_match(s, digit_regex);
}

inline bool isNotNegativeInteger(const std::string& s)
{
    const std::regex digit_regex("^[\+]?[0-9]+");
    return regex_match(s, digit_regex);
}

inline float inputNotNegativeFloat(const std::string& msg)
{
    char str[100];
    bool first = true;
    do {
        if (!first) std::cout << "Некорректный ввод, введите еще раз >> ";
        std::cout << msg;
        std::cin >> str;
        first = false;
    } while (!isNotNegativeFloat(str));
    return atof(str);
}

inline int inputNotNegativeInteger(const std::string& msg)
{
    char str[100];
    bool first = true;
    do
    {
        if (!first) std::cout << "Некорректный ввод, введите еще раз >> ";
        std::cout << msg;
        std::cin >> str;
        first = false;
    } while (!isNotNegativeInteger(str));
    return atoi(str);
}

inline char* inputString(std::string msg)
{
    std::cout << msg;
    char ch = 0;
    char* str = new char[100];
    int i = 0;
    std::cin.ignore(1000, '\n');
    while ((ch = std::cin.get()) != '\n') {
        str[i++] = ch;
    }
    str[i] = '\0';
    return str;
}


