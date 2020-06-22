/**
 * Arquivo com os testes de inserção com um conjunto de dados sintético
 */

#include "../../rtree/tree.hpp"
#include "../../rtree/split.hpp"
#include "../../rtree/geometry.hpp"

#include <array>
#include <chrono>
#include <cstddef>
#include <iostream>

#include "helper.hpp"


void doInsertTestWithSyntheticData()
{
    
    // Definindo os valores de m e M que serão utilizados em cada instância de teste
    // Os elementos são utilizados em pares
    std::array<std::size_t, 7> mValues{2, 4, 6, 12, 20, 28, 40};
    std::array<std::size_t, 7> MValues{4, 10, 15, 30, 50, 70, 100};

    std::cout << "Teste de inserção com dados sintéticos (Retângulos gerados com o programa rtreeapplet)" << std::endl;
    
    for(std::size_t i = 0; i < mValues.size(); ++i)
    { 
        std::cout << "SI_1 - Construção da árvore com 500 elementos - RTree(" << mValues[i] << "," << MValues[i] << ")" << std::endl;

        auto start = std::chrono::high_resolution_clock::now();
        
        RTree rTree(mValues[i], MValues[i], new QuadraticSplitStrategy());
        insertSyntheticData(rTree);
        auto end = std::chrono::high_resolution_clock::now();

        printTreeHeight(rTree);
        printElementsInTree(rTree);
        printTimeLog(start, end);

        logInCSV("insert_test_syntheticdata_" + std::to_string(i), start, end, rTree, mValues[i], MValues[i], i);
    }
}
