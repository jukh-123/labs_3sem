





/*Інформація про речі, вилучені на митниці, включає:
– назву;
– людину, у якої було вилучено даний об’єкт;
– кількість одиниць;
– вартість одиниці;
– дату вилучення.
Відсортувати речі за загальною вартістю, у випадку рівної
загальної вартості – за вартістю одиниці, інакше – за датою
вилучення.*/

#include "Item.h"
#include "LinkedList_Node.h"
#include "BinaryHeap.h"


int main(int argc, char const *argv[])
{
    BinaryHeap h;

    LinkedList l1;

    Item case1("Cup", "John J.", 1000, 0.26, "12-06-2019");
    Item case2("Lamp", "Jack A.", 30, 5, "12-07-2012");
    Item case3("Pillow", "Jake F.", 1000, 3, "19-01-2010");
    Item case4("Chisel", "Gin C.", 130, 2, "12-09-2021");

    Item case5("Chis222el", "Gin C.", 1300, 2, "12-09-2021");
    Item case6("123", "Gifn C.", 1, 2, "12-09-2021");
    Item case7("444", "Gisn C.", 4, 2, "12-09-2021");


    h.add_element(case1);
    h.add_element(case2);
    h.add_element(case3);
    h.add_element(case4);
    h.add_element(case5);

    h.add_element(case6);
    h.add_element(case7);
    h.delete_element(case4);
    // h.heap_sort();
    h.show_items();

    // l1.add_item(case1); 
    // l1.add_item(case2); 
    // l1.add_item(case3); 
    // l1.add_item(case4); 

    

    // l1.add_item(case5, &case2); 
    // l1.delete_item(case3);
    // l1.show_items(true);
    

    


    return 0;
}
