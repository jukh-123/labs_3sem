


#include <fstream>
#include </home/jukh/PycharmProjects/ALaSD/include.h>
int current_bit = 0;
unsigned char bit_buffer = 0;

FILE *f;

void WriteBit (int bit)
{
    bit_buffer <<= 1; // зсув бітів

    bit_buffer |= bit;

    current_bit++;
    if (current_bit == 8)
    {
        fwrite (&bit_buffer, 1, 1, f);
        current_bit = 0;
        bit_buffer = 0;
    }
}

int main(int argc, char const *argv[])
{
    f = fopen("coded.bin", "w");
    int arr[100] = {1,0,1,0,0,1,1,1,0,0,0,0,0,1,0,1,0,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,0,1,0,1,1,1,1,0,0,0,1,1,0,1,0,0,1,1,1,1,1,0,1,1,0,0,1,1,0,0,1,0,1,1,1,1,0,1,0,1,0,0,1,0,0,0,1,1,1,0,1,0,0,0,0,0,0,1,0,0,1,0,0};
    for (size_t i = 0; i < 100; i++)
    {
        WriteBit(arr[i]);
    }

    ifstream f1("coded1.bin", ios::binary | ios::in);
    char c;
    while (f1.get(c))
    {
        for (int i = 7; i >= 0; i--) // or (int i = 0; i < 8; i++)  if you want reverse bit order in bytes
            cout << ((c >> i) & 1);
    }
    
    return 0;
}
