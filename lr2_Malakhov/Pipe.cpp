#include "Pipe.h"



int Pipe::MAX_ID = 0;

Pipe::Pipe() 
{
	id = ++MAX_ID;
}

std::ostream& operator << (std::ostream& out, const Pipe& p)
{
	out << "�����: " << p.length << endl;
	out << "�������: " << p.diam << endl;
	out << (p.repaired ? "� ������� !" : "�� � �������!");
	out << endl;
	return out;
}
std::istream& operator >> (std::istream& in, Pipe& pipe1)
{
	pipe1.length = inputNotNegativeFloat("������� �����: ");
	pipe1.diam = inputNotNegativeFloat("������� �������: ");
	return in;
}