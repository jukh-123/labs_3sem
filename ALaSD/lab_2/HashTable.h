#include <fstream>
#include <vector>
#include <algorithm>
#include </home/jukh/PycharmProjects/ALaSD/include.h>

class Node
{
    public:
        string str;
        int counter = 1;
        Node *next = NULL;
        Node(string str, int count = 1){this->str = str; counter = count;}
        Node(){this->str = "";}
};
struct less_than_key
{
    inline bool operator() (const Node* struct1, const Node* struct2)
    {
        return (struct1->counter < struct2->counter);
    }
};



class HashTable
{
    public:
        
        


        HashTable(){arr.resize(arr_size); }
        void add_element(string str, int count = 1);
        void delete_element(string str);
        void print_element(string str);
        int find_element(string str);
        void find_biggest_element();
        
    private:
        size_t arr_size = 5;
        vector<Node*> arr;
        size_t count_of_elements;
        const float overflow = 0.75;
        
        void is_overflow();
        long long hash_func(string str);
        long int index_func(string str);
};



void HashTable::find_biggest_element()
{
    size_t biggest_num = 0;
    vector<Node*> tmp;
    size_t j = 0;
    Node *ptr;
    for(size_t i = 0; i<arr_size; i++)
    {
        if(arr[i] != NULL)
        {
            ptr = arr[i];
            
            
            while(tmp.size() == 5 && ptr != NULL)
            {
                if(tmp[0]->counter < ptr->counter ) // якщо найменший елемент менший за щось
                {
                    tmp[0] = ptr; // заміняємо елемент і сортуємо масив
                    sort(tmp.begin(), tmp.end(), less_than_key());
                }
                ptr = ptr->next;
            }
            while(tmp.size() != 5 && ptr != NULL) // поповнюємо масив першими п'ятьма входженнями
            {
                tmp.push_back(ptr);
                
                ptr = ptr->next;
            } 
            sort(tmp.begin(), tmp.end(), less_than_key());
        }
    }

    for (size_t i = 0; i < tmp.size(); i++)
    {
        cout << tmp[i]->str << " має " << tmp[i]->counter << " входжень у тексті." << endl;
    }
    
    
    
    
}


void HashTable::is_overflow()
{
    count_of_elements = 0;
    for (size_t i = 0; i < arr_size; i++) //перевірка скільки у масиві не пустих елементів
    {
        if(arr[i] != NULL)
        {
            count_of_elements++;
        }
    }

    
    if((float)count_of_elements / (float)arr_size >= overflow) // якщо не пустих елементів більше 75%, то розширяємо масив удвічі
    {
        
        arr_size *= 2;
        arr.resize(arr_size, NULL);
        vector<string> s; //строки старої таблиці
        vector<int> c; //кількість входжень строк старої таблиці
        for (size_t i = 0; i < arr_size/2; i++) //перезаповнюємо масив з урахуванням нової розмірності
        {
            if(arr[i] != NULL) //якщо по індексу існує зв'язаний список
            {
                Node *ptr = arr[i];
                Node *p1;
                while(ptr != NULL) //видаляємо весь список
                {
                    p1 = ptr->next;
                    s.push_back(ptr->str);
                    c.push_back(ptr->counter);
                    delete ptr;
                    ptr = p1;
                }
                arr[i] = NULL; 

            }
        }
        for(size_t j = 0; j<s.size(); j++) //перезаповнюємо масив з урахуванням нової розмірності
        {
            add_element(s[j], c[j]);
        }
        s.clear();
        c.clear();
    }
}

void HashTable::add_element(string str, int count)
{
    is_overflow();
    
    long int k = index_func(str);

    Node *ptr = new Node(str, count); //count для того щоб при перезаповнені масиву після оверфлоу, можна було зберегти каунтер.
    
    if(arr[k] != NULL) // якщо по індексу вже існує список 
    {
        Node *ptr1 = arr[k];

        while(ptr1 != NULL) //шукаємо потрібний елемент по списку
        {
            if(ptr1->str == str) //якщо знайшли елемент з такою ж строкою, то поповнюємо каунтер і виходимо з функції
            {
                ptr1->counter++;
                return;
            }
            if(ptr1->next == NULL)
            {
                break;
            }
            ptr1 = ptr1->next;
        }
    
        ptr1->next = ptr; // якщо індекс не пустий, але у зв'язаному списку потрібної строки немає
    }
    else //якщо індекс пустий
        arr[k] = ptr;
}

long int HashTable::index_func(string str)
{
    long int index = hash_func(str);
    index = index % arr_size;
    return index;
}

long long HashTable::hash_func(string str)
{

    const int p = 53;
    const int m = 1e9 + 9;
    long long hash_value = 0;
    long long p_pow = 1;
    for (char c : str) 
    {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}
    
int HashTable::find_element(string str)
{
    size_t index = index_func(str);
    Node *ptr = arr[index];
    while(ptr->str != str)
    {
        ptr = ptr->next;
    }
    return ptr->counter;
}