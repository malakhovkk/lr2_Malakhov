#include "Pipe.h"



int Pipe::MAX_ID = 0;

Pipe::Pipe() 
{
	id = ++MAX_ID;
}

std::ostream& operator << (std::ostream& out, const Pipe& p)
{
	out << "Длина: " << p.length << endl;
	out << "Диаметр: " << p.diam << endl;
	out << (p.repaired ? "В ремонте !" : "Не в ремонте!");
	out << endl;
	return out;
}
std::istream& operator >> (std::istream& in, Pipe& pipe1)
{
	pipe1.length = inputNotNegativeFloat("Введите длину: ");
	pipe1.diam = inputNotNegativeFloat("Введите диаметр: ");
	return in;
}