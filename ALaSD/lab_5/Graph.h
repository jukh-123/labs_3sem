




#include <stack>
#include <queue>
#include </home/jukh/PycharmProjects/ALaSD/include.h>

class Graph
{
public:
    size_t number_of_vertex = 0;
    bool **matrix; // матриця суміжності
    Graph(size_t number_of_vertex, bool **matrix);
    Graph(){;}
    ~Graph(){
        ;
    }
    bool is_connected(vector<int> v);
    vector<int> DFS();
    vector<vector<int>> BFS();
};

Graph::Graph(size_t number_of_vertex, bool **matrix)
{
    this->number_of_vertex = number_of_vertex;
    this->matrix = matrix;
}
bool Graph::is_connected(vector<int> v)
{
    if(v.size() == number_of_vertex)
    {
        cout << "Граф є зв'язним" << endl;
        return true;
    }
    else
    {
        cout << "Граф не є зв'язним" << endl;
        return false;
    }
}

vector<vector<int>> Graph::BFS()
{
    queue<int> Queue;
    vector<int> nodes;
    vector<vector<int>> edges;
    edges.resize(number_of_vertex);

    int vertex[number_of_vertex];
    for (size_t i = 0; i < number_of_vertex; i++)
    {
        vertex[i] = 0;
    }
    Queue.push(vertex[0]);
    vector<int> t = {0, 0};
    edges[0] = t;
    while(!Queue.empty())
    {
        unsigned short int node = Queue.front();
        Queue.pop();
        vertex[node] = 2;
        for (int i = 0; i < number_of_vertex; i++)
        {
            if(matrix[node][i] == 1 && vertex[i] == 0)
            {
                if(node != 0)
                    edges[i] = edges[node];

                edges[i].push_back(node);
                edges[i].push_back(i);

                Queue.push(i);
                vertex[i] = 1;
            }
        }
        nodes.push_back(node);
    }
    // for (size_t i = 0; i < nodes.size(); i++)
    // {
    //     cout << "Вершину "<< i << " було досягнуто за шляхом: ";
    //     for(int j = 0; j<edges[i].size(); j++)
    //     {
    //         cout << edges[i][j];
    //         if(j%2 != 0 && j != edges[i].size()-1)
    //         {
    //             cout << ", ";
    //         }
    //         else if(j != edges[i].size()-1)
    //         {
    //             cout << "-";
    //         }
    //     }
    //     cout << endl;
    // }
    return edges;
    
    
}

vector<int> Graph::DFS()
{
    
    vector<int> v;
    vector<vector<int>> edges_vec;
    edges_vec.reserve(number_of_vertex);
    v.reserve(number_of_vertex);


    stack<int> Stack; 
    stack<vector<int>> edges;


    int *vertex = new int [number_of_vertex]; // Зберігання станів вершин графу 0 = не відвідана, 1 = знайдена, 2 = відвідана

    for (size_t i = 0; i < number_of_vertex; i++)
    {
        vertex[i] = 0;
    }

    //ініціалізація першої вершини
    Stack.push(vertex[0]);
    vector<int> temp = {0, 0};
    edges.push(temp);
    temp.clear();

    while (!Stack.empty())
    {
        int node = Stack.top(); //беремо індекс найближчої за індексом вершини (наприклад до 1 найближча 2) і видаляємо її зі стеку
        Stack.pop();
        
        vector<int> tmp = edges.top();//Беремо шлях до цієї вершини і видаляємо його зі стеку
        edges.pop();
        
        
        if(vertex[node] == 2) // якщо ця вершина вже була відвідана
        {
            continue; // починаємо заново - уходимо до попередньої вершини
        }
        vertex[node] = 2; // записуємо що вершина відвідана
        vector<int> arr(2);
        for (int i = number_of_vertex - 1; i >= 0; i--) // цикл у зворотньому порядку тому що стек заповнюється у зворотньому порядку
        {
            if(matrix[node][i] == 1 && vertex[i] != 2) // якщо є ребро, та вершина ще не відвідана
            {
                if(node != i)
                {
                    arr = {node, i};
                    edges.push(arr);
                } // кладемо ребро по котрому ми дійшли до цієї вершини
                Stack.push(i); // кладемо цю вершину у стек
                vertex[i] = 1; // записуємо знайдену вершину
            }
        }
        
        
        edges_vec.push_back(tmp);
        v.push_back(node);
    }
    //якщо 0ва вершина не є зв'язаною з графом????
    is_connected(v);
    
    // for (size_t i = 0; i < v.size(); i++)
    // {
    //     cout << "Вершину " << v[i] << " вперше було досягнуто по ребру: ";
    //     for (size_t j = 0; j < 2; j++)
    //     {
    //         cout << edges_vec[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    
    
    return v;
}