#pragma once


#include <regex>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;


inline bool isNotNegativeFloat(const string& s)
{
    const regex digit_regex("^[\+]?[0-9]+(\,[0-9])?[0-9]*");
    return regex_match(s, digit_regex);
}

inline bool isNotNegativeInteger(const string& s)
{
    const regex digit_regex("^[\+]?[0-9]+");
    return regex_match(s, digit_regex);
}

inline float inputNotNegativeFloat(const string& msg)
{
    char str[100];
    bool first = true;
    do {
        if (!first) cout << "Некорректный ввод, введите еще раз >> ";
        cout << msg;
        cin >> str;
        first = false;
    } while (!isNotNegativeFloat(str));
    return atof(str);
}

inline int inputNotNegativeInteger(const string& msg)
{
    char str[100];
    bool first = true;
    do
    {
        if (!first) cout << "Некорректный ввод, введите еще раз >> ";
        cout << msg;
        cin >> str;
        first = false;
    } while (!isNotNegativeInteger(str));
    return atoi(str);
}

inline char* inputString(string msg)
{
    cout << msg;
    char ch = 0;
    char* str = new char[100];
    int i = 0;
    cin.ignore(1000, '\n');
    while ((ch = cin.get()) != '\n') {
        str[i++] = ch;
    }
    str[i] = '\0';
    return str;
}


