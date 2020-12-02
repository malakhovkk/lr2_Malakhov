#include "CS.h"

int CS::MAX_ID = 0;
CS::CS(int needed)
{
    if(needed != -1)
	id = ++MAX_ID;
}

CS::CS()
{
    id = ++MAX_ID;
}

void CS::setID(int id) {
    this->id = id;
}
int CS::getID()
{
    return id;
}
std::ostream& operator << (std::ostream& out, const CS& cs)
{
    out << "ID: " << cs.id << std::endl;
	out << "������������: " << cs.name << std::endl;
	out << "���������� �����: " << cs.number << std::endl;
	out << "���������� ����� � ������: " << cs.numberOfAvailable << std::endl;
	out << "���������� �������������: " << cs.efficiency << std::endl;
	return out;
}
std::istream& operator >> (std::istream& in, CS& cs1)
{
    strcpy_s(cs1.name, inputString("������� ������������: "));
    cs1.number = inputNotNegativeInteger("������� ���������� �����: ");
    int cur = inputNotNegativeInteger("������� ���������� ����� � ������: ");
    while (cur > cs1.number)
    {
        std::cout << "��������� ����� ������ ���������� �����! ";
        cur = inputNotNegativeInteger("������� ���������� ����� � ������: ");
    }
    cs1.numberOfAvailable = cur;
    cs1.efficiency = inputNotNegativeFloat("������� ���������� �������������: ");
	return in;
}