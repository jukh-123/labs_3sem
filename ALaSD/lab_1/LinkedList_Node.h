
class Node
{
public:
    Item item;
    Node *prev, *next;

    Node(Item item);
    Node(){item = Item();};
};

Node::Node(Item item)
{
    this->item = item;
    next = NULL;
}

class LinkedList
{
public:
    Node *head, *tail;
  
    LinkedList(){head = NULL;}
    void add_item(Item item, Item *after_item = NULL);
    void find_item(string item_name, string owner_name);
    void delete_item(Item item);
    void show_items(bool from_end=false);

};

void LinkedList::add_item(Item item, Item *after_item)
{
    Node *ptr = new Node(item);
    
    
    

    if(this->head == NULL) // якщо список пустий
    {
        this->head = ptr;
        this->tail = ptr;
    }
    else
    {
        if(after_item != NULL)
        {
            Node *AI = this-> head;
            while(AI->item != *after_item)
            {
                AI = AI->next;
                if(AI == NULL)
                {
                    cout << "Невірний об'єкт для вставки" << endl;
                    return;
                }
            }

            if(AI != this->tail) //якщо елемент після котрого потрібно додати новий елемент не у кінці списку, то робимо вставку, інакше вставка у кінець
            {
                AI->next->prev = ptr;
                ptr->next = AI->next;
                AI->next = ptr;
                ptr->prev = AI;
                return;
            }
        }

        this->tail->next = ptr; // старий кінець списку указує на новий елемент
        ptr->prev = this->tail; // новий кінець списку вказує на старий кінець списку
        this->tail = ptr; // присвоєння нового кінця списку
    }
}

void LinkedList::find_item(string item_name, string owner_name)
{
    Node *ptr = this->head;
    while(ptr->item.item_name != item_name || ptr->item.person != owner_name) 
    {
        ptr = ptr->next;
        if(ptr == NULL)
        {
            cout << "За запитом не знайдено жодного предмету."<<endl;
            return;
        }
    }
    cout << "\n ************************************* Знайдено предмет за запитом. *******" << endl;
    ptr->item.print_data();
}

void LinkedList::delete_item(Item item1)
{
    Node *ptr = this->head;
    while(ptr->item != item1)
    {
        ptr = ptr->next;
        if(ptr == NULL)
        {
            cout << "Об'єкт для видалення не знайдено." << endl;
            return;
        }
    }

    Node *prev_obj = ptr->prev;
    Node *next_obj = ptr->next;

    cout << "\n*******************Видалено об'єкт.*** \n"<< endl;
    ptr->item.print_data() ;
    delete ptr;



    if(next_obj == NULL) // якщо ptr = tail
    {
        this->tail = prev_obj;
    }
    else
    {
        next_obj->prev = prev_obj;
    }
    
    if(prev_obj == NULL) //якщо ptr = head
    {
        this->head = next_obj;
    }
    else
    {
        prev_obj->next = next_obj;
    }
    

}

void LinkedList::show_items(bool from_end)
{
    
    if(from_end)
    {
        Node *ptr = this->tail;
        while(ptr != NULL)
        {
            cout << "***************Case: *****************" << endl;
            ptr->item.print_data();
            ptr = ptr->prev;
            cout << endl;
        }
    }
    else
    {
        Node *ptr = this->head;
        while(ptr != NULL)
        {
            cout << "***************Case: *****************" << endl;
            ptr->item.print_data();
            ptr = ptr->next;
        }
    }
}

