#include <callbacks/callbacks.h>

#include <iostream>

int main(int, char*[])
{
    auto sum = callbacks::add(1, 1);
    std::cout << sum << std::endl;
    return 0;
}
