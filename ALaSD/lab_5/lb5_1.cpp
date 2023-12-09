


#include <map>
#include <iterator>
#include <vector>
#include "Graph.h"
#include "lb5_1.h"


bool erase_edges(vector<vector<int>> v, vector<int> boat)
{
    for (vector<vector<int>>::iterator j = v.begin(); j != v.end(); )
    { //видаляємо у масиві всі ребра цих двох предметів
        if((*j)[0] == boat[0] || (*j)[1] == boat[0] || 
        (*j)[0] == boat[1] || (*j)[1] == boat[1])
        {
            v.erase(j);
        }
        else
        {
            j++;
        }
    }
    if(v.size() == 0) return true; // якщо на березі не залишиться жодної небезпечної пари
    else return false;
}



/*
1)-> Козел, собака (собака)
1)<- Козел

2)-> Козел, капуста (собака, капуста)
2)<- Козел

3)-> Вовк, вовк (капуста, вовк, вовк)
3)<- Собака

4)-> Собака, козел (собака, козел, капуста, вовк, вовк)

1)Беремо 2 тварини з берега 1
Поки на березі 1 є якісь тварини:
    Якщо на березі 1 стоїть 2 тварини, і човен пустий:
        Беремо обох

    2)Треба перевіряти берег 2 на те, якщо висадити обидві тварини з човна, чи буде на березі 2 неправильна пара?
    Якщо так, то висаджувати тварину без конфліктів, і пробувати привезти іншу на берег 1. 
        Якщо тварини без конфліктів немає, спробувати висадити обидві, і забрати ту, котра заважала
        Якщо тварини без конфліктів немає, а спроба висадити обох з човна в будь-якому випадку невдала, повертатись до попередньої ітерації, та шукати інші варіанти розподілення тварин
    Якщо ні, висаджувати обох, повертатись на минулий берег.
    
    3)Якщо тварина у човні одна:
        Якщо тварина на березі один одна:
            Забираємо тварину з берега 1
            Завершення програми
            
        4)Перевіряти, якщо висадити цю тварину на березі 1 і забрати двох інших, чи буде неправильна пара на березі 1? 
        Якщо так
        Забираємо з берега 1 одну тварину, повертаємось на другий пункт

        Якщо ні 
        Висаджуємо тварину, беремо пару, котра заважала, повертаємось на другий пункт

*/
class Task2
{
public:
    Graph g;
    Task2(int num)
    {
        animals.insert(make_pair(0, "Козел"));
        animals.insert(make_pair(1, "Вовк1"));
        animals.insert(make_pair(2, "Вовк2"));
        animals.insert(make_pair(3, "Собака"));
        animals.insert(make_pair(4, "Капуста"));
        this->num = num;
        this->matrix = new bool *[num]{
            new bool[num]{0, 1, 1, 1, 1},
            new bool[num]{1, 0, 0, 1, 0},
            new bool[num]{1, 0, 0, 1, 0},
            new bool[num]{1, 1, 1, 0, 0},
            new bool[num]{1, 0, 0, 0, 0},
        };
        g = Graph(5, matrix);
        vertex = g.DFS();
    }
    map<int, string> animals;
    size_t counter = 0;
    size_t num;
    bool **matrix;
    vector<int> vertex;
    vector<vector<int>> bad_pairs;

    void control_start();

private:
    bool check_coast(vector<int> coast, vector<int> boat_to_check);
    void take_from_one_send_to_another(vector<int> *coast_from, vector<int> *coast_to, vector<int> *boat, int coast_id);
    void form_pairs();
    void send_and_take(vector<int> *coast, vector<int> id_to_take, vector<int> id_to_leave, vector<int> *boat, int coast_id);
    void leave_animals_on_coast(vector<int> *coast, vector<int> *boat, int index, int coast_id);
    vector<int> take_animals_from_coast(vector<int> coast, vector<int> animals_to_take);
};

void Task2::form_pairs()
{
    for (int i = 0; i < num; i++) // Записуємо всі небезпечні пари
    {
        for (int j = 0; j < num; j++)
        {
            if(matrix[i][j] == 1)
            {
                vector<int> tmp = {i, j};
                bad_pairs.push_back(tmp);
            }
        }
    }
}


bool Task2::check_coast(vector<int> coast, vector<int> boat_to_check)
{
    for (size_t i = 0; i < boat_to_check.size(); i++)
    {
        coast.push_back(boat_to_check[i]); // висаджуємо тварин(у)
    }
    //перевіряємо всі пари тварин на небезпечну пару
    for (size_t i = 0; i < coast.size(); i++)
    {
        for (size_t j = i+1; j < coast.size(); j++)
        {
            vector<int> tmp = {coast[i], coast[j]};
            for (size_t k = 0; k < bad_pairs.size(); k++)
            {
                if(bad_pairs[k] == tmp)
                {
                    return false;
                }
            }
        }
    }
    return true;

}

void Task2::take_from_one_send_to_another(vector<int> *coast_from, vector<int> *coast_to, vector<int> *boat, int coast_id)
{
    for (size_t i = 0; i < boat->size(); i++)
    {
        for (size_t j = 0; j < coast_from->size(); j++)
        {
            if((*coast_from)[j] == (*boat)[i])
            {
                cout << counter << " ітерація: Забрали " << animals[(*boat)[i]] << " з берега " << coast_id << endl;
                coast_from->erase(coast_from->begin() + j);
            }
        }
        
    }
    if(coast_id == 1)
    {
        coast_id = 2;
    }
    else
        coast_id = 1;
    for (size_t i = 0; i < boat->size(); i++)
    {
        cout << counter << " ітерація: Привезли " << animals[(*boat)[i]] << " до берега " << coast_id << endl;
        coast_to->push_back((*boat)[i]);
    }
    boat->clear();
    
}

void Task2::send_and_take(vector<int> *coast, vector<int> id_to_take, vector<int> id_to_leave, vector<int> *boat, int coast_id)
{
    for (size_t i = 0; i < id_to_leave.size(); i++)
    {
        for (size_t j = 0; j < boat->size(); j++)
        {
            if(id_to_leave[i] == (*boat)[j])
            {
                cout << counter << " ітерація: Висадили " << animals[(*boat)[j]] << " на березі " << coast_id << endl;
                coast->push_back((*boat)[j]);// висаджуємо тварину на берег
                boat->erase(boat->begin() + j);
            }
        }
    }
    
    for (size_t i = 0; i < id_to_take.size(); i++)
    {
        for (size_t j = 0; j < coast->size(); j++)
        {
            if(id_to_take[i] == (*coast)[j])
            {
                cout << counter << " ітерація: Забрали " << animals[(*coast)[j]] << " з берега " << coast_id << endl;
                boat->push_back((*coast)[j]); // садимо цю тварину у човен
                *coast->erase(coast->begin() + j);
            }
            
        }
    }
    
    

}

void Task2::leave_animals_on_coast(vector<int> *coast, vector<int> *boat, int index, int coast_id)
{
    cout << counter << " ітерація: Висадили " << animals[(*boat)[index]] << " на березі " << coast_id << endl;
    coast->push_back((*boat)[index]);
    boat->erase(boat->begin() + index);
}

vector<int> Task2::take_animals_from_coast(vector<int> coast, vector<int> animals_to_take)
{
    for (size_t i = 0; i < animals_to_take.size(); i++)
    {
        for (size_t j = 0; j < coast.size();)
        {
            if(coast[j] == animals_to_take[i])
            {
                coast.erase(coast.begin() + j);
                break;
            }
            else
                j++;
        }
    }
    return coast;
}

void Task2::control_start()
{
    form_pairs();
    vector<int> coast_1 = vertex;
    vector<int> coast_2;
    vector<int> boat;


    
    

    while(!coast_1.empty())
    {
        counter ++;
        if(boat.empty() || boat.size() == 2)
        {
            if(boat.empty())
            {
                for (size_t i = 0; i < bad_pairs.size(); i++) // забираємо двох тварин з берега 1
                {
                    boat = bad_pairs[i];
                    if(erase_edges(bad_pairs, boat) == true) // якщо знайшли потрібну пару
                    {
                        cout << counter << " ітерація: Забрали " << animals[boat[0]] << " "<< animals[boat[1]]
                        << " з берега 1" << endl;
                        coast_1 = take_animals_from_coast(coast_1, boat);
                        break;
                    }
                }
            }

            
            if(check_coast(coast_2, boat)) // чи можемо висадити обох?
            {
                for (size_t i = 0; i < boat.size(); i++)
                {
                    leave_animals_on_coast(&coast_2, &boat, i, 2);

                }
                continue;
            }
            else // чи можна висадити одну без конфліктів?
            {
                bool is_found = false;
                for (size_t i = 0; i < boat.size(); i++)
                {
                    vector<int> boat_tmp = {boat[i]};
                    if(check_coast(coast_2, boat_tmp)) // знайшли тварину, котру можна було б висадити на березі без перешкод
                    {
                        leave_animals_on_coast(&coast_2, &boat, i, 2);

                        is_found = true;
                        break;
                    }
                }
                if(is_found) // знайшли тварину, котру можна було б висадити на березі без перешкод
                    continue;

                else // пробуємо висадити обох, і забрати одну
                {
                    bool is_found = false;
                    for (size_t i = 0; i < boat.size(); i++)
                    {
                        // vector<int> boat_tmp = {boat[i]};
                        vector<int> coast_tmp = coast_2;
                        for (size_t j = 0; j < coast_tmp.size(); j++)
                        {
                            coast_tmp.erase(coast_tmp.begin() + j); // забираємо тварину з берега
                            if(check_coast(coast_tmp, boat)) // чи буде небезпечна пара якщо забрати цю тварину, і висадити обох з човна
                            {
                                vector<int> to_leave = boat;
                                vector<int> to_take = {coast_2[j]};
                                send_and_take(&coast_2, to_take, to_leave, &boat, 2);
                                
                                is_found = true;
                                break;
                            }
                            else
                            {
                                coast_tmp = coast_2;
                            }
                        }
                        if(is_found)
                            break;
                    }
                    if(is_found)
                    {
                        continue;
                    }
                    else // пробуємо висадити одну, і забрати одну
                    {
                        for (size_t i = 0; i < boat.size(); i++)
                        {
                            vector<int> boat_tmp = {boat[i]};
                            vector<int> coast_tmp = coast_2;
                            for (size_t j = 0; j < coast_tmp.size(); j++)
                            {
                                coast_tmp.erase(coast_tmp.begin() + j); // забираємо тварину з берега
                                if(check_coast(coast_tmp, boat_tmp)) // чи буде небезпечна пара якщо забрати цю тварину, і висадити обох з човна
                                {
                                    vector<int> to_leave = boat;
                                    vector<int> to_take = {coast_2[j]};
                                    send_and_take(&coast_2, to_take, to_leave, &boat, 2);
                                    
                                    is_found = true;
                                    break;
                                }
                                else
                                {
                                    coast_tmp = coast_2;
                                }
                            }
                        }
                    }
                }
            }
        }
        else if(boat.size() == 1)
        {
            cout << "У човні зараз знаходиться: " << animals[boat[0]] << endl;
            bool is_found = false;
            for (size_t i = 0; i < coast_1.size(); i++) // чи можна висадити цю тварину і забрати двох інших?
            {
                vector<int> coast_tmp = coast_1;
                for (size_t j = i+1; j < coast_1.size(); j++)
                {
                    coast_tmp.erase(coast_tmp.begin() + j);
                    coast_tmp.erase(coast_tmp.begin() + i);
                    if(check_coast(coast_tmp, boat))
                    {
                        vector<int> to_leave = {boat[0]};
                        vector<int> to_take = {coast_1[i], coast_1[j]};
                        send_and_take(&coast_1, to_take, to_leave, &boat, 1);
                        
                        is_found = true;
                        break;
                    }
                    else
                    {
                        coast_tmp = coast_1;
                    }
                }
                if(is_found)
                    break;
            }
            if(is_found)
            {
                continue;
            }
            else
            { // пробуємо забирати тварину з берега 1 і везти їх обох на берег 2
                for (size_t i = 0; i < coast_1.size(); i++)
                {
                    vector<int> boat_tmp = boat;
                    boat_tmp.push_back(coast_1[i]);
                    if(check_coast(coast_2, boat_tmp) || coast_1.size() == 1)
                    {
                        boat = boat_tmp;
                        take_from_one_send_to_another(&coast_1, &coast_2, &boat, 1);
                        boat.clear();
                        is_found = true;
                        break;
                    }   
                    else
                    {
                        is_found = false;
                        for (size_t j = 0; j < boat_tmp.size(); j++) // пробуємо забрати одну тварину, і одну висадити
                        {
                            vector<int> boat_tmp_1 = {boat_tmp[j]};
                            if(check_coast(coast_2, boat_tmp_1))
                            {
                                boat.push_back(boat_tmp_1[0]);
                                take_from_one_send_to_another(&coast_1, &coast_2, &boat, 1);
                                
                                is_found = true;
                                break;
                            }
                            
                        }
                        if(is_found)
                            break;
                        boat_tmp = boat;
                    }
                }
                if(is_found)
                {
                    continue;
                }
            }   
        }
    }
    bad_pairs.clear();
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
    size_t num= 7;
    bool **matrix_task1 = new bool *[num] {
    new bool[num]{0, 0 , 0, 0, 0, 0, 0},
    new bool[num]{0, 0 , 0, 1, 1, 1, 0},
    new bool[num]{0, 0 , 0, 1, 0, 1, 1},
    new bool[num]{0, 1 , 1, 0, 0, 0, 1},
    new bool[num]{0, 1 , 0, 0, 0, 1, 1},
    new bool[num]{0, 1 , 1, 0, 1, 0, 0},
    new bool[num]{0, 0 , 1, 1, 1, 0, 0},
    };
    Graph g1(num, matrix_task1);
    cout << "*************Перше завдання: ******************" << endl;
    g1.DFS();
    num = 5;


    
    cout << "************Друге завдання вирішення: ***************" << endl;
    Task2 t2(5);
    t2.control_start();

    num = 15;
    bool **maze = new bool *[num]{
    new bool[num]{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //0
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
    Graph maze_graph(num, maze);
    vector<vector<int>> v = maze_graph.BFS();
    cout << "\n\n\nВихід з лабіринту лежить за шляхом: ";
    for (size_t i = 0; i < v[14].size(); i++)
    {
        cout << v[14][i];
        if(i%2 != 0 && i != v[14].size()-1)
        {
            cout << ", ";
        }
        else if(i != v[14].size()-1)
        {
            cout << "-";
        }
    }
    cout << endl;

    return 0;
}
