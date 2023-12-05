




/*Для заданого рядка символів визначити послідовність дій з
розбиття рядка на задані частини, що характеризується мінімальними
вимогами до часу виконання дій. Частини, на які необхідно розбити
рядок, задаються порядковими номерами символів, які є межами
частин рядка. Тобто якщо рядок довжиною 10 символів необхідно
розділити на частини після символів 3, 5, то в результаті має бути
сформовано три нові рядка: з першого до третього символу, з
четвертого до п’ятого та з шостого до десятого. 

 Ці розбиття можна виконати в порядку зліва направо 
або справо наліво (у випадку більшої кількості частин таких варіацій стає ще більше).
 Розбиття зліва направо має наступну вартість: 10 (розбиває рядок на 3 та 7
символів) + 7 (розбиває рядок на 2 та 5 символів). Таким чином, в
результаті необхідно визначити послідовність розбиття рядка, що
характеризується мінімальною загальною вартістю за часом, та
вартість такого розбиття.*/
#include <vector>
#include </home/jukh/PycharmProjects/ALaSD/include.h>


/*
    Кожна підзадача - порахувати вартість розбиття нового відрізку, котрий образувався у наслідок попереднього розбиття
    i1 < n1, i2 < n2, ik < nk.
*/

int func(string str, vector<size_t> points)
{
    static int total_cost = 0;
    static int counter_left = 1; // по індексу 0 лежить 0
    static int counter_right = points.size() - 2;
    
    string s_left = "";
    string s_right = "";

    if(counter_left != points.size() - 1 && counter_right != 0)
    {
        int left_1 = counter_left;
        int right_1 = counter_right;
        int cost_1 = strlen(str.c_str()); // для обрахування вартості розбиття підстроки по першому символу
        if(counter_right == counter_left)
        {
            total_cost += cost_1;
            return total_cost;
        }
        int left_cost = 0; // Для обрахування вартості розбиття всієї строки в одному напряму
        int right_cost = 0;

        
        // left_cost_1 += (points[counter_left] - points[counter_left - 1]) + (points.back() - points[counter_left]) + 1;
        for (size_t i = 0; i < strlen(str.c_str()); i++) // ліве розбиття
        {
            if(i == points[left_1] && i !=strlen(str.c_str()) - 1) // розбиваємо строку і рахуємо вартість повного розбиття
            {
                left_cost += (strlen(str.c_str()) - points[left_1-1]) ; 
                left_1 ++;
            }
        
            if(i >= points[counter_left])
                s_left.push_back(str[i]);
        }


        // right_cost_1 += (points[counter_right+1] - points[counter_right]) + points[counter_right] + 1;
        for (int i = strlen(str.c_str()) - 1; i >= 0; i--) // праве розбиття
        { 
            if(i == points[right_1] && i != 0) // розбиваємо строку і рахуємо вартість повного розбиття
            {
                right_cost += points[right_1+1] + 1; // від попередньої точки до поточної + від поточної до початку
                right_1 --;
            }
            if(i <= points[counter_right])
                s_right.push_back(str[i]);
        }


        
        

        if(left_cost < right_cost) // якщо вартість повного лівого виявилась більше за повне праве розбиття
        {
            total_cost += cost_1; //додаємо вартість розбиття по першому елементу
            for (size_t i = counter_left + 1; i < points.size(); i++) // здвигаємо індекси для нової строки
            {
                points[i] -= points[counter_left] ;
            }
            
            points[counter_left] = 0;
            
            counter_left ++;
            cout << "Вигіднішим виявилось ліве розбиття: " << s_left << endl;
            func(s_left, points);
        }
        else 
        {
            total_cost += cost_1;

            counter_right --;
            cout << "Вигіднішим виявилось праве розбиття: " << s_right << endl;
            func(s_right, points);
        }

        
        
        
    }
    return total_cost;
    
}


int main(int argc, char const *argv[])
{
    string str = "qwertyuiopasdfg";
    vector<size_t> points = {0, 3, 6, 10, 12, 14};
    size_t counter = 5;
    vector<string> result;
    string s = "";
    unsigned int cost = 0;
    int f = func(str, points);
    
    cout << "Найдешевше розбиття має вартість " << f << endl;
    
    return 0;
}
