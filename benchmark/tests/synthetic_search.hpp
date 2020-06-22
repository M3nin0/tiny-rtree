/**
 * Arquivo com os testes de busca em um conjunto de dados sintético
*/

#include "../../rtree/tree.hpp"
#include "../../rtree/split.hpp"
#include "../../rtree/geometry.hpp"

#include <array>
#include <chrono>
#include <cstddef>
#include <iostream>

#include "helper.hpp"


void doSearchTestWithSyntheticDataOne()
{
    // Definindo os valores de m e M que serão utilizados em cada instância de teste
    // Os elementos são utilizados em pares
    std::array<std::size_t, 7> mValues{2, 4, 6, 12, 20, 28, 40};
    std::array<std::size_t, 7> MValues{4, 10, 15, 30, 50, 70, 100};

    std::cout << "Teste de busca com dados reais (Municípios do Brasil)| Retângulo menor" << std::endl;
    
    for(std::size_t i = 0; i < mValues.size(); ++i)
    { 
        std::cout << "SS_1 - Busca na árvore com 500 elementos - RTree(" << mValues[i] << ", " << MValues[i] << ")" << std::endl;
        RTree rTree(mValues[i], MValues[i], new QuadraticSplitStrategy());

        insertSyntheticData(rTree);

        auto start = std::chrono::high_resolution_clock::now();
        std::vector<RNode*> els = rTree.search(new Rectangle(30, 1120, 1970, 2310));
        auto end = std::chrono::high_resolution_clock::now();

        assert(els.size() == 103); // Contado um a um para verificação =D
        std::cout << els.size() << std::endl;

        printTreeHeight(rTree);
        printElementsInTree(rTree);
        printTimeLog(start, end);
        printRecoveredElements(els, 103);

        // log
        logInCSV("retangulo_sintetico_search_" + std::to_string(i), start, end, rTree, mValues[i], MValues[i], i);
    }
}
