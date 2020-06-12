#include <iostream>

#include "insert.hpp"
#include "search.hpp"

int main()
{
    doInsertTest();

    std::cout << "\n\n=======\n\n" << std::endl;

    doSearchTest();

    return 0;
}