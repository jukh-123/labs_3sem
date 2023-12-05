





#include <vector>
#include <algorithm>
#include </home/jukh/PycharmProjects/ALaSD/include.h>

class Application
{
public:
    size_t profit = 0;
    size_t date_of_start;
    size_t date_of_finish;
    Application( size_t profit, size_t date_of_start, size_t date_of_finish)
    {
        this->profit = profit;
        this->date_of_start = date_of_start;
        this->date_of_finish = date_of_finish;
    }

};

bool sort_by_profit(const Application &a, const Application &b)
{
    if(a.profit / (a.date_of_finish - a.date_of_start) == b.profit / (a.date_of_finish - a.date_of_start))
    {
        size_t time_required_a = a.date_of_finish - a.date_of_start;
        size_t time_required_b = b.date_of_finish - b.date_of_start;

        if(time_required_a > time_required_b)
        {
            return true;
        }
        else
            return false;
    }
    return (a.profit / (a.date_of_finish - a.date_of_start) < b.profit / (a.date_of_finish - a.date_of_start));
}


// беремо всі доступні проекти і порівнюємо їх між собою, беремо найвигідніший у перерахунку на місяць з доступних(ті, що лежать поза датами виконання вже обраних)
// якщо є однакові за вигодою, беремо найкоротший
vector<Application> func(vector<Application> arr)
{ 

    vector<Application> result; // результатом будуть найвигідніші проекти, котрі не перетинаються один з одним
    int busy_months[2];
    sort(arr.rbegin(), arr.rend(), sort_by_profit);
    cout << "Відсортований масив: ***" << endl;
    for (size_t i = 0; i < arr.size(); i++)
    {
        cout << arr[i].profit << endl;
    }
    while(arr.size() != 0)
    {
        
        
        result.push_back(arr[0]);

        busy_months[0] = arr[0].date_of_start;
        busy_months[1] = arr[0].date_of_finish;
        
        arr.erase(arr.begin() + 0);
        for (size_t i = 0; i < arr.size(); i++)
        {
            if(arr[i].date_of_finish > busy_months[0] && arr[i].date_of_start < busy_months[1])
            {
                arr.erase(arr.begin() + i);
                i--; // для того щоб почати наступну ітерацію з цього ж індексу, бо після видалення індекси з'їжджають на 1 назад
            }
        }
        
    }
    return result;


    /// Реалізація за допомогою динамічного програмування
    while(arr.size() != 0)
    {
        vector<Application> temp;
        size_t profit_of_inner_projects = 0;

        sort(arr.rbegin(), arr.rend(), sort_by_profit); // знаходимо найвигідніший, якщо декілька з однаковою прибутковістю, віддаємо пріоритет тим, у котрих менше час виконання
        
        result.push_back(arr[0]);

        busy_months[0] = arr[0].date_of_start;
        busy_months[1] = arr[0].date_of_finish;

        arr.erase(arr.begin() + 0);
        for(size_t i = 0; i<arr.size() ; i++) // знаходимо всі елементи дата котрих лежить всередині поточного проекту
        {
            if(arr[i].date_of_finish > busy_months[0] && arr[i].date_of_start < busy_months[1])
            {
                temp.push_back(arr[i]);
                
                profit_of_inner_projects += arr[i].profit; // їх сума більша за профіт поточного проекту?
                
                arr.erase(arr.begin() + i);
                i--; // для того щоб почати наступну ітерацію з цього ж індексу, бо після видалення індекси з'їжджають на 1 назад
            }
        }
        if(profit_of_inner_projects > result.back().profit) //проекти, через котрі неможливо було б взяти поточний проект, перевищують його прибутковість
        {
            temp = func(temp); // масив з проектами, котрі перетинаються з поточним, при цьому не перетинаються між собою
            profit_of_inner_projects = 0;
            for(size_t i=0; i<temp.size(); i++)
            {
                profit_of_inner_projects += temp[i].profit;
            }
            if(profit_of_inner_projects > result.back().profit) //сума проектів, котрі між собою не перетинаються, і лежать у межах поточного проекту більше за поточний проект
            {
                result.pop_back(); // Видаляємо поточний проект так як внутрішні проекти взяти вигідніше
                for(size_t i=0; i<temp.size(); i++)
                {
                    result.push_back(temp[i]);
                }
            }
        }

    }
    
}


int main(int argc, char const *argv[])
{
    Application web_dev(100, 1, 13);
    Application cinema(100, 6, 20); 
    Application shelfs(150, 13, 20); 
    Application cups(120, 3, 6); 
    Application windows(500, 20, 24);
    Application scarf(123, 24, 30);
    Application coat(444, 30, 35);
    Application shoes(1000, 1, 10); 
    vector<Application> pool = {web_dev, cinema, shelfs, cups, windows, scarf, coat, shoes};
    vector<Application> v = func(pool);


    cout << "Найвигідніші проекти згідно з жадібним алгоритмом: " << endl;
    unsigned int total_profit = 0;
    for (size_t i = 0; i < v.size(); i++)
    {
        cout << v[i].profit << endl;
        total_profit+=v[i].profit;
    }
    
    cout << "Загальний прибуток складатиме: " << total_profit << endl;
    
    return 0;
}
