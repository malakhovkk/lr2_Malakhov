#pragma once
class CS
{
private:
    int id;
public:
    static int MAX_ID;
    CS();
    char name[100];
    int number;
    int numberOfAvailable;
    float efficiency;

    //friend std::ostream& operator << (std::ostream& out, const Pipe& pipe);
    //friend std::istream& operator >> (std::istream& in, Pipe& pipe);
};

