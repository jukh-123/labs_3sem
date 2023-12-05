

/*
Сформувати дерево з даних про верстати на даному заводі. Забезпечити пошук інформації про
верстат за інвентарним номером з визначенням відсотку перестою за
останній місяць (відносно загального робочого часу за місяць), а
також визначення типу верстатів, який використовується найбільше.
*/




#include "B_Tree.h"

int main(int argc, char const *argv[])
{
    Machine_Tools t1(10, "Test1", "Grinding machine", 100, 10);
    Machine_Tools t2(5, "Test2", "Gear", 10, 0.1);
    Machine_Tools t3(3, "Test3", "Gear", 102, 10);
    Machine_Tools t4(7, "Test4", "Lathe", 100, 10);
    Machine_Tools t5(8, "Test5", "Lathe", 100, 10);
    Machine_Tools t6(15, "Test6", "Drill", 100, 10);
    Machine_Tools t7(11, "Test7", "Drill", 239, 10);
    Machine_Tools t8(13, "Test8", "Saw", 50, 10);
    Machine_Tools t9(12, "Test9", "Saw", 20, 10);
    Machine_Tools t10(14, "Test10", "Shaper", 300, 10);
    Machine_Tools t11(20, "Test11", "Planer", 1100, 10);
    Machine_Tools t12(17, "Test12", "Grinding machine", 100, 10);
    Machine_Tools t13(25, "Test13", "Grinding machine", 100, 10);
    Machine_Tools t14(23, "Test14", "Grinding machine", 100, 10);
    Machine_Tools t15(24, "Test15", "Grinding machine", 100, 10);

    B_Tree BT(t1);
    BT.add_element(t2);
    BT.add_element(t3);
    BT.add_element(t4);
    BT.add_element(t5);
    BT.add_element(t6);
    BT.add_element(t7);
    BT.add_element(t8);
    BT.add_element(t9);
    BT.add_element(t10);
    BT.add_element(t11);
    BT.add_element(t12);
    BT.add_element(t13);
    BT.add_element(t14);
    BT.add_element(t15);
    cout << "***********Пошук верстати з номером 15*****************************" << endl;
    BT.find_element(15);
    cout << "\n\n\n******Пошук 4 найбільш використовуваних типів верстат*************" << endl;
    BT.find_biggest(4);
    cout << "\n\n\n*******Пошук 6 найбільш використовуваних типів верстат*************" << endl;
    BT.find_biggest(6);

    cout << "\n\n\n Вивід дерева: " << endl;
    BT.print_tree();

    BT.delete_element(t8);

    cout << "\n\n\n Вивід дерева після видалення елементу 13: " << endl;
    BT.print_tree();

    return 0;
}
