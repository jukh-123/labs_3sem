


#include "Node1.h"
#include "HashTable.h"











int main(int argc, char const *argv[])
{
    ifstream words_file("words.txt");
    string str;
    HashTable HT;
    int counter = 0;
    if(words_file.is_open())
    {
        while(words_file >> str)
        {
            HT.add_element(str);
            // if(str == "a")
            // {
            //     counter ++;
            // }
            
        }
    }
    HT.find_biggest_element();
    return 0;
}
