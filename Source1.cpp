#include <iostream>
#include <algorithm>
#include <vector>
#include <string> 
#include <iomanip>
#include <sstream>
#include <stack>
using namespace std;

vector<string>split(string& str, char delim = ' ')
{
    string word;
    stringstream in(str);
    vector<string>ans;
    while (getline(in, word, delim))
    {
        ans.push_back(word);
    }
    return ans;
}

class Punkt
{
private:
    string name;
    int cntPeople;
public:
    Punkt(const string& nm, const int& cn)
    {
        this->name = nm;
        this->cntPeople = cn;
    }
    Punkt(const Punkt& p)
    {
        this->name = p.getName();
        this->cntPeople = p.getPeoples();
    }

    string getName()const
    {
        return this->name;
    }

    int getPeoples()const
    {
        return this->cntPeople;
    }

    Punkt operator=(const Punkt& p)
    {
        if (this != &p)
        {
            this->cntPeople = p.getPeoples();
            this->name = p.getName();
        }
        return (*this);
    }
    void setName(const string& str)
    {
        this->name = str;
    }
    void setPeoples(const double& d)
    {
        this->cntPeople = d;
    }
    bool operator==(const Punkt& p)
    {
        return (this->getName() == p.getName() && this->cntPeople == p.getPeoples());
    }
    bool operator==(const string& str)
    {
        string a = this->getName();
        return equal(a.begin(), a.end(), str.begin(), str.end(), [](char a, char b) {
            return tolower(a) == tolower(b);
            });
    }
    friend istream& operator>>(istream& in, Punkt& p);
    friend ostream& operator<<(ostream& out, const Punkt& p);
};

class TGraph
{
private:
    vector<Punkt>vertex;
    struct Edge
    {
        int a;
        int b;
        double wieght;
        Edge(int src, int to, double wg)
        {
            this->a = src;
            this->b = to;
            this->wieght = wg;
        }
    };

    vector<Edge>edges;//Ребры
    int getIndexVertex(const string& s);
    double getLenghWays(int src, int to);
public:
    void AddVertex(const Punkt& p);
    void AddEdge(const string& src, const string& to, double wg);
    void removeVertex(const string& name);
    void removeEdge(int index);
    void PrintVertexes();
    vector<vector<int>> toAdjList();
    void DFS(const string& src); 
    void AlgorithmFord(const string& src, const string& to);
    void PrintGraf();

    ~TGraph()
    {
        vertex.clear();
        edges.clear();
    }

};

int main()
{
    TGraph gr;
    Punkt p1("New York", 3000000);
    Punkt p2("Uonkers", 250000);
    Punkt p3("Washington", 4000000);
    Punkt p4("Moscow", 2000000);
    Punkt p5("Sankt Peterburg", 1600000);
    Punkt p6("Parij", 2554500);
    Punkt p7("Delhi", 60000000);
    gr.AddVertex(p1);
    gr.PrintVertexes();
    gr.AddVertex(p2);
    gr.AddVertex(p3);
    gr.AddVertex(p4);
    gr.AddVertex(p5);
    gr.AddVertex(p6);
    gr.AddVertex(p7);
    gr.AddEdge("New york", "Uonkers", 255);
    gr.AddEdge("New york", "Washington", 355);
    gr.AddEdge("Moscow", "Sankt Peterburg", 175);
    gr.AddEdge("Uonkers", "Sankt Peterburg", 755);
    gr.AddEdge("Sankt Peterburg", "Washington", 1075);
    gr.AddEdge("Sankt Peterburg", "Parij", 685);
    gr.AddEdge("Uonkers", "Parij", 998);
    gr.AddEdge("Washington", "Delhi", 1554);
    cout << "============================== GRAPH =================================================\n";
    gr.PrintGraf();
    cout << "========================================================================================\n";
    gr.DFS("New York");//Запускаем DFS
    cout << "\n============================== end dfs =================================================\n";

    cout << "\n\n================================== Bellman Ford SHort way ====================================\n";
    gr.AlgorithmFord("New York", "Sankt Peterburg");//Для примера запускаем от Нью Йорк до Санкт Петербурга
    cout << "\n\n================================================================================================\n";
    return 0;
}

istream& operator>>(istream& in, Punkt& p)
{
    string st;
    getline(in, st);
    vector<string>sp = split(st, ';');
    p.setName(sp[0]);
    p.setPeoples(std::stoi(sp[1].c_str()));
    return in;
}

ostream& operator<<(ostream& out, const Punkt& p)
{
    out << setw(25) << p.getName() << "|" << setw(8) << p.getPeoples();
    return out;
}

int TGraph::getIndexVertex(const string& s)
{
    for (int i = 0; i < this->vertex.size(); i++)
        if (this->vertex[i] == s)
            return i;
    return -1;
}

double TGraph::getLenghWays(int src, int to)
{
    for (auto& it : edges)
    {
        if (it.a == src && it.b == to)
            return it.wieght;
    }
    return INT_MAX * 1.0;
}

void TGraph::AddVertex(const Punkt& p)
{
    this->vertex.push_back(p);//Добавление 
}

void TGraph::AddEdge(const string& src, const string& to, double wg)
{
    int a = getIndexVertex(src);
    int b = getIndexVertex(to);
    cout << a << endl;
    cout << b << endl;
    if (a == -1)
    {
        //Если нет такое вершина
        cout << "Error we can't found this punkt: \n";
        return;
    }
    if (b == -1)
    {
        //Если нет такое вершина
        cout << "Error we can't found this punkt: \n";
        return;
    }
    Edge ednew = Edge(a, b, wg);
    this->edges.push_back(ednew);
    cout << "added succesfuly\n";
}

void TGraph::removeVertex(const string& name)
{
    int a = getIndexVertex(name);
    if (a != -1)
    {
        vertex.erase(vertex.begin() + a);
        while (1)
        {
            int ind = -1;
            for (int i = 0; i < edges.size(); i++)
            {
                if (edges[i].a == a || edges[i].b == a)
                {
                    ind = i;
                    break;
                }
            }
            if (ind != -1)
            {
                edges.erase(edges.begin() + ind);

            }
            else
                break;
        }
        cout << "Deleted succesfuly\n";
    }
    else
    {
        cout << "Not found given punkt\n";
    }

}

void TGraph::removeEdge(int index)
{
    if (index >= 0 && index < edges.size())
    {
        edges.erase(edges.begin() + index);
        cout << "Has deleted\n";
    }
    else
    {
        cout << "Incorrect index\n";
    }
}

void TGraph::PrintVertexes()
{
    cout << setw(25) << "  Name  " << "|" << setw(8) << "Peoples" << endl;
    cout << "|++++++++++++++++++++++++|++++++++|\n";
    for (auto& it : vertex)
        cout << it << endl;
    cout << "|++++++++++++++++++++++++|++++++++|\n";
}

vector<vector<int>> TGraph::toAdjList()
{
    vector<vector<int>>adj(vertex.size(), vector<int>());//Список смежности
    for (int i = 0; i < edges.size(); i++)
    {
        adj[edges[i].a].push_back(edges[i].b);//Граф ориентированный
    }
    return adj;
}

void TGraph::DFS(const string& src)
{
    cout << "----------------------------------DFS-------------------------------------\n";
    int s = getIndexVertex(src);//индекс населленого пункта
    if (s == -1)
    {
        cout << "Error src Punkt\n";
        return;
    }
    vector<vector<int>>adj = toAdjList();
    //Реализуем обход в глубину
    vector<bool> visited(vertex.size(), false);
    stack<int> stack;//Используем итеративный что бы обойти
    //Вставим стартвовую вершину
    stack.push(s);
    cout << "\n\n";
    while (!stack.empty())
    {
        int s = stack.top();
        stack.pop();
        if (!visited[s])
        {
            cout << "(**" << vertex[s].getName() << "**)" << "->";
            visited[s] = true;
        }
        for (auto i : adj[s])
            if (!visited[i])
                stack.push(i);
    }
    cout << "\n\n";
}

void TGraph::AlgorithmFord(const string& src, const string& to)
{
    int INF = INT_MAX;
    vector<int> d(vertex.size(), INF);
    int start = getIndexVertex(src);
    int end = getIndexVertex(to);
    if (start == -1 || end == -1)
    {
        cout << "Error incorrect one is two punkt or both\n";
        return;//Если нет таких пунктов
    }
    d[start] = 0;
    vector<int> p(vertex.size(), -1);
    for (;;) {
        bool any = false;
        for (int j = 0; j < edges.size(); ++j)
            if (d[edges[j].a] < INF)
                if (d[edges[j].b] > d[edges[j].a] + edges[j].wieght) {
                    d[edges[j].b] = d[edges[j].a] + edges[j].wieght;
                    p[edges[j].b] = edges[j].a;
                    any = true;
                }
        if (!any)  break;
    }

    if (d[end] == INF)
        cout << "No path from (" << vertex[start].getName() << ") to (" << vertex[end].getName() << ").";
    else {
        vector<int> path;//Путь
        //Вернемся обратно
        for (int cur = end; cur != -1; cur = p[cur])
            path.push_back(cur);
        reverse(path.begin(), path.end());

        cout << "Path from (" << vertex[start].getName() << ") to (" << vertex[end].getName() << "): \n\n";
        for (size_t i = 0; i < path.size(); ++i)
            cout << "( " << vertex[path[i]].getName() << " )-->";
        cout << endl << endl;
        cout << "Summary lenght way is : " << d[end] << endl;
    }
}

void TGraph::PrintGraf()
{
    vector<vector<int>>adjList = toAdjList();
    for (int i = 0; i < adjList.size(); i++)
    {
        cout << "(" << vertex[i] << "  )-->";
        for (auto it : adjList[i])
        {
            cout << "[ " << vertex[it] << " way lenght: " << getLenghWays(i, it) << " ]  ";
        }
        cout << endl;
    }
}
