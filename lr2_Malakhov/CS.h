#pragma once
#include <iostream>
#include "utils.h"


class CS
{
private:
    int id;
public:
    static int MAX_ID;
    CS(int needed);
    CS();
    char name[100];
    int number;
    int numberOfAvailable;
    float efficiency;
    void setID(int id);
    int getID();
    friend std::ostream& operator << (std::ostream& out, const CS& pipe);
    friend std::istream& operator >> (std::istream& in, CS& pipe);
};

