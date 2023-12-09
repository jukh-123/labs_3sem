/*Розробити програмне забезпечення, яке реалізує
використання алгоритму Хаффмана для стискання даних текстового
файлу у вигляді класу. Клас повинен мати методи, які дозволяють
задати файл з даними, виконати стискання даних, визначити
параметри виконаного стискання та зворотне перетворення, записати
результати кодування/декодування в файл.*/

#include <vector>
#include <fstream>
#include <map>
#include </home/jukh/PycharmProjects/ALaSD/include.h>
map<char,vector<bool>> table;
class m_pair
{
public:
    char symbol = '0';
    size_t frequency = 0;
    m_pair *left = NULL, *right = NULL;

    m_pair(){;};
    m_pair(char symbol, size_t frequency)
    {
        this->symbol = symbol;
        this->frequency = frequency;
    }
};

class HuffmanTree
{
public:
    vector<m_pair*> minHeap; // з початку це бінарна купа, потім - дерево з лівим та правим зв'язком

    int add_element(char symb, size_t freq);
    void form_tree();
    void delete_element(int index);
    void print_codes(m_pair* ptr, int arr[], int top);
    void write_bit(int bit);
    void decode();
private:

    m_pair extract_min_elements();
};

void HuffmanTree::decode()
{
    ifstream coded_file("coded.bin", ios::in | ios::binary);
    ofstream encoded_file("encoded.txt");
    m_pair *p = minHeap[0]; // починаємо з гори
    unsigned short int count=0; 
    char byte;
    byte = coded_file.get();
    while(!coded_file.eof())
    {   
        bool b = byte & (1 << (7-count) ) ; // отримуємо значення біту у байті на позиції 7-count
        if (b) 
            p=p->right; 
        else 
            p=p->left;
        if (p->left==NULL && p->right==NULL)  //дійшли до листа (всі букви - листи і всі листи - букви)
        {
            encoded_file << p->symbol;
            p = minHeap[0]; // йдемо знову зверху
        }  
        count++;
        if (count==8) 
        {
            count=0;
            byte = coded_file.get(); // розшифровуємо наступний символ
        }
    }
    coded_file.close();
    encoded_file.close();
}





void HuffmanTree::write_bit(int bit)
{
    ifstream input_file("words.txt", ios::out | ios::binary);
    ofstream code_file("coded.bin", ios::out | ios::binary);
    unsigned short int count=0; //лічильник оброблених бітів у байті
    char buf=0;
    char c;
    while (input_file.get(c))
    { 
        vector<bool> x = table[c]; // значення цього байту згідно дерева Хаффмана
        for(size_t i=0; i<x.size(); i++)
        {
            buf |= x[i]<<(7-count);  //зсув ліворуч на 7-count бітів та запис у байт x[i]
            count++; 
            if (count==8) 
            { 
                  
                code_file << buf; 
                count=0; 
                buf=0; 
            }
       }
    }
    input_file.close();
    code_file.close();
    
}

void HuffmanTree::print_codes(m_pair* ptr, int arr[], int top)
{// лівий - батько - правий
    if(ptr->left != NULL) // якщо є лівий елемент то присвоюємо зв'язку 0, йдемо до лівого елементу
    {
        arr[top] = 0;
        print_codes(ptr->left, arr, top+1);
    }
    if(ptr->right != NULL)
    {
        arr[top] = 1;
        print_codes(ptr->right, arr, top+1);
    }

    if(!ptr->right && !ptr->left) // коли дійдемо до листа то друкуємо його масив (всі літери - листи і всі листи - літери)
    {
        cout << ptr->symbol << " має " << ptr->frequency << " входжень у тексті."
        << " його код за алгоритмом Хаффмана = ";
        vector<bool> v;
        for (size_t i = 0; i < top; i++)
        {
            cout << arr[i];
            if(arr[i] == 0)
            {
                v.push_back(false);
            }
            else
            {
                v.push_back(true);
            }
            
        }
        table[ptr->symbol] = v;
        cout << endl;
        
    }
    
}

void HuffmanTree::delete_element(int index)
{
    
    swap(minHeap[minHeap.size()-1], minHeap[index]);
    delete minHeap[minHeap.size()-1];
    minHeap.erase(minHeap.begin() + minHeap.size()-1);
    

    for (size_t i = 0; 2*i+1 < minHeap.size(); )
    {
        size_t smallest_child = 2*i + 1; // припустимо що найменша ліва дитина
        if ( smallest_child + 1 < minHeap.size() && 
        minHeap[smallest_child]->frequency > minHeap[smallest_child + 1]->frequency) // якщо існує ще одна дитина && ліва дитина > правої
        {
            smallest_child++; //заміняємо ліву дитину на праву
        }

        if(minHeap[i]->frequency <= minHeap[smallest_child]->frequency)
        {
            return; 
        }
        swap(minHeap[i], minHeap[smallest_child]);


        i = smallest_child;
    }
}


m_pair HuffmanTree::extract_min_elements() // повертає найменший елемент та видаляє його з купи
{
    m_pair temp = *minHeap[0];
    delete_element(0);
    
    return temp;
}

int HuffmanTree::add_element(char symb, size_t freq)
{
    m_pair *cur_pair = new m_pair(symb, freq);
    minHeap.push_back(cur_pair);
    int i = minHeap.size()-1;

    for (i; i != 0; i = (i-1)/2)
    {
        if(minHeap[i]->frequency < minHeap[(i-1)/2]->frequency) //якщо новий елемент менше за свого батька міняємо місцями
        {
            swap(minHeap[i], minHeap[(i-1)/2]);
        }
        else return i;
    }
    return i;
}

void HuffmanTree::form_tree()
{
    
    while(minHeap.size() != 1)
    { // 2 найменші елементи видаляємо з масиву, замість них додаємо новий елемент і йому даємо зв'язок left right
        m_pair v = extract_min_elements();
        m_pair *temp = new m_pair(v.symbol, v.frequency); // найменший елемент
        temp->left = v.left;
        temp->right = v.right;

        v = extract_min_elements();
        m_pair *temp1 = new m_pair(v.symbol, v.frequency); // другий найменший елемент
        temp1->left = v.left;
        temp1->right = v.right;

        int index = add_element('$', temp->frequency + temp1->frequency); // повертаємо індекс доданого N елементу і присвоюємо зв'язки

        minHeap[index]->left = temp; 
        minHeap[index]->right = temp1;
    }
    int arr[100];
    print_codes(minHeap[0], arr, 0);
}




int main(int argc, char const *argv[])
{
    fstream File("words.txt");
    
    HuffmanTree HT;
    char ch;
    
    vector<int> frequencies(256, 1);
    vector<char> symbs;
    
    while(File.get(ch))
    {
        bool is_found = false;
        //пошук співпадіння, чи є символ у масиві
        for (size_t i = 0; i < symbs.size(); i++)
        {
            if(ch == symbs[i])
            {
                frequencies[i] ++;
                is_found = true;
                break;
            }
        }
        if(!is_found)
        {
            symbs.push_back(ch);
        }
        
    }
    for (size_t i = 0; i < symbs.size(); i++)
    {
        HT.add_element(symbs[i], frequencies[i]);
    }
    

    HT.form_tree();
    HT.write_bit(1);
    HT.decode();
    return 0;
}
