/**
 * Arquivo com os testes de busca em um conjunto de dados real
 */

#include "../../rtree/tree.hpp"
#include "../../rtree/split.hpp"
#include "../../rtree/geometry.hpp"

#include <array>
#include <chrono>
#include <cstddef>
#include <iostream>

#include "helper.hpp"


void doSearchTestWithRealDataOne()
{
    // Definindo os valores de m e M que serão utilizados em cada instância de teste
    // Os elementos são utilizados em pares
    std::array<std::size_t, 4> mValues{2, 4, 20, 40};
    std::array<std::size_t, 4> MValues{4, 10, 50, 100};

    std::cout << "Teste de busca com dados reais (Municípios do Brasil)| Retângulo menor" << std::endl;
    
    for(std::size_t i = 0; i < mValues.size(); ++i)
    { 
        std::cout << "C1 - Construção da árvore com 5572 elementos - RTree(" << mValues[i] << ", " << MValues[i] << ")" << std::endl;
        RTree rTree(mValues[i], MValues[i], new QuadraticSplitStrategy());

        insertBrazilianCitiesData(rTree); // feito para remover qualquer tipo de E/S

        auto start = std::chrono::high_resolution_clock::now();
        std::vector<RNode*> els = rTree.search(new Rectangle(-55.695, -53.870, -7.174, -5.750));
        auto end = std::chrono::high_resolution_clock::now();

        assert(els.size() == 3);

        printTreeHeight(rTree);
        printElementsInTree(rTree);
        printTimeLog(start, end);
        printRecoveredElements(els, 3);
    }
}


void doSearchTestWithRealDataTwo()
{
    // Definindo os valores de m e M que serão utilizados em cada instância de teste
    // Os elementos são utilizados em pares
    std::array<std::size_t, 4> mValues{2, 4, 20, 40};
    std::array<std::size_t, 4> MValues{4, 10, 50, 100};

    std::cout << "Teste de busca com dados reais (Municípios do Brasil) | Retângulo maior" << std::endl;
    
    for(std::size_t i = 0; i < mValues.size(); ++i)
    { 
        std::cout << "C1 - Construção da árvore com 5572 elementos - RTree(" << mValues[i] << ", " << MValues[i] << ")" << std::endl;
        RTree rTree(mValues[i], MValues[i], new QuadraticSplitStrategy());

        insertBrazilianCitiesData(rTree); // feito para remover qualquer tipo de E/S

        auto start = std::chrono::high_resolution_clock::now();
        std::vector<RNode*> els = rTree.search(new Rectangle(-40.93, -33.82, -13.21, -2.12));
        auto end = std::chrono::high_resolution_clock::now();

        assert(els.size() == 1140);

        printTreeHeight(rTree);
        printElementsInTree(rTree);
        printTimeLog(start, end);
        printRecoveredElements(els, 1140);
    }
}
