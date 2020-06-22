#include <iostream>

#include "insert.hpp"
#include "search.hpp"
#include "real_search.hpp"
#include "real_insert.hpp"
#include "synthetic_insert.hpp"
#include "synthetic_search.hpp"

#include "helper.hpp"

int main()
{
    // Limpando o log
    clearCSV();

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

    std::cout << "\n\n=======\n\n" << std::endl;
    doSearchTestWithSyntheticDataOne();

    return 0;
}
