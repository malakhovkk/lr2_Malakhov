// lr1_Malakhov.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
//#include <regex>
//#include <string>
#include "Pipe.h"
#include "utils.h"
#include "CS.h"

using namespace std;


void AddPipe(vector<Pipe>& vecPipe)
{
    Pipe pipe1;
    pipe1.length = inputNotNegativeFloat("Введите длину: ");
    pipe1.diam = inputNotNegativeFloat("Введите диаметр: ");
    vecPipe.push_back(pipe1);
}



void AddCS(vector<CS>& vecCS)
{
    CS cs1;
    strcpy_s(cs1.name, inputString("Введите наименование: "));
    cs1.number = inputNotNegativeInteger("Введите количество цехов: ");
    int cur = inputNotNegativeInteger("Введите количество цехов в работе: ");
    while (cur > cs1.number)
    {
        cout << "Введенное число больше количества цехов! ";
        cur = inputNotNegativeInteger("Введите количество цехов в работе: ");
    }
    cs1.numberOfAvailable = cur;
    cs1.efficiency = inputNotNegativeFloat("Введите показатель эффективности: ");
    vecCS.push_back(cs1);
}

void DisplayCS(vector<CS>& vecCS)
{
    int i = 1;
    if (vecCS.size() == 0) cout << "Нет КС!";
    for (auto& it : vecCS)
    {
        cout << "Компрессорная станция №: " << i++ << endl;
        cout << "Наименование: " << it.name << endl;
        cout << "Количество цехов: " << it.number << endl;
        cout << "Количество цехов в работе: " << it.numberOfAvailable << endl;
        cout << "Показатель эффективности: " << it.efficiency << endl << endl;
    }
}

void DisplayPipes(vector<Pipe>& vecPipe)
{

    int i = 1;

    if (vecPipe.size() == 0) cout << "Нет труб!";
    for (auto& it : vecPipe)
    {
        cout << "Труба №: " << i++ << endl;
        cout << "Длина: " << it.length << endl;
        cout << "Диаметр: " << it.diam << endl;
        cout << (it.repaired ? "В ремонте !" : "Не в ремонте!");
        cout << endl;
    }
}

void EditPipes(vector<Pipe>& vecPipe)
{
    DisplayPipes(vecPipe);
    int num;
    num = inputNotNegativeInteger("Введите номер трубы: ");
    if (num > vecPipe.size() || num <= 0)
    {
        cout << "Такой трубы не существует! ";
    }
    else
    {

        int isRepaired = inputNotNegativeInteger("Редактирование признака 'в ремонте' для трубы(0 - не в ремонте, 1 - в ремонте): ");
        while (!(isRepaired == 0 || isRepaired == 1))
        {
            isRepaired = inputNotNegativeInteger("Редактирование признака 'в ремонте' для трубы(0 - не в ремонте, 1 - в ремонте): ");
        }
        vecPipe[num - 1].repaired = (bool)isRepaired;

        cout << "Исправленная труба: " << endl;
        cout << "Длина: " << vecPipe[num - 1].length << endl;
        cout << "Диаметр: " << vecPipe[num - 1].diam << endl;
        cout << (vecPipe[num - 1].repaired ? "В ремонте !" : "Не в ремонте!");

        // ВЫВЕСТИ ТРУБУ, КОТОРУЮ ОТРЕДАКТИРОВАЛИ
    }
}

void EditCS(vector<CS>& vecCS)
{
    DisplayCS(vecCS);
    int num;
    num = inputNotNegativeInteger("Введите номер КС: ");
    if (num > vecCS.size() || num <= 0)
    {
        cout << "Такой станции не существует! ";
    }
    else
    {
        int Add = inputNotNegativeInteger("Запуск и останов цеха в КС(1 - добавить, 0 - остановить): ");
        while (!(Add == 0 || Add == 1))
        {
            Add = inputNotNegativeInteger("Запуск и останов цеха в КС(1 - добавить, 0 - остановить): ");
        }
        int res;
        if (Add == 0)
        {
            res = -1;
        }
        else
        {
            res = 1;
        }

        if (vecCS[num - 1].numberOfAvailable + res >= 0 && vecCS[num - 1].numberOfAvailable + res <= vecCS[num - 1].number)
        {
            vecCS[num - 1].numberOfAvailable += res;

            cout << "Измененная компрессорная станция: " << endl;
            cout << "Наименование: " << vecCS[num - 1].name << endl;
            cout << "Количество цехов: " << vecCS[num - 1].number << endl;
            cout << "Количество цехов в работе: " << vecCS[num - 1].numberOfAvailable << endl;
            cout << "Показатель эффективности: " << vecCS[num - 1].efficiency << endl << endl;

        }
        else
        {
            cout << "Невозможно выполнить действие";
        }
    }
}

void OutputToFile(const vector<CS>& vecCS, const vector<Pipe>& vecPipe, char * str)
{

    ofstream fout;
    fout.open(str);
    if (!fout.is_open())
        cout << "Файл не может быть открыт!\n";
    else
    {
        int i = 1;
        if (vecCS.size() == 0) fout << "Нет КС!";
        for (auto& it : vecCS)
        {
            fout << "Компрессорная станция №: " << i++ << endl;
            fout << "Наименование: " << it.name << endl;
            fout << "Количество цехов: " << it.number << endl;
            fout << "Количество цехов в работе: " << it.numberOfAvailable << endl;
            fout << "Показатель эффективности: " << it.efficiency << endl << endl;
        }

        i = 1;
        if (vecPipe.size() == 0) fout << "Нет труб!";
        for (auto& it : vecPipe)
        {
            fout << "Труба №: " << i++ << endl;
            fout << "Длина: " << it.length << endl;
            fout << "Диаметр: " << it.diam << endl;
            fout << (it.repaired ? "В ремонте !" : "Не в ремонте!");
            fout << endl;
        }
        cout << "Вывели трубы и КС в файл output.txt";

        fout.close();
    }
}

void InputFromFile(vector<CS>& vecCS, vector<Pipe>& vecPipe, char* str)
{
    ifstream fin("input.txt");
    if (!fin.is_open())
        cout << "Файл не может быть открыт!\n";
    else
    {
        vecPipe.clear();
        vecCS.clear();
        string buff;
        while (fin >> buff)
        {
            Pipe pipe1;
            CS cs1;
            if (buff == "pipe")
            {
                fin >> pipe1.length;
                fin >> pipe1.diam;
                vecPipe.push_back(pipe1);
            }
            else
            {
                fin >> cs1.name;
                fin >> cs1.number;
                fin >> cs1.numberOfAvailable;
                fin >> cs1.efficiency;
                vecCS.push_back(cs1);
            }
        }
    }
    cout << "Ввели из файла данные";
    fin.close();
}

void EraseFromPipes(vector<Pipe>& vecPipe)
{

    DisplayPipes(vecPipe);
    if (vecPipe.size() > 0) {
        int number;
        do {
            number = inputNotNegativeInteger("Введите трубу, которую нужно удалить: ");
        } while (number > vecPipe.size() || number == 0);
        cout << "Удалена " << number << "-я труба";
        vecPipe.erase(vecPipe.begin() + number - 1);
    }
}

void EraseFromCS(vector<CS>& vecCS)
{

    DisplayCS(vecCS);
    if (vecCS.size() > 0) {
        int number;
        do {
            number = inputNotNegativeInteger("Введите КС, которую нужно удалить: ");
        } while (number > vecCS.size() || number == 0);
        cout << "Удалена " << number << "-я КС";
        vecCS.erase(vecCS.begin() + number - 1);
    }
}

vector<int> CSFilterByName(vector<CS>& vecCS, char* str)
{
    vector<int> res;
    for (int i = 0; i < vecCS.size(); ++i) {
        if (strcmp(vecCS[i].name, str) == 0) {
            res.push_back(i);
        }
    }
    return res;
}

float percent(CS cs1)
{
    return ((float)cs1.number - (float)cs1.numberOfAvailable) / (float)cs1.number * 100;
}

vector<int> CSFilterByPerc(vector<CS>& vecCS, float perc)
{
    vector<int> res;
    for (int i = 0; i < vecCS.size(); ++i) {
        if (abs(percent(vecCS[i]) - perc) <= 1) {
            res.push_back(i);
        }
    }
    return res;
}

vector<int> PipeFilterByRepaired(vector<Pipe>& vecPipe, bool repaired = true)
{
    vector<int> res;
    for (int i = 0; i < vecPipe.size(); ++i) {
        if (vecPipe[i].repaired) {
            res.push_back(i);
        }
    }
    return res;
}
int main()
{

    setlocale(LC_ALL, "Russian");
    vector<CS> vecCS;
    vector<Pipe> vecPipe;
    for (;;)
    {
        system("CLS");
        int command;
        cout << "1. Добавить трубу" << endl <<
            "2. Добавить КС" << endl <<
            "3. Просмотр всех объектов" << endl <<
            "4. Редактировать трубу" << endl <<
            "5. Редактировать КС" << endl <<
            "6. Сохранить" << endl <<
            "7. Загрузить" << endl <<
            "8. Удалить трубу" << endl <<
            "9. Удалить КС" << endl << 
            "10. Фильр КС по названию" << endl <<
            "11. Фильтр КС по проценту незадействованных цехов" << endl <<
            "12. Фильтр труб, которые в ремонте" << endl <<
            "0. Выход" << endl;
        command = inputNotNegativeInteger("Введите номер команды: ");
        while (command > 12)
        {
            cout << "Введенное число больше 12! ";
            command = inputNotNegativeInteger("Введите номер команды: ");
        }

        switch (command)
        {
        case 1:
        {
            AddPipe(vecPipe);
            break;
        }
        case 2:
        {
            AddCS(vecCS);
            break;
        }
        case 3:
        {
            DisplayCS(vecCS);
            DisplayPipes(vecPipe);
            system("pause");
            break;
        }
        case 4:
        {
            EditPipes(vecPipe);
            system("pause");
            // Доделать
            break;
        }
        case 5:
        {
            EditCS(vecCS);
            system("pause");
            break;
        }
        case 6:
        {
            char* str = inputString("Введите название: ");
            OutputToFile(vecCS, vecPipe, str);
            system("pause");
            break;
        }
        case 7:
        {
            char* str = inputString("Введите название: ");
            InputFromFile(vecCS, vecPipe, str);
            system("pause");
            break;
        }
        case 8:
        {
            EraseFromPipes(vecPipe);
            system("pause");
            break;
        }
        case 9:
        {
            EraseFromCS(vecCS);
            system("pause");
            break;
        }
        case 10:
        {
            char *str = inputString("Введите название: ");
            auto res = CSFilterByName(vecCS, str);
            for (int i = 0; i < res.size(); i++)
            {
                cout << "Компрессорная станция №: " << i + 1 << endl;
                cout << "Наименование: " << vecCS[res[i]].name << endl;
                cout << "Количество цехов: " << vecCS[res[i]].number << endl;
                cout << "Количество цехов в работе: " << vecCS[res[i]].numberOfAvailable << endl;
                cout << "Показатель эффективности: " << vecCS[res[i]].efficiency << endl << endl;
            }
            system("pause");
            break;
        }
        case 11:
        {
            float perc = inputNotNegativeFloat("Введите процент незадействованных цехов: ");
            cout << "Результаты +-1%" << endl;
            auto res = CSFilterByPerc(vecCS, perc);
            for (int i = 0; i < res.size(); i++)
            {
                cout << "Компрессорная станция №: " << i + 1 << endl;
                cout << "Наименование: " << vecCS[res[i]].name << endl;
                cout << "Количество цехов: " << vecCS[res[i]].number << endl;
                cout << "Количество цехов в работе: " << vecCS[res[i]].numberOfAvailable << endl;
                cout << "Показатель эффективности: " << vecCS[res[i]].efficiency << endl;
                cout << "Процент незадействованных цехов: " << percent(vecCS[res[i]]) << endl << endl;
            }
            system("pause");
            break;
        }
        case 12:
        {
            cout << "Все трубы, которые в ремонте: " << endl;
            auto res = PipeFilterByRepaired(vecPipe);
            for (int i = 0; i < res.size(); i++)
            {
                cout << "Труба №: " << i + 1 << endl;
                cout << vecPipe[res[i]];
            }
            system("pause");
            break;
        }
        case 0:
        {
            return 0;
        }
        default:
            break;
        }
    }
}





// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.