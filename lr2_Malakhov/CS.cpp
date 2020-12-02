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
	out << "Наименование: " << cs.name << std::endl;
	out << "Количество цехов: " << cs.number << std::endl;
	out << "Количество цехов в работе: " << cs.numberOfAvailable << std::endl;
	out << "Показатель эффективности: " << cs.efficiency << std::endl;
	return out;
}
std::istream& operator >> (std::istream& in, CS& cs1)
{
    strcpy_s(cs1.name, inputString("Введите наименование: "));
    cs1.number = inputNotNegativeInteger("Введите количество цехов: ");
    int cur = inputNotNegativeInteger("Введите количество цехов в работе: ");
    while (cur > cs1.number)
    {
        std::cout << "Введенное число больше количества цехов! ";
        cur = inputNotNegativeInteger("Введите количество цехов в работе: ");
    }
    cs1.numberOfAvailable = cur;
    cs1.efficiency = inputNotNegativeFloat("Введите показатель эффективности: ");
	return in;
}