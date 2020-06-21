#include <iostream>

#include "insert.hpp"
#include "search.hpp"
#include "real_search.hpp"
#include "real_insert.hpp"
#include "synthetic_insert.hpp"

int main()
{
    doBaseInsertTest();

    std::cout << "\n\n=======\n\n" << std::endl;

    doBaseSearchTest();

    std::cout << "\n\n=======\n\n" << std::endl;

    doInsertTestWithRealData();

    std::cout << "\n\n=======\n\n" << std::endl;

    doInsertTestWithSyntheticData();

    std::cout << "\n\n=======\n\n" << std::endl;

    doSearchTestWithRealDataOne();

    std::cout << "\n\n=======\n\n" << std::endl;

    doSearchTestWithRealDataTwo();

    return 0;
}
