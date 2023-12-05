#include </home/jukh/PycharmProjects/ALaSD/include.h>

class Item
{
public:
    string item_name;
    string person;
    unsigned int item_amount;
    float item_cost;

    string date;
    float total_cost;

    Item(string item_name, string person, unsigned int item_amount, float item_cost, string date);
    Item();
    void print_data();

    bool operator==(const Item& i);
    bool operator!=(const Item& i);

};
bool Item::operator==(const Item& i)
{
    if(item_name == i.item_name && person == i.person && item_amount == i.item_amount && item_cost == i.item_cost
    && date == i.date)
    {
        return true;
    }
    else return false;
}


bool Item::operator!=(const Item& i)
{
    if(item_name != i.item_name || person != i.person || item_amount != i.item_amount || item_cost != i.item_cost
    || date != i.date)
    {
        return true;
    }
    else return false;
}

Item::Item()
{
    this->item_name = "";
    this->person = "";
    this->item_amount = 0;
    this->item_cost = 0;
    this->date = "";
}
Item::Item(string item_name, string person, unsigned int item_amount, float item_cost, string date)
{
    this->item_name = item_name;
    this->person = person;
    this->item_amount = item_amount;
    this->item_cost = item_cost;
    this->date = date;
    this->total_cost = item_cost*item_amount;
}

void Item::print_data()
{
    cout << "Ім'я: " << person << endl
    << "Предмет: " << item_name << endl
    << "Кількість: " << item_amount << endl
    << "Вартість одиниці: " << item_cost << endl
    << "Дата вилучення: " << date << endl
    << "Загальна вартість: " << item_amount * item_cost << endl;
}
