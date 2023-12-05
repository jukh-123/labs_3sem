




#include <vector>
#include "Graph.h"

void task1(bool **matrix, vector<vector <int>> v, size_t num)
{
    bool **adj_matr = new bool *[num]{
    new bool[num]{0, 1, 1, 1, 1},
    new bool[num]{1, 0, 0, 1, 0},
    new bool[num]{1, 0, 0, 1, 0},
    new bool[num]{1, 1, 1, 0, 0},
    new bool[num]{1, 0, 0, 0, 0},
    };
    bool **matrix_copy = new bool*[num];
    for (size_t i = 0; i < num; i++)
    {
        matrix_copy[i] = new bool[num];
        for (size_t j = 0; j < num; j++)
        {
            matrix_copy[i][j] = matrix[i][j];
        }
        
    }

    
    vector<int> boat;
    vector<vector<int>> v_copy = v;
    for (size_t i = 1; i < v.size(); i++) // З першого тому що у індексі 0 лежить {0, 0}
    {
        boat = v[i]; // намагаємось забрати першу пару
        bool to_break = false;
        // for (size_t j = 0; j < v_copy.size(); j++) // видаляємо всі зв'язки
        // {
        //     //видаляємо всі ребра цієї пари
        //     if(v_copy[j][0] == boat[0] || v_copy[j][1] == boat[0] || v_copy[j][0] == boat[1] || v_copy[j][1] == boat[1])
        //     {
        //         v_copy.erase(v_copy.begin() + j);
        //         j--;
        //     }
        // }
        //якщо після видалення ребер залишаються елементи, котрі не можна залишати разом
        for (size_t j = 0; j < num; j++)
        { //видаляємо у матриці всі зв'язки
            matrix_copy[boat[0]][j] = 0;
            matrix_copy[j][boat[0]] = 0;
            matrix_copy[boat[1]][j] = 0;
            matrix_copy[j][boat[1]] = 0;
        }

        for (size_t j = 0; j < num; j++)
        {
            for (size_t k = 0; k < num; k++)
            {
                if(matrix_copy[j][k] == true)
                {
                    to_break = true;
                }
                matrix_copy[j][k] = matrix[j][k];
            }
        }
        if(!to_break)
        {
            cout << boat[0] << ' ' << boat[1] << endl;
            v.erase(v.begin() + boat[1]);
            for (size_t j = 0; j < num; j++)
            { //видаляємо у матриці всі зв'язки
                matrix_copy[boat[0]][j] = 0;
                matrix_copy[j][boat[0]] = 0;
                matrix_copy[boat[1]][j] = 0;
                matrix_copy[j][boat[1]] = 0;
            }
            i = 0;
        }

        


        // for(size_t j = 0; j < num; j++)
        // {
        //     matrix[i][j] = 0;
        // }
    }
    
    
    
}

int main(int argc, char const *argv[])
{
    /*new bool[num]{0, 1 , 1, 0, 1, 0, 0},
    new bool[num]{1, 0 , 0, 1, 1, 1, 0},
    new bool[num]{1, 0 , 0, 1, 0, 1, 1},
    new bool[num]{0, 1 , 1, 0, 0, 0, 1},
    new bool[num]{1, 1 , 0, 0, 0, 1, 1},
    new bool[num]{0, 1 , 1, 0, 1, 0, 0},
    new bool[num]{0, 0 , 1, 1, 1, 0, 0},*/

    /*new bool[num]{0, 1 , 1, 0, 1, 0, 0},
    new bool[num]{1, 0 , 0, 1, 1, 1, 0},
    new bool[num]{1, 0 , 0, 1, 0, 1, 1},
    new bool[num]{0, 1 , 1, 0, 0, 0, 1},
    new bool[num]{1, 1 , 0, 0, 0, 1, 1},
    new bool[num]{0, 1 , 1, 0, 1, 0, 0},
    new bool[num]{0, 0 , 1, 1, 1, 0, 0},*/
    size_t num= 5;
    bool **adj_matr = new bool *[num]{
    new bool[num]{0, 1, 1, 1, 1},
    new bool[num]{1, 0, 0, 1, 0},
    new bool[num]{1, 0, 0, 1, 0},
    new bool[num]{1, 1, 1, 0, 0},
    new bool[num]{1, 0, 0, 0, 0},
    };
    num = 15;
    bool **maze = new bool *[num]{
    new bool[num]{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, //0
    new bool[num]{1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //1
    new bool[num]{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //2
    new bool[num]{0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //3
    new bool[num]{0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}, //4
    new bool[num]{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //5
    new bool[num]{0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0}, //6
    new bool[num]{0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0}, //7
    new bool[num]{0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0}, //8
    new bool[num]{0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0}, //9
    new bool[num]{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0}, //10
    new bool[num]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, //11
    new bool[num]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1}, //12
    new bool[num]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0}, //13
    new bool[num]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, //14
    };
    Graph g1(5, adj_matr);
    Graph maze_graph(num, maze);
    // g2.DFS();
    vector<vector<int>> v = maze_graph.BFS();
    cout << "Виход з лабіринту лежить за шляхом: ";
    for (size_t i = 0; i < v[13].size(); i++)
    {
        cout << v[13][i] <<" ";
    }
    
    
    // task1(adj_matr, g1.BFS(), num);
    return 0;
}
