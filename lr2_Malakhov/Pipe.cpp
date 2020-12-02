
#include "Pipe.h"


int Pipe::MAX_ID = 0;

Pipe::Pipe(int needed) 
{
	if (needed != -1)
	id = ++MAX_ID;
}

Pipe::Pipe()
{
	id = ++MAX_ID;
}

void Pipe::setID(int id) {
	this->id = id;
}

int Pipe::getID()
{
	return id;
}

std::ostream& operator << (std::ostream& out, const Pipe& p)
{
	out << "ID: " << p.id << std::endl;
	out << "�����: " << p.length << std::endl;
	out << "�������: " << p.diam << std::endl;
	out << (p.repaired ? "� ������� !" : "�� � �������!");
	out << std::endl;
	return out;
}
std::istream& operator >> (std::istream& in, Pipe& pipe1)
{
	pipe1.length = inputNotNegativeFloat("������� �����: ");
	pipe1.diam = inputNotNegativeFloat("������� �������: ");
	return in;
}