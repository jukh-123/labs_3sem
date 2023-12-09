/*Задача 1
Мапа визначає авіасполучення між містами Північної
Америки. Кожний переліт з однієї точки на мапі в іншу має деяку
мінімальну вартість, при чому зворотній рейс може коштувати іншу
суму. Мандрівник хоче визначити авіапереліт між заданими містами, який має мінімальну вартість, розглядаючи зокрема і варіанти з
пересадками. При цьому мандрівник має дисконтну програму з
деякими авіаперевізниками, за якою ціна на деякі рейси може бути для
нього знижена на деяку постійну суму (тобто вартість деяких рейсів
може виявитися для нього прибутковою, в такому разі сума
накопичується на окремому його рахунку).*/
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include </home/jukh/PycharmProjects/ALaSD/include.h>
map<string, unsigned short int> cities;
unsigned short int city_id = 0;
// class City
// {
// public:
//     string city_name = "";
//     unsigned short int city_id;
//     string country = "";
//     City(string city_name, string country)
//     {
//         this->city_name = city_name;
//         this->city_id = city_id++;
//         this->country = country;
//     }
// };

/*Задача 2:
А. Компанія забезпечує інтернет-підключення користувачів за
допомогою оптичного кабелю. Для підключення нових абонентів було
сформовано граф, який представляє можливі траси оптичного
з’єднання. На графі ребрами представлені кабельні канали, а
вершинами – місця, де є можливість вибору подальшого напрямку
прокладення кабелю. Визначити трасу, яка з’єднає дві задані точки на
мапі і буде мати при цьому найменшу довжину.*/

/*Задача 3:
А. Враховуючи, що граф, описаний у попередньому завданні,
представляє можливості з’єднання району з існуючими
магістральними лініями, визначити всі найкоротші шляхи всередині
графу.*/

vector<vector<unsigned short int>> fill_prices(vector<vector<unsigned short int>> routes)
{
    routes[cities["New York"]][cities["California"]] = 100;
    routes[cities["California"]][cities["New York"]] = 120;

    routes[cities["Houston"]][cities["Washington"]] = 150;
    routes[cities["Washington"]][cities["Houston"]] = 130;

    routes[cities["Toronto"]][cities["Montreal"]] = 10;
    routes[cities["Montreal"]][cities["Toronto"]] = 7;

    routes[cities["Ottawa"]][cities["Montreal"]] = 12;
    routes[cities["Montreal"]][cities["Ottawa"]] = 10;

    routes[cities["Mexico City"]][cities["California"]] = 25;
    routes[cities["California"]][cities["Mexico City"]] = 29;

    routes[cities["Guadalajara"]][cities["Miami"]] = 34;
    routes[cities["Miami"]][cities["Guadalajara"]] = 55;

    routes[cities["New York"]][cities["Washington"]] = 15;
    routes[cities["Washington"]][cities["New York"]] = 15;

    routes[cities["Toronto"]][cities["New York"]] = 12;
    routes[cities["New York"]][cities["Toronto"]] = 12;

    routes[cities["Miami"]][cities["Califronia"]] = 25;
    routes[cities["Califronia"]][cities["Miami"]] = 25;

    routes[cities["Washington"]][cities["Houston"]] = 31;
    routes[cities["Houston"]][cities["Washington"]] = 29;

    return routes;
}

void insert_cities()
{
    cities.insert(make_pair( "New York", city_id++));
    cities.insert(make_pair( "Califronia", city_id++));
    cities.insert(make_pair( "Houston", city_id++));
    cities.insert(make_pair( "Washington", city_id++));
    cities.insert(make_pair( "Toronto", city_id++));
    cities.insert(make_pair( "Montreal", city_id++));
    cities.insert(make_pair( "Ottawa", city_id++));
    cities.insert(make_pair( "Mexico City", city_id++));
    cities.insert(make_pair( "Guadalajara", city_id++));
    cities.insert(make_pair( "Miami", city_id++));
}

int main(int argc, char const *argv[])
{
    insert_cities();
    vector<vector<unsigned short int>> routes(city_id + 1);
    for (size_t i = 0; i < city_id + 1; i++)
    {
        routes[i].resize(city_id + 1);
    }
    routes = fill_prices(routes);

    for (size_t i = 0; i < city_id + 1; i++)
    {
        for (size_t j = 0; j < routes[i].size(); j++)
        {
            cout << routes[i][j] << " ";
        }
        cout << endl;
        
    }
    


    
    return 0;
}
