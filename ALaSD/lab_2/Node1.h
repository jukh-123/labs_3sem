
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