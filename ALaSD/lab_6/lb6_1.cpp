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
map<unsigned short int, string> cities_idx;
unsigned short int city_id = 0;
const int INF = 1e9;

class Route
{
public:
    Route(string start, string end, int price)
    {
        this->start = start;
        this->end = end;
        this->price = price;
    }
    Route(){;}
    string start, end;
    int price;
    
};

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

vector<int> get_cheapest(vector<Route> routes, string to_start)
{
    vector<int> cheapest_prices(city_id, INF);
    vector<int> from(city_id, -1);
    int start = cities[to_start];

    cheapest_prices[start] = 0; // визначаємо ціну до стартового міста як 0

    for (size_t i = 0; i < city_id - 1; i++) // v - 1 ітерацій
    {
        for(auto &[start1, end, price] : routes) // у кожній ітерації розглядаємо всі існуючі шляхи
        { // перевірка на те, що ціна до початку маршруту не є нескінченністю, інакше може бути ситуація коли віднімаємо від нескінченності
            if(cheapest_prices[cities[start1]] != INF && cheapest_prices[cities[end]] > cheapest_prices[cities[start1]] + price)
            { // намагаємось покращити відстань до кожного ребра
                cheapest_prices[cities[end]] = cheapest_prices[cities[start1]] + price; 
                from[cities[end]] = cities[start1]; // у from лежать останній(найоптимальніший) варіант як попасти у місто
            }
        }
    }

    vector<int> path;
    string finish;

    cout << "\n\nМісто призначення: ";
    cin >> finish;
    for (int v = cities[finish]; v != -1; v = from[v])
    { // записуємо як ми прийшли у кожне місто з маршруту востаннє
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    

    cout << "Найдешевший маршрут у " << cities_idx[cities[finish]] << 
    " коштує " << cheapest_prices[cities[finish]] <<
    " по містам: ";
    for (size_t j = 0; j < path.size(); j++)
    {
        cout << cities_idx[path[j]] << " - ";
    }

    

    return cheapest_prices;
}

void insert_cities()
{
    cities.insert(make_pair( "New-York", city_id++));
    cities.insert(make_pair( "California", city_id++));
    cities.insert(make_pair( "Houston", city_id++));
    cities.insert(make_pair( "Washington", city_id++));
    cities.insert(make_pair( "Toronto", city_id++));
    cities.insert(make_pair( "Montreal", city_id++));
    cities.insert(make_pair( "Ottawa", city_id++));
    cities.insert(make_pair( "Mexico-City", city_id++));
    cities.insert(make_pair( "Guadalajara", city_id++));
    cities.insert(make_pair( "Miami", city_id++));
    for (auto &i : cities)
    {
        cities_idx.insert(make_pair(i.second, i.first));
    }
    
}

int main(int argc, char const *argv[])
{
    insert_cities();

    vector<Route> routes(21);
    for (auto &[start, end, price]: routes)
    {
        cin >> start >> end >> price;
    }
    
    string start_city;
    cout << "\n\nПочаткове місто: ";
    cin >> start_city;
    cout << endl;

    cout << "Індекс міста: "<< cities[start_city] << endl;
    const int INF = 1e9;
   
    vector<int> cheapest = get_cheapest(routes, start_city);

    
    
    return 0;
}
