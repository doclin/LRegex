#include <iostream>

using namespace std;

int main()
{
    const char* a= "a\\d";
    cout << (int)a[1] << endl;
    cout << (int)a[2] << endl;
    cout << (int)a[3] << endl;

    return 0;
}