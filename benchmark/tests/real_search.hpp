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


void doSearchTestWithRealData()
{
    
    // Definindo os valores de m e M que serão utilizados em cada instância de teste
    // Os elementos são utilizados em pares
    std::array<std::size_t, 4> mValues{2, 4, 20, 40};
    std::array<std::size_t, 4> MValues{4, 10, 50, 100};

    std::cout << "Teste de busca com dados reais (Municípios do Brasil)" << std::endl;
    
    for(std::size_t i = 0; i < mValues.size(); ++i)
    { 
        std::cout << "C1 - Construção da árvore com 5572 elementos - RTree(" << mValues[i] << "," << MValues[i] << ")" << std::endl;
        RTree rTree(mValues[i], MValues[i], new QuadraticSplitStrategy());

        insertBrazilianCitiesData(rTree); // feito para remover qualquer tipo de E/S

        auto start = std::chrono::high_resolution_clock::now();
        std::vector<RNode*> els = rTree.search(new Rectangle(1.5, 4.5, 4.7, 5.7));
        auto end = std::chrono::high_resolution_clock::now();

        assert(els.size() == 2);

        printTreeHeight(rTree);
        printElementsInTree(rTree);
        printTimeLog(start, end);
        printRecoveredElements(els, 2);
    }
}
