/*На одній з вулиць містечка будинки класифіковано за трьома
типами: перший – звичайні житлові споруди, другий – промислові
споруди, а третій – міські заклади (лікарні, школи тощо). 

+У результаті вулиця схематично зображена набором літер, кожна з яких визначає
тип будинку. У процесі збору інформації про місто була створена
матриця – таблиця, в якій кожен стовпчик і рядок відповідають
одному з типів будівель. 
+ Відповідно клітинка такої таблиці визначає,
чи розташовані на даній вулиці міста поруч будівлі заданого типу.
Матриця симетрична. 


Визначити, скільки існує способів взаємного
розташування будинків даних типів між собою за заданою матрицею
для заданої кількості будинків на вулиці, тобто кількість можливих
наборів літер заданої довжини, що відповідають заданій матриці.*/
#include <vector>
#include </home/jukh/PycharmProjects/ALaSD/include.h>
enum Types
{
    Living_Building, Industrial_Building, Municipal_Building
};

enum Sides
{
    Left, Right  
};


class Street
{
public:
    vector<vector<string>> buildings; // двомірний тому що будинки з двох сторін 
    
    bool matrix[3][3];
    vector<vector<string>> m1;
    string set[3] = {"ЖС", "ПР", "МЗ"};
    Street() : buildings(2)
    {
        
    }
    void add_building(string building_type, int side); // якщо 0 то ліва сторона
    void form_matrix();
    void final_result(size_t amount_of_buildings);
    
private:
    size_t counter_of_ifs = 0;
    void get_combinations(vector<string> prefix, int n, int k, bool is_start, vector<bool> counters);
};


void Street::get_combinations(vector<string> prefix, int n, int k, bool is_start, vector<bool> counters)
{
    if(k == 0)
    {
        
        bool s = true;
        for (size_t i = 0; i < m1.size(); i++)
        {
            if(counters[i] == false) 
                s = false;
        }
        if(s)
        {
            for (size_t i = 0; i < prefix.size(); i++)
            {
                cout << prefix[i] << " ";
            }
            cout << endl;
        }
        
        return;
    }



   
    for (size_t i = 0; i < n; i++) 
    {
        bool is_true = false;
        vector<string> new_prefix; // {ЖС, ПР, ЖС, МЗ}
        new_prefix = prefix; // set[i] - будинок котрий ми будемо додавати, prefix - ті що вже додані
        new_prefix.push_back(set[i]);
        
        for (size_t j = 0; j < new_prefix.size() - 1; j++) // -1 для того щоб не враховувати set[i]
        {
            for (size_t k = 0; k < m1.size(); k++)
            {
                if(new_prefix[j] + new_prefix[j+1] == m1[k][0] || new_prefix[j] + new_prefix[j+1] == m1[k][1]) // якщо знайшли потрібне поєднання символів
                {
                    is_true = true;
                    counters[k] = true;
                    break;
                }
            }
            // Обробка ситуацій де будинки стоять поруч, проте не мають
            if(new_prefix[j] == "ЖС" ) 
            {
                if(new_prefix[j+1] == "ЖС")
                {
                    if(!matrix[Living_Building][Living_Building] == true)
                    {
                        is_true = false;
                        break;
                    }
                }
                else if(new_prefix[j+1] == "ПР")
                {
                    if(!matrix[Living_Building][Industrial_Building] == true)
                    {
                        is_true = false;
                        // counters.pop_back();
                        break;
                    }    
                }
                else if(new_prefix[j+1] == "МЗ")
                {
                    if(!matrix[Living_Building][Municipal_Building] == true)
                    {
                        is_true = false;
                        // counters.pop_back();
                        break;
                    }
                }
            }
            else if(new_prefix[j] == "ПР")
            {
                if(new_prefix[j+1] == "ЖС")
                {
                    if(!matrix[Industrial_Building][Living_Building] == true)
                    {
                        is_true = false;
                        // counters.pop_back();
                        break;
                    }
                }
                else if(new_prefix[j+1] == "ПР")
                {
                    if(!matrix[Industrial_Building][Industrial_Building] == true)
                    {
                        is_true = false;
                        // counters.pop_back();
                        break;
                    }
                    
                }
                else if(new_prefix[j+1] == "МЗ")
                {
                    if(!matrix[Industrial_Building][Municipal_Building] == true)
                    {
                        is_true = false;
                        // counters.pop_back();
                        break;
                    }
                    
                }
            }
            else if(new_prefix[j] == "МЗ")
            {
                if(new_prefix[j+1] == "ЖС")
                {
                    if(!matrix[Municipal_Building][Living_Building] == true)
                    {
                        is_true = false;
                        // counters.pop_back();
                        break;
                    }
                    
                }
                else if(new_prefix[j+1] == "ПР")
                {
                    if(!matrix[Municipal_Building][Industrial_Building] == true)
                    {
                        is_true = false;
                        // counters.pop_back();
                        break;
                    }
                }
                else if(new_prefix[j+1] == "МЗ")
                {
                    if(!matrix[Municipal_Building][Municipal_Building] == true)
                    {
                        is_true = false;
                        // counters.pop_back();
                        break;
                    }
                    
                }
            }
        }


        if(is_true || is_start) // робимо нові строки тільки з тих, що мають хоча б одну виконану умову
            get_combinations(new_prefix, n, k-1, false, counters);

        for (size_t k = 0; k < counters.size(); k++)
        {
            counters[k] = false;
        }
        
        
    }
    
}

void Street::final_result(size_t amount_of_buildings)
{
    vector<bool> counters;
    counters.resize(m1.size());
    for (size_t i = 0; i < m1.size(); i++)
    {
        counters[i] = false;
    }
    vector<string> v1;
    get_combinations(v1, 3, amount_of_buildings, true, counters); // 3 - кількість типів будівель
}



void Street::add_building(string building_type, int side)
{
    buildings[side].push_back(building_type);
}
void Street::form_matrix() 
{
    m1.resize(6);
    for (size_t i = 0; i < m1.size(); i++)
    {
        m1[i].resize(2);
    }
    
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            matrix[i][j] = false;
        }
    }
    
    for (size_t i = 0; i < buildings.size(); i++)
    {
        for (size_t j = 0; j < buildings[i].size()-1; j++)
        {
            // m1 = {{"ЖСПР", "ПРЖС"}, {ЖСМЗ, МЗЖС}, {ПРМЗ, МЗПР}, {МЗМЗ, МЗМЗ}} size = counter_of_ifs
            static int ctr = 0;
            bool is_found = false;
            for(size_t k = 0; k<m1.size(); k++) // шукаємо співпадіння у масиві строк
            {
                if(buildings[i][j] + buildings[i][j+1] == m1[k][0] || buildings[i][j+1] + buildings[i][j] == m1[k][0])
                {
                    is_found = true;
                }
            }
            if(!is_found)
            {
                m1[ctr][0] = buildings[i][j] + buildings[i][j+1]; // ЖСПР 
                m1[ctr][1] = buildings[i][j+1] + buildings[i][j]; // ПРЖС
                ctr++;
            }
            if(buildings[i][j] == "ЖС")
            {
                if(buildings[i][j+1] == "ЖС")
                {
                    matrix[Living_Building][Living_Building] = true;
                }
                else if(buildings[i][j+1] == "ПР")
                {
                    matrix[Living_Building][Industrial_Building] = true;
                    matrix[Industrial_Building][Living_Building] = true;
                }
                else if(buildings[i][j+1] == "МЗ")
                {
                    matrix[Living_Building][Municipal_Building] = true;
                    matrix[Municipal_Building][Living_Building] = true;
                }
                
            }
            else if(buildings[i][j] == "ПР")
            {
                if(buildings[i][j+1] == "ПР")
                {
                    matrix[Industrial_Building][Industrial_Building] = true;
                }
                else if(buildings[i][j+1] == "МЗ")
                {
                    matrix[Industrial_Building][Municipal_Building] = true;
                    matrix[Municipal_Building][Industrial_Building] = true;
                }
                else if(buildings[i][j+1] == "ЖС")
                {
                    matrix[Living_Building][Industrial_Building] = true;
                    matrix[Industrial_Building][Living_Building] = true;
                }
                
            }
            else if(buildings[i][j] == "МЗ")
            {
                if(buildings[i][j+1] == "МЗ")
                {
                    matrix[Municipal_Building][Municipal_Building] = true;
                }
                else if(buildings[i][j+1] == "ПР")
                {
                    matrix[Municipal_Building][Industrial_Building] = true;
                    matrix[Industrial_Building][Municipal_Building] = true;
                }
                else if(buildings[i][j+1] == "ЖС")
                {
                    matrix[Living_Building][Municipal_Building] = true;
                    matrix[Municipal_Building][Living_Building] = true;
                }
                
            }
        }
        
    }
    for (size_t i = 0; i < m1.size(); i++)
    {
        if(m1[i][0] == "")
        {
            m1.erase(m1.begin() + i);
            i--;
        }
    }
    
    
    
    

    
}



int main(int argc, char const *argv[])
{
    Street s1;
    s1.add_building("ЖС", Left);
    s1.add_building("МЗ", Left);
    s1.add_building("ПР", Left);
    s1.add_building("ЖС", Left);
    s1.add_building("ЖС", Right);
    s1.add_building("ПР", Right);
    s1.add_building("МЗ", Right);
    s1.add_building("МЗ", Right);
    s1.form_matrix();

    s1.final_result(7);
    return 0;
}
