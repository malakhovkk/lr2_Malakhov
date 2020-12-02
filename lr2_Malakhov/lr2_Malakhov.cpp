﻿// lr1_Malakhov.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
//#include <regex>
//#include <string>
#include "Pipe.h"
#include "utils.h"
#include "CS.h"
#include <unordered_map>
using namespace std;

struct pairCS
{
    int idCS;
    float length;
};

void AddPipe( unordered_map<int, Pipe>& mapPipe)
{
    Pipe pipe1(0);
    pipe1.length = inputNotNegativeFloat("Введите длину: ");
    pipe1.diam = inputNotNegativeFloat("Введите диаметр: ");
    mapPipe.insert(make_pair(pipe1.getID(), pipe1));
}



void AddCS(unordered_map<int, CS>& mapCS)
{
    CS cs1(0);
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
    mapCS.insert(make_pair(cs1.getID(), cs1));
}

void DisplayCS(unordered_map<int, CS>& mapCS)
{
    int i = 1;
    if (mapCS.size() == 0) cout << "Нет КС!";
    for (auto& it : mapCS)
    {
        cout << "Компрессорная станция №: " << i++ << endl;
        cout << "ID: " << it.second.getID() << std::endl;
        cout << "Наименование: " << it.second.name << endl;
        cout << "Количество цехов: " << it.second.number << endl;
        cout << "Количество цехов в работе: " << it.second.numberOfAvailable << endl;
        cout << "Показатель эффективности: " << it.second.efficiency << endl << endl;
    }
}

void DisplayPipes(unordered_map<int, Pipe>& mapPipe)
{

    int i = 1;

    if (mapPipe.size() == 0) cout << "Нет труб!";
    for (auto& it : mapPipe)
    {
        cout << "Труба №: " << i++ << endl;
        cout << "ID: " << it.second.getID() << endl;
        cout << "Длина: " << it.second.length << endl;
        cout << "Диаметр: " << it.second.diam << endl;
        cout << (it.second.repaired ? "В ремонте !" : "Не в ремонте!");
        cout << endl;
    }
}

void EditPipes(unordered_map<int, Pipe>& mapPipe)
{
    DisplayPipes(mapPipe);
    int num;
    num = inputNotNegativeInteger("Введите ID трубы: ");
    if (mapPipe.find(num) == mapPipe.end())
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
        mapPipe[num].repaired = (bool)isRepaired;

        cout << "Исправленная труба: " << endl;
        cout << "Длина: " << mapPipe[num].length << endl;
        cout << "Диаметр: " << mapPipe[num].diam << endl;
        cout << (mapPipe[num].repaired ? "В ремонте !" : "Не в ремонте!");

        // ВЫВЕСТИ ТРУБУ, КОТОРУЮ ОТРЕДАКТИРОВАЛИ
    }
}

void EditCS(unordered_map<int, CS>& mapCS)
{
    DisplayCS(mapCS);
    int num;
    num = inputNotNegativeInteger("Введите ID КС: ");
    if (mapCS.find(num) == mapCS.end())
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

        if (mapCS[num].numberOfAvailable + res >= 0 && mapCS[num].numberOfAvailable + res <= mapCS[num].number)
        {
            mapCS[num].numberOfAvailable += res;

            cout << "Измененная компрессорная станция: " << endl;
            cout << "Наименование: " << mapCS[num].name << endl;
            cout << "Количество цехов: " << mapCS[num].number << endl;
            cout << "Количество цехов в работе: " << mapCS[num].numberOfAvailable << endl;
            cout << "Показатель эффективности: " << mapCS[num].efficiency << endl << endl;

        }
        else
        {
            cout << "Невозможно выполнить действие";
        }
    }
}

void OutputToFile(unordered_map<int, CS>& mapCS, unordered_map<int, Pipe>& mapPipe, char * str)
{

    ofstream fout;
    fout.open(string(str) + ".txt");
    if (!fout.is_open())
        cout << "Файл не может быть открыт!\n";
    else
    {
   
        for (auto& it : mapCS)
        {
            fout << "cs" << endl;
            int id = it.second.getID();
            fout <<  id << endl;
            fout <<  it.second.name << endl;
            fout <<  it.second.number << endl;
            fout <<  it.second.numberOfAvailable << endl;
            fout <<  it.second.efficiency << endl << endl;
        }

     
        
        for (auto& it : mapPipe)
        {
            fout << "pipe" << endl;
            int id = it.second.getID();
            fout << id << endl;
            fout << it.second.length << endl;
            fout << it.second.diam << endl;
            fout << (it.second.repaired ? 1 : 0) << endl;
        }
        cout << "Вывели трубы и КС в файл output.txt";

        fout.close();
    }
}

void InputFromFile(unordered_map<int, CS>& mapCS, unordered_map<int, Pipe>& mapPipe, char* str)
{
    ifstream fin(string(str) + ".txt");
    if (!fin.is_open())
        cout << "Файл не может быть открыт!\n";
    else
    {
        mapPipe.clear();
        mapCS.clear();
        string buff;
        int maxid1 = -1;
        int maxid2 = -1;
        while (fin >> buff)
        {
            Pipe pipe1(-1);
            CS cs1(-1);
            if (buff == "pipe")
            {
                int id;
                fin >> id;
                pipe1.setID(id);
                fin >> pipe1.length;
                fin >> pipe1.diam;
                fin >> pipe1.repaired;
                mapPipe.insert(make_pair(pipe1.getID(), pipe1));
                if (maxid1 < id) maxid1 = id;
            }
            else
            {
                int id;
                fin >> id;
                cs1.setID(id);
                fin >> cs1.name;
                fin >> cs1.number;
                fin >> cs1.numberOfAvailable;
                fin >> cs1.efficiency;
                mapCS.insert(make_pair(cs1.getID(), cs1));
                if (maxid2 < id) maxid2 = id;
            }
            Pipe::MAX_ID = maxid1;
            CS::MAX_ID = maxid2;
        }
    }
    cout << "Ввели из файла данные";
    fin.close();
}

void EraseFromPipes(unordered_map<int, Pipe>& mapPipe)
{

    DisplayPipes(mapPipe);
    if (mapPipe.size() > 0) {
        int number;
        do {
            number = inputNotNegativeInteger("Введите ID КС, которую нужно удалить: ");
        } while (mapPipe.find(number) == mapPipe.end());
        mapPipe.erase(mapPipe.find(number));
    }
}

void EraseFromCS(unordered_map<int, CS>& mapCS)
{

    DisplayCS(mapCS);
    if (mapCS.size() > 0) {
        int number;
        do {
            number = inputNotNegativeInteger("Введите ID КС, которую нужно удалить: ");
        } while (mapCS.find(number) == mapCS.end());
        mapCS.erase(mapCS.find(number));
    }
}

vector<int> CSFilterByName(unordered_map<int, CS>& mapCS, char* str)
{
    vector<int> res;
    for (auto &cs1: mapCS) {
        if (strcmp(cs1.second.name, str) == 0) {
            res.push_back(cs1.first);
        }
    }
    return res;
}

float percent(CS cs1)
{
    return ((float)cs1.number - (float)cs1.numberOfAvailable) / (float)cs1.number * 100;
}

vector<int> CSFilterByPerc(unordered_map<int, CS>& mapCS, float perc)
{
    vector<int> res;
    for (auto& cs1 : mapCS) {
        if (abs(percent(cs1.second) - perc) <= 1) {
            res.push_back(cs1.first);
        }
    }
    return res;
}

vector<int> PipeFilterByRepaired(unordered_map<int, Pipe>& mapPipe, bool repaired = true)
{
    vector<int> res;
    for (auto& pipe1 : mapPipe) {
        if (pipe1.second.repaired) {
            res.push_back(pipe1.first);
        }
    }
    return res;
}

void addConnection(unordered_map<int, vector<pairCS>>& graph, unordered_map<int, CS>& mapCS, unordered_map<int, Pipe>& mapPipe, int idPipe, int idCS1, int idCS2)
{
    pairCS p1;
    p1.length = mapPipe[idPipe].length;
    p1.idCS = idCS2;
    graph[idCS1].push_back(p1);
}
void displayGraph(unordered_map<int, vector<pairCS>>& graph, unordered_map<int, CS>& mapCS, unordered_map<int, Pipe>& mapPipe)
{
    for (auto& el: graph)
    {
        cout << "КС с ID " << el.first << " соединен с: ";
        for (auto cs = el.second.begin(); cs != el.second.end(); cs++)
        {
            cout << cs->idCS  << " трубой длиной " << cs->length;
            if (cs + 1 != el.second.end()) cout << ", ";
        }
        cout << endl;
    }
}

struct pairUsed
{
    int id;
    bool used;
};

void dfs(int v, unordered_map<int, vector<pairCS>>& g, unordered_map<int, bool>& count, vector<int>& ans) {
    count[v] = true;
    vector<pairCS> arr;
    arr = g[v];
    for (auto & el: arr) {
        int to = el.idCS;
        if (!count[to])
            dfs(to, g, count, ans);
    }
    ans.push_back(v);
}

unordered_map<int, bool> countCS(unordered_map<int, vector<pairCS>>& g)
{
    unordered_map<int, bool> countArr;
    for (auto& el : g)
    {
        countArr[el.first] = false;
        for (auto& p1 : el.second)
        {
            countArr[p1.idCS] = false;
        }
    }
    return countArr;
}

void topologicalSort( unordered_map<int, vector<pairCS>>& g, unordered_map<int, bool>& count, vector<int>& ans) {
    count = countCS(g);
       
    ans.clear();
    for (auto & el: count)
        if (!el.second)
            dfs(el.first, g, count, ans);
    reverse(ans.begin(), ans.end());
}


int main()
{
   
    setlocale(LC_ALL, "Russian");
    unordered_map<int, CS> mapCS;
    unordered_map<int, Pipe> mapPipe;
    //vector < vector<int> > graph;
    unordered_map<int, vector<pairCS>> graph;

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
            "13. Соединить две КС трубой в газотранспортную сеть" << endl << 
            "14. Топологическая сортировка" << endl <<
            "0. Выход" << endl;
        command = inputNotNegativeInteger("Введите номер команды: ");
        while (command > 14)
        {
            cout << "Введенное число больше 14! ";
            command = inputNotNegativeInteger("Введите номер команды: ");
        }

        switch (command)
        {
        case 1:
        {
            AddPipe(mapPipe);
            break;
        }
        case 2:
        {
            AddCS(mapCS);
            break;
        }
        case 3:
        {
            DisplayCS(mapCS);
            DisplayPipes(mapPipe);
            system("pause");
            break;
        }
        case 4:
        {
            EditPipes(mapPipe);
            system("pause");
            // Доделать
            break;
        }
        case 5:
        {
            EditCS(mapCS);
            system("pause");
            break;
        }
        case 6:
        {
            char* str = inputString("Введите название: ");
            OutputToFile(mapCS, mapPipe, str);
            system("pause");
            break;
        }
        case 7:
        {
            char* str = inputString("Введите название: ");
            InputFromFile(mapCS, mapPipe, str);
            system("pause");
            break;
        }
        case 8:
        {
            EraseFromPipes(mapPipe);
            system("pause");
            break;
        }
        case 9:
        {
            EraseFromCS(mapCS);
            system("pause");
            break;
        }
        case 10:
        {
            char *str = inputString("Введите название: ");
            auto res = CSFilterByName(mapCS, str);
            for (int i = 0; i < res.size(); i++)
            {
                cout << "Компрессорная станция №: " << i + 1 << endl;
                cout << "Наименование: " << mapCS[res[i]].name << endl;
                cout << "Количество цехов: " << mapCS[res[i]].number << endl;
                cout << "Количество цехов в работе: " << mapCS[res[i]].numberOfAvailable << endl;
                cout << "Показатель эффективности: " << mapCS[res[i]].efficiency << endl << endl;
            }
            system("pause");
            break;
        }
        case 11:
        {
            float perc = inputNotNegativeFloat("Введите процент незадействованных цехов: ");
            cout << "Результаты +-1%" << endl;
            auto res = CSFilterByPerc(mapCS, perc);
            for (int i = 0; i < res.size(); i++)
            {
                cout << "Компрессорная станция ID: " << res[i] << endl;
                cout << "Наименование: " << mapCS[res[i]].name << endl;
                cout << "Количество цехов: " << mapCS[res[i]].number << endl;
                cout << "Количество цехов в работе: " << mapCS[res[i]].numberOfAvailable << endl;
                cout << "Показатель эффективности: " << mapCS[res[i]].efficiency << endl;
                cout << "Процент незадействованных цехов: " << percent(mapCS[res[i]]) << endl << endl;
            }
            system("pause");
            break;
        }
        case 12:
        {
            cout << "Все трубы, которые в ремонте: " << endl;
            auto res = PipeFilterByRepaired(mapPipe);
            for (auto &pipe1: mapPipe)
            {
                cout << pipe1.second;
            }
            system("pause");
            break;
        }
        case 13:
        {

            /*for (int i = 0; i < mapCS.size(); ++i)
            {
                graph[i].resize(mapCS.size());
                for (int j = 0; j < mapCS.size(); ++j)
                    graph[i][j] = 0;
            }*/
            DisplayCS(mapCS);
            DisplayPipes(mapPipe);
            graph.clear();
            int times = inputNotNegativeInteger("Сколько раз Вы собираетесь вводить КСx2 и Трубу?");
            while (times > 0)
            {
                int idPipe = inputNotNegativeInteger("Введите ID трубы: ");
                while (mapPipe.find(idPipe) == mapPipe.end())
                {
                    cout << "Введите еще раз!\n";
                    idPipe = inputNotNegativeInteger("Введите ID трубы: ");
                }
                int idCS1 = inputNotNegativeInteger("Введите ID КС1, от которой идет труба: ");
                while (mapCS.find(idCS1) == mapCS.end())
                {
                    cout << "Введите еще раз!\n";
                    idCS1 = inputNotNegativeInteger("Введите ID КС1, от которой идет труба: ");
                }
                int idCS2 = inputNotNegativeInteger("Введите ID КС2, к которой идет труба: ");
                while (mapCS.find(idCS2) == mapCS.end())
                {
                    cout << "Введите еще раз!\n";
                    idCS2 = inputNotNegativeInteger("Введите ID КС2, к которой идет труба: ");
                }
                times--;
                addConnection(graph, mapCS, mapPipe, idPipe, idCS1, idCS2);
            }
            displayGraph(graph, mapCS, mapPipe);
            system("pause");
            break;
        }
        case 14:
        {
            unordered_map<int, bool> count;
            vector<int> ans;
            topologicalSort(graph, count, ans);
            for (auto index = ans.begin(); index != ans.end(); index++)
            {
                cout << *index;
                if (index + 1 != ans.end()) cout << " -> ";
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