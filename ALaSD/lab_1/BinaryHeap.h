#include<vector>
#include </home/jukh/PycharmProjects/ALaSD/include.h>


class BinaryHeap
{
public:
    vector<Item> arr; //дитина = 2*i+1, батько = (i-1)/2 цілочисельно
    BinaryHeap(){;}
    BinaryHeap(vector<Item> a);
    void add_element(Item it);
    void delete_element(Item it);
    void show_items();
    void heap_sort();
private:
    void check_up();
    void check_down(int n=-1);
};

BinaryHeap::BinaryHeap(vector<Item> a)
{
    for(size_t i=0; i<a.size(); i++)
    {
        arr.push_back(a[i]);
        check_up();
    }
}

void BinaryHeap::heap_sort()
{
    for(int i = arr.size()-1; i>=0; i--)
    {
        swap(arr[i], arr[0]);

        check_down(i); // викликаємо сортировку для всіх елементів окрім останнього
    }
}

void BinaryHeap::show_items()
{

    for (size_t i = 0; i < arr.size(); i++)
    {
        cout << "*************************" << i+1 << " ***************************** " << endl;
        arr[i].print_data();
    }
    
    
}


void BinaryHeap::delete_element(Item it)
{
    
    Item tmp;
    size_t i = 0;
    for(i; i<arr.size(); i++)
    {
        if(arr[i] == it)
        {
            tmp = arr[i];
            break;
        }
    }
    arr[i] = arr[arr.size()-1];
    arr.pop_back();
    check_down();

    cout << "Видалено елемент\n";
    tmp.print_data();
}

void BinaryHeap::check_down(int n)
{
    if(n == -1) n = arr.size();

    for (size_t i = 0; 2*i+1 < n; )
    {
        size_t biggest_child = 2*i+1; // припустимо що найбільша ліва дитина
        if ( biggest_child + 1 < n && 
        arr[biggest_child+1].total_cost > arr[biggest_child].total_cost) // якщо існує ще одна дитина && ліва дитина < правої
        {
            biggest_child++; //заміняємо ліву дитину на праву
        }

        if(arr[i].total_cost >= arr[biggest_child].total_cost)
        {
            return; 
        }
        swap(arr[i], arr[biggest_child]);


        i = biggest_child;
    }
    
}

void BinaryHeap::check_up()
{
    for (size_t i = arr.size()-1; i != 0; i = (i-1)/2)
    {
        if(arr[i].total_cost > arr[(i-1)/2].total_cost)
        {
            swap(arr[i], arr[(i-1)/2]);

        }
        else if(arr[i].total_cost == arr[(i-1)/2].total_cost)
        {
            if(arr[i].item_cost > arr[(i-1)/2].item_cost)
            { 
                swap(arr[i], arr[(i-1)/2]);

            }
        }
        else break;
    }
    
}


void BinaryHeap::add_element(Item it)
{
    arr.push_back(it);
    check_up();
}


