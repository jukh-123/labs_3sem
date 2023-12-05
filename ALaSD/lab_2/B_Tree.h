
/*
Сформувати дерево з даних про верстати на даному заводі. Забезпечити пошук інформації про
верстат за інвентарним номером з визначенням відсотку перестою за
останній місяць (відносно загального робочого часу за місяць), а
також визначення типу верстатів, який використовується найбільше.
*/

/*Клас, що реалізує B-дерево, має дозволяти виконувати
наступні операції на основі окремих методів: створення порожнього
дерева, відображення структури дерева, пошук у дереві, вставлення
ключа, видалення ключа.*/
#include <algorithm>
#include <utility>
#include <vector>
#include </home/jukh/PycharmProjects/ALaSD/include.h>



class Machine_Tools
{
public:
    unsigned int inventory_number;
    string type;
    string inventory_name;
    float inventory_monthtime; //in hours
    float inventory_downtime; //in hours   
    void print_info();
    Machine_Tools(){;}
    Machine_Tools(unsigned int inventory_number, string inventory_name,
    string type, float inventory_monthtime, float inventory_downtime);
    
private:
    string __defined_types[7] = {"Grinding machine", "Gear", "Lathe", "Drill", "Saw", "Shaper", "Planer"};  
      
};
Machine_Tools::Machine_Tools(unsigned int inventory_number, string inventory_name,
                            string type, float inventory_monthtime, float inventory_downtime)
{
    this->inventory_number = inventory_number;
    this->inventory_name = inventory_name;
        
    bool type_flag = false;
    for(size_t i=0; i<sizeof(__defined_types) / sizeof(string); i++) //перевірка на вірність типу
    {
        if(type == __defined_types[i])
        {
            this->type = type;
            type_flag = true;
        }
    }
    if(! type_flag)
    {
        cout << "Ви ввели невірний тип верстати" << endl;
        return;
    }
    
    this->inventory_monthtime = inventory_monthtime;
    this->inventory_downtime = inventory_downtime;
}
void Machine_Tools::print_info()
{
    cout << "Назва: " << inventory_name << ". З серійним номером: " << inventory_number << endl
    << "Тип: " << type << endl
    << "Використовувався " << inventory_monthtime << " годин за поточний місяць" << endl
    << "Простой склав " << inventory_downtime << " годин за поточний місяць" << endl;
}


class Node
{
    public:
        Node* left = NULL;
        Node* right = NULL;
        Machine_Tools tool;
        Node(){tool = Machine_Tools();}
        Node(Machine_Tools _tool) 
        {
            tool = _tool;
        }
};
class B_Tree
{
public:

    B_Tree(){root = NULL;}
    B_Tree(Machine_Tools t);

    void add_element(Machine_Tools t);
    void delete_element(Machine_Tools t);
    void find_element(int inv_num);
    void print_tree();
    void find_biggest(int n=1);
private:
    vector<pair<string, int>> pairs;
    size_t number_of_elements = 0;
    Node* root;
    void __print_tree(Node* node); 
};






B_Tree::B_Tree(Machine_Tools t)
{
    Node *ptr = new Node(t);
    root = ptr;
}
void B_Tree::print_tree()
{
    __print_tree(root);
}
void B_Tree::__print_tree(Node* node) // друкується з початку права дитина, потім батько, потім ліва дитина
{ 
    if(node == NULL)
    {
        return;
    }
    
    __print_tree(node->right);

    node->tool.print_info();

    
    __print_tree(node->left);

    
    
    
}

bool sortbysec(const pair<string,int> &a,
              const pair<string,int> &b)
{
    return (a.second < b.second);
}

void B_Tree::find_biggest(int n)
{
    sort(pairs.rbegin(), pairs.rend(), sortbysec);
    for(size_t i = 0; i < n; i++)
    {
        cout << "Тип верстати " << pairs[i].first << " має " << pairs[i].second << " напрацьованих годин" << endl;
    }
    
}
void B_Tree::add_element(Machine_Tools t)
{
    Node * ptr = new Node(t);
    if(!root ) //якщо дерево пусте
    {
        root = ptr;
        return;
    }
    Node *prev = NULL;
    Node *temp = root;
    while(temp != NULL)
    {
        prev = temp;
        if(temp->tool.inventory_number > t.inventory_number)
        {
            temp = temp->left;
        }
        else if(temp->tool.inventory_number < t.inventory_number)
        {
            temp = temp->right;
        }
    }
    if(prev->tool.inventory_number > t.inventory_number)
    {
        prev->left = ptr;
    }
    else if(prev->tool.inventory_number < t.inventory_number)
    {
        prev->right = ptr;
    }
    
    for(size_t i = 0; i < pairs.size(); i++)
    {
        if(ptr->tool.type == pairs[i].first) //шукаємо тип, якщо у масиві вже існує елемент з цим типом, то додаємо до пари час використання верстати
        {
            pairs[i].second += ptr->tool.inventory_monthtime;
            return;
        }
    }
    //якщо не знайшли жодного елементу з таким типом, то створюємо пару
    pairs.push_back(make_pair(ptr->tool.type, ptr->tool.inventory_monthtime));
}

void B_Tree::find_element(int inv_num)
{
    Node *p1 = root;
    while(p1 != NULL)
    {
        if(inv_num < p1->tool.inventory_number)
        {
            p1 = p1->left;
        }
        else if(inv_num > p1->tool.inventory_number)
        {
            p1 = p1->right;
        }
        else
        {
            p1->tool.print_info();
            cout << "Відсоток перестою за місяць склав: " << (p1->tool.inventory_downtime / p1->tool.inventory_monthtime)*100 << "%" << endl;
            return;
        }
    }


    cout << "Елемент не знайдено" << endl;
    
}

void B_Tree::delete_element(Machine_Tools t)
{
    Node *ptr;
    Node *p1 = root;
    while(p1 != NULL)
    {
        if(t.inventory_number == p1->tool.inventory_number) // знайшли потрібний елемент
        {
            if(p1->left == NULL && p1->right == NULL) //якщо знайшли потрібний елемент і цей елемент є листом
            {
                if(ptr->left == p1) //видаляємо зв'язок батька з цим елементом
                {
                    ptr->left = NULL;
                }
                else
                {
                    ptr->right = NULL;
                }
                delete p1;
                p1 = NULL;
            }
            else if(p1->left == NULL) //немає лівого дочірнього елементу
            {
                if(ptr->left == p1) //шукаємо який p1 дочірній елемент
                {
                    ptr->left = p1->right;
                    delete p1;
                    p1 = NULL;
                }
                else //елемент для видалення праворуч
                {
                    ptr->right = p1->right;
                    delete p1;
                    p1 = NULL;
                }
            }
            else if(p1->right == NULL) //немає правого дочірнього елементу
            {
                if(ptr->left == p1) //шукаємо який це дочірній елемент
                {
                    ptr->left = p1->left;
                    delete p1;
                    p1 = NULL;
                }
                else // елемент для видалення праворуч
                {
                    ptr->right = p1->left;
                    delete p1;
                    p1 = NULL;
                }
            }
            else // є обидва елементи
            { //потрібно знайти найменший елемент з правого піддерева, змінити значення видаляємого елементу на значення найменшого
                ptr = p1;
                Node * temp = p1->right; //вкзаує на найменший елемент правого піддерева
                if(temp->left == NULL && temp->right == NULL) //якщо праворуч від видаляємого елементу знаходиться лист
                {
                    p1->tool = temp->tool;
                    p1->right = NULL;
                    delete temp;
                    return;
                }
                //мінімальне значення дерева завжди буде найлівішим
                while(temp->left != NULL)
                {
                    ptr = temp; //ptr указує на батька найменшого елементу правого піддерева
                    temp = temp->left;
                }
                p1->tool = temp->tool; // на цьому етапі у дереві 2 однакових елементи 
                //у temp не існує лівої дитини, і temp ліва дитина ptr
                
                ptr->left = temp->right; // видаляємо temp і зв'язуємо батька з дочірнім елементом temp, або NULL
                delete temp;
            }
        }
        else if(t.inventory_number < p1->tool.inventory_number)
        {
            ptr = p1;
            p1 = p1->left;
        }
        else if(t.inventory_number > p1->tool.inventory_number)
        {
            ptr = p1;
            p1 = p1->right;
        }
    }
}