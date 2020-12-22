// lr1_Malakhov.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <map>
//#include <regex>
//#include <string>
#include "Pipe.h"
#include "utils.h"
#include "CS.h"
#include <unordered_map>
#include <queue>
#include <iterator>
using namespace std;

#define INF 1E6

struct pairCS
{
    int idCS;
    int idPipe;
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
    p1.idPipe = idPipe;
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
            cout << cs->idCS  << " кс длиной " << mapPipe[cs->idPipe].length;
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
    if (g.find(v) != g.end()) {

        arr = g[v];
        for (auto& el : arr) {
            int to = el.idCS;

            if (!count[to])
                dfs(to, g, count, ans);
        }
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

void OutputGraphToFile(unordered_map<int, vector<pairCS>> graph, char* str)
{

    ofstream fout;
    fout.open(string(str) + ".txt");
    if (!fout.is_open())
        cout << "Файл не может быть открыт!\n";
    else
    {

        for (auto& el : graph)
        {
            fout << el.second.size() << " ";
            fout <<  el.first << " ";
            for (auto cs = el.second.begin(); cs != el.second.end(); cs++)
            {
                fout << cs->idCS << " " << cs->idPipe << " ";
            }
            fout << endl;
        }
        cout << "Вывели в файл данные";
        fout.close();
    }
}



void InputGraphFromFile(unordered_map<int, vector<pairCS>>& graph, char* str)
{

    ifstream fin(string(str) + ".txt");
    if (!fin.is_open())
        cout << "Файл не может быть открыт!\n";
    else
    {
        int buff;
        while (fin >> buff)
        {
            int CSid1;
            fin >> CSid1;
            for (int i = 0; i < buff; i++)
            {
                int CSid2;
                fin >> CSid2;
                int Pipeid;
                fin >> Pipeid;
                pairCS pair1;
                pair1.idCS = CSid2;
                pair1.idPipe = Pipeid;
                graph[CSid1].push_back(pair1);
            }
        }
        cout << "Ввели из файла данные";
        fin.close();
    }

}


unordered_map<int, int> visitedCS(unordered_map<int, vector<pairCS>>& g)
{
    unordered_map<int, int> countArr;
    for (auto& el : g)
    {
        countArr[el.first] = 0;
        for (auto& p1 : el.second)
        {
            countArr[p1.idCS] = 0;
        }
    }
    return countArr;
}

bool dfs2(int v, unordered_map<int, vector<pairCS>>& g, unordered_map<int, int>& cl,  int& cycle_st) {
    if (g.find(v) == g.end())
    {
        return false;
    }
    cl[v] = 1;
    for (size_t i = 0; i < g[v].size(); ++i) {
        int to;
        to = g[v][i].idCS;
        if (cl[to] == 0) {
            if (dfs2(to, g, cl, cycle_st))  return true;
        }
        else if (cl[to] == 1) {
            //cycle_end = v;
            cycle_st = to;
            return true;
        }
    }
    cl[v] = 2;
    return false;
}

bool searchForCycle(unordered_map<int, vector<pairCS>>& graph)
{
    //vector<char> cl;
    unordered_map<int, int> p;
    int cycle_st, cycle_end;
    p = visitedCS(graph);
    //cl.assign(p.size(), 0);
    cycle_st = -1;
    for (auto& el : p)
            if (dfs2(el.first, graph, p, cycle_st)) break;
    if (cycle_st == -1) return false;
    else return true;
}

bool checkIfOk(unordered_map<int, vector<pairCS>>& graph, unordered_map<int, CS>& mapCS, unordered_map<int, Pipe>& mapPipe, int& idCS)
{
    
    bool exist = false;
    vector<int> toDelete;
    if (graph.find(idCS) != graph.end())
    {
        graph.erase(idCS);
        exist = true;
    }
    //if (graph.find(idCS) != graph.end()) return false;
    for (auto el = graph.begin(); el != graph.end(); el++)
    {
        for (auto it = 0; it < el->second.size(); it++)
        {
            if (el->second[it].idCS == idCS) {
                el->second.erase(el->second.begin() + it);
                exist = true;
                toDelete.push_back(el->first);
            }
        }
    }

    //for (auto& i : toDelete)
    //{
    //    if (graph[i].size() == 0) graph.erase(i);
    //}
    return exist;
}

void deleteConnection(unordered_map<int, vector<pairCS>>& graph, unordered_map<int, CS> mapCS, unordered_map<int, Pipe>& mapPipe)
{
    int idCS = inputNotNegativeInteger("Введите ID КС: ");

    while (mapCS.find(idCS) == mapCS.end())
    {
        cout << "Введите еще раз, в сети нет такой КС!\n";
        idCS = inputNotNegativeInteger("Введите ID КС: ");
    }
    if (checkIfOk(graph, mapCS, mapPipe, idCS))
    {
        cout << "Успешно удален!\n";
    }
    else
    {
        cout << "Произошла ошибка\n";
    }


}

int FindShortestPath(unordered_map<int, vector<pairCS>>& graph, unordered_map<int, Pipe>& mapPipe, const int & idCS1, const int& idCS2)
{
   /* queue<int> q;
    unordered_map<int, bool> used = countCS(graph);
    int n = used.size();
    q.push(idCS1);
    vector<int> d(n, INT_MAX), p(n);
    used[idCS1] = true;
    p[idCS1] = -1;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (size_t i = 0; i < graph[v].size(); ++i) {
            int to = graph[v][i].idCS;
            if (!used[to]) {
                used[to] = true;
                q.push(to);
                d[to] = d[v] + mapPipe[graph[v][i].idPipe].length;
                p[to] = v;
            }
        }
    }
    int sum = 0;*/


        unordered_map<int, bool> u  = countCS(graph);
        int n = u.size();
        int s = idCS1; // стартовая вершина

        unordered_map<int, float> d;
        for (auto& el : graph)
        {
            d[el.first] = 1e5;
            for (auto& el2 : el.second)
            {
                d[el2.idCS] = 1e5;
            }
        }
        unordered_map<int, int> p;
        for (auto& el : graph)
        {
            p[el.first] = 0;
            for (auto& el2 : el.second)
            {
                p[el2.idCS] = 0;
            }
        }
        d[s] = 0;

       // for (int i = 0; i < n; ++i) {
        for (auto i1 = u.begin(); i1 != u.end(); i1++) {
            //int i = i1->first;
            int v = -1;
           // for (int j = 0; j < n; ++j)
            for (auto j1 = u.begin(); j1 != u.end(); j1++) {
                int j = j1->first;
                if (!u[j] && (v == -1 || d[j] < d[v]))
                    v = j;
            }
            if (d[v] == 1e5)
                break;
            u[v] = true;

            for (auto j = graph[v].begin(); j != graph[v].end(); ++j) {
                int to = j->idCS;
                 float   len = mapPipe[j->idPipe].length;
                if (d[v] + len < d[to]) {
                    d[to] = d[v] + len;
                    p[to] = v;
                }
            }
        }
        
        if (d[idCS2] < 1e5)
        {
            vector<int> path;
            for (int v = idCS2; v != s; v = p[v])
                path.push_back(v);
            path.push_back(s);
            reverse(path.begin(), path.end());
            cout << "Путь: ";
            for (int& i : path)
            {
                cout << i << " ";
            }
        }
   /* int sum = 0;
    for (int v = idCS2; v != s; v = p[v])
        sum += d[v];*/

    /*vector<int> path;
    for (int v = idCS2; v != s; v = p[v])
        path.push_back(v);
    path.push_back(s);

    for (auto& i : d) cout << i.second << " ";\
    cout << endl;
    cout << endl;*/

    return d[idCS2];
}




int bfs(unordered_map<int, vector<pairCS>>& graph, int id_from, int id_to, unordered_map<int, int>& path, map <pair<int, int>, float> flow, map <pair<int, int>, float>& capacity)
{
    //unordered_map<int, int>color; //цвета вершин
    unordered_map<int, int>queue; //Очередь, хранящая номера вершин входящих в неё
    //vector<int>path; //массив пути
    //map <pair<int,int>,int> flow;
   // map <pair<int, int>, int> capacity;

    unordered_map<int, int> color;
    for (auto i = graph.begin(); i != graph.end(); i++)
    {
        color[i->first] = 0; //отмечаем все вершины непройденными WHITE=0
        for (auto el : i->second)
        {
            color[el.idCS] = 0;
        }
    }
    
    auto head = graph.begin();   // Начало очереди 0
    auto tail = graph.begin();   // Хвост 0

    queue[tail->first] = id_from;   // Вступили на первую вершину
    tail++;
    color[id_from] = 1;

    path[id_from] = -1;   // Специальная метка для начала пути
    while (head != tail) //Пока хвост не совпадет с головой
    {
        int u = queue[head->first]; //вершина u пройдена
        head++;
        color[u] = -1;

        for (auto i = color.begin(); i != color.end(); i++) // Смотрим смежные вершины
        {
            // Если не пройдена и не заполнена
            if (color[i->first] == 0 && (capacity[make_pair(u, i->first)] - flow[make_pair(u, i->first)] > 0))
            {
                // Вступаем на вершину v
                queue[tail->first] = i->first;
                tail++;
                color[i->first] = 1;
                path[i->first] = u; // Путь обновляем
            }
        }
    }
    if (color[id_to] == -1) // Если конечная вершина, дошли - возвращаем 0, прочитанная
        return 0;
    else return 1;
}
float min(float a, float b)
{
    return (a < b) ? a : b;
}
void max_flow(unordered_map<int, vector<pairCS>>& graph, unordered_map<int, Pipe >& mapPipe)
{

    int source = inputNotNegativeInteger( "Введите id КС - исток: ");
    int stock = inputNotNegativeInteger( "Введите id КС - сток: ");
    if (graph.find(source) != graph.end())
    {
        int u;
        int maxflow = 0;            // Изначально нулевой
        map <pair<int, int>, float> flow;
        unordered_map<int, int>path;
        map <pair<int, int>, float> capacity;
        for (const auto& i : graph)  // Зануляем матрицу потока
        {
            float res;
            for (auto& x : i.second)
            {
                float res = sqrt((float)pow(mapPipe[x.idPipe].diam, 5)/ (float)mapPipe[x.idPipe].length);
                capacity[make_pair(i.first, x.idCS)]=  res ;
                flow[make_pair(i.first, x.idCS)] = 0;
            }
        }
        while (bfs(graph, source, stock, path, flow, capacity) == 0)             // Пока существует путь
        {
            int delta = INT_MAX;
            for (u = graph.begin()->first; path[u] >= 0; u = path[u]) // Найти минимальный поток в сети
            {
                delta = min(delta, capacity[make_pair(path[u], u)] - flow[make_pair(path[u], u)]);
            }
            for (u = graph.begin()->first; path[u] >= 0; u = path[u]) // По алгоритму Форда-Фалкерсона 
            {
                flow[make_pair(path[u], u)] += delta;
                flow[make_pair(u, path[u])] -= delta;
            }
            maxflow += delta;                       // Повышаем максимальный поток
        }
        cout << "Максимальный поток: " << source << " -> " << stock << " = " << maxflow << endl;
    }
    else cout << "Невозможно!" << endl;
}


//struct edge {
//    int a, b, cap, flow;
//};
//
//int n, s, t, d[MAXN], ptr[MAXN], q[MAXN];
//vector<edge> e;
//vector<int> g[MAXN];
//
//void add_edge(int a, int b, int cap) {
//    edge e1 = { a, b, cap, 0 };
//    edge e2 = { b, a, 0, 0 };
//    g[a].push_back(e.size());
//    e.push_back(e1);
//    g[b].push_back(e.size());
//    e.push_back(e2);
//}
//
//bool bfs() {
//    int qh = 0, qt = 0;
//    q[qt++] = s;
//    d(n, -1);
//    d[s] = 0;
//    while (qh < qt && d[t] == -1) {
//        int v = q[qh++];
//        for (size_t i = 0; i < g[v].size(); ++i) {
//            int id = g[v][i],
//                to = e[id].b;
//            if (d[to] == -1 && e[id].flow < e[id].cap) {
//                q[qt++] = to;
//                d[to] = d[v] + 1;
//            }
//        }
//    }
//    return d[t] != -1;
//}
//
//int dfs(int v, int flow) {
//    if (!flow)  return 0;
//    if (v == t)  return flow;
//    for (; ptr[v] < (int)g[v].size(); ++ptr[v]) {
//        int id = g[v][ptr[v]],
//            to = e[id].b;
//        if (d[to] != d[v] + 1)  continue;
//        int pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
//        if (pushed) {
//            e[id].flow += pushed;
//            e[id ^ 1].flow -= pushed;
//            return pushed;
//        }
//    }
//    return 0;
//}
//
//int dinic() {
//    int flow = 0;
//    for (;;) {
//        if (!bfs())  break;
//        memset(ptr, 0, n * sizeof ptr[0]);
//        vector<int> ptr()
//        while (int pushed = dfs(s, INF))
//            flow += pushed;
//    }
//    return flow;
//}



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
            "13. Добавить две КС, соединенные трубой в газотранспортную сеть" << endl <<
            "14. Топологическая сортировка" << endl <<
            "15. Вывод сети в файл" << endl <<
            "16. Ввод сети из файла" << endl <<
            "17. Отобразить сеть" << endl <<
            "18. Удалить вершину из графа" << endl <<
            "19. Удалить граф" << endl <<
            "20. Удалить ребро из графа" << endl <<
            "21. Поиск кратчайшего пути" << endl <<
            "22. Поиск максимального потока " << endl <<
            "0. Выход" << endl;
        command = inputNotNegativeInteger("Введите номер команды: ");
        while (command > 22)
        {
            cout << "Введенное число больше 22! ";
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
            char* str = inputString("Введите название: ");
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
            for (auto& pipe1 : mapPipe)
            {
                cout << pipe1.second;
            }
            system("pause");
            break;
        }
        case 13:
        {
            DisplayCS(mapCS);
            DisplayPipes(mapPipe);
            if (mapCS.size() >= 2)
            {
                unordered_map<int, bool> usedPipes;

                for (auto& el : mapPipe)
                {
                    usedPipes.insert(make_pair(el.first, false));
                }
                for (auto& el : graph)
                {
                    for (auto& p1 : el.second)
                    {
                        usedPipes[p1.idPipe] = true;
                    }
                }
                int times = inputNotNegativeInteger("Сколько раз Вы собираетесь вводить КСx2 и Трубу?");
                int idPipe = 0, idCS1 = 0, idCS2 = 0;
                while (times > 0)
                {
                    idPipe = inputNotNegativeInteger("Введите ID трубы (введите 0, чтобы выйти): ");
                    if (idPipe == 0) break;
                    while (mapPipe.find(idPipe) == mapPipe.end() || usedPipes[idPipe] || mapPipe[idPipe].repaired)
                    {
                        cout << "Введите еще раз!\n";
                        idPipe = inputNotNegativeInteger("Введите ID трубы (введите 0, чтобы выйти): ");
                        if (idPipe == 0) break;
                    }
                    if (idPipe == 0) break;
                    usedPipes[idPipe] = true;
                    idCS1 = inputNotNegativeInteger("Введите ID КС1, от которой идет труба (введите 0, чтобы выйти): ");
                    if (idCS1 == 0) break;
                    while (mapCS.find(idCS1) == mapCS.end())
                    {
                        cout << "Введите еще раз!\n";
                        idCS1 = inputNotNegativeInteger("Введите ID КС1, от которой идет труба (введите 0, чтобы выйти): ");
                        if (idCS1 == 0) break;
                    }
                    if (idCS1 == 0) break;
                    idCS2 = inputNotNegativeInteger("Введите ID КС2, к которой идет труба (введите 0, чтобы выйти): ");
                    if (idCS2 == 0) break;
                    while (mapCS.find(idCS2) == mapCS.end())
                    {
                        cout << "Введите еще раз!\n";
                        idCS2 = inputNotNegativeInteger("Введите ID КС2, к которой идет труба (введите 0, чтобы выйти): ");
                        if (idCS2 == 0) break;
                    }
                    if (idCS2 == 0) break;
                    times--;
                    addConnection(graph, mapCS, mapPipe, idPipe, idCS1, idCS2);
                }
                if(idPipe != 0 || idCS1 != 0 || idCS2 != 0) displayGraph(graph, mapCS, mapPipe);
            }
            else
            {
                cout << "Невозможно совершить операцию!";
            }
            system("pause");
            break;
        }
        case 14:
        {
            if (!searchForCycle(graph))
            {
                unordered_map<int, bool> count;
                vector<int> ans;
                topologicalSort(graph, count, ans);
                for (auto index = ans.begin(); index != ans.end(); index++)
                {
                    cout << *index;
                    if (index + 1 != ans.end()) cout << " -> ";
                }
            }
            else
            {
                cout << "Граф цикличный!";
            }
            system("pause");
            break;
        }
        case 15:
        {
            char* str = inputString("Введите название: ");

            OutputGraphToFile(graph, str);

            system("pause");
            break;
        }
        case 16:
        {
            char* str = inputString("Введите название: ");

            InputGraphFromFile(graph, str);
            system("pause");
            break;
        }
        case 17:
        {
            displayGraph(graph, mapCS, mapPipe);
            system("pause");
            break;
        }
        case 18:
        {
            deleteConnection(graph, mapCS, mapPipe);
            system("pause");
            break;
        }
        case 19:
        {
            graph.clear();
            cout << "Граф удалён!\n";
            system("pause");
            break;
        }
        case 20:
        {
            int i = 1;
            for (auto& el : graph)
            {
                for (auto it = el.second.begin(); it != el.second.end(); ++it)
                {
                    cout << "Номер ребрa: " << i << endl;
                    cout << el.first << " -> " << it->idCS << endl;
                    i++;
                }
            }
            int num = inputNotNegativeInteger("Введите номер ребра, который нужно удалить:");
            while (num <= 0 || num > i)
            {
                cout << "Неверный ввод:\n";
                num = inputNotNegativeInteger("Введите номер ребра, который нужно удалить:");
            }
            int i2 = 1;
            int res;
            int resI;
            bool fetched = false;
            for (auto& el : graph)
            {
                if (fetched) break;
                for (auto it = 0; it < el.second.size() && !fetched; ++it)
                {
                    if (i2 == num)
                    {
                        res = it;
                        resI = el.first;
                        fetched = true;
                    }
                    i2++;
                }
            }
            graph[resI].erase(graph[resI].begin() + res);
            break;
        }
        case 21:
        {
            unordered_map <int, bool> usedCS;
            //for (auto& el : mapCS)
            //{
            //    usedCS.insert(make_pair(el.first, false));
            //}
            for (auto& el : graph)
            {
                usedCS[el.first] = true;
                for (auto& p1 : el.second)
                {
                    usedCS[p1.idCS] = true;
                }
            }
            int idCS1 = inputNotNegativeInteger("Введите ID 1 КС: ");
            while (graph.find(idCS1) == graph.end())
            {
                cout << "Некорректный ввод или из этой вершины не выходят ребра\n";
                idCS1 = inputNotNegativeInteger("Введите ID 1 КС: ");
            }
            int idCS2 = inputNotNegativeInteger("Введите ID 2 КС: ");
            while (usedCS.find(idCS2) == usedCS.end())
            {
                cout << "Некорректный ввод\n";
                idCS2 = inputNotNegativeInteger("Введите ID 2 КС: ");
            }
            float path = FindShortestPath(graph, mapPipe, idCS1, idCS2);
            if (path >= 1e5)
            {
                cout << "Нет пути";
            }
            else
            {
                cout << "Длина пути:" << path;
            }
            system("pause");
            break;
        }
        case 22:
        {
            max_flow(graph, mapPipe);
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