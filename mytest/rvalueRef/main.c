#include <iostream>

int main()
{
    int && rv = 4;
    rv = 5;
    std::cout << rv << std::endl;

    return 0;
}
