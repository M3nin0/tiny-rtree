#ifndef __HELPER__
#define __HELPER__

#include "../../rtree/tree.hpp"
#include "../../rtree/split.hpp"
#include "../../rtree/geometry.hpp"

#include <chrono>
#include <iostream>

/**
 * DESCRIPTION: Função auxiliar para facilitar a visualização da quantidade de elementos na árvore
 */
void printElementsInTree(const RTree& tree) 
{
    std::cout << "Quantidade de elementos na árvore: " << tree.count() << std::endl;
}

/**
 * DESCRIPTION: Função auxiliar para facilitar a visualização da altura da árvore
 */
void printTreeHeight(const RTree& tree)
{
    std::cout << "Altura da árvore: " << tree.height() << std::endl;
}

/**
 * DESCRIPTION: Função auxiliar para facilitar a visualização dos resultados
 * 
 * SEE: http://www.cplusplus.com/reference/chrono/high_resolution_clock/now
 * SEE: https://en.cppreference.com/w/cpp/chrono/time_point/time_since_epoch
 */
void printTimeLog(std::chrono::time_point<std::chrono::high_resolution_clock> start, 
                    std::chrono::time_point<std::chrono::high_resolution_clock> end)
{
    auto initialTime = std::chrono::time_point_cast<std::chrono::milliseconds>(start).time_since_epoch().count();
    auto finalTime = std::chrono::time_point_cast<std::chrono::milliseconds>(end).time_since_epoch().count();

    std::cout << "Tempo utilizado: " << (finalTime - initialTime) << " (ms)" << std::endl;
}

void printRecoveredElements(std::vector<RNode*> els, int nCorrected)
{
    std::cout << "Foram encontrados " << els.size() << "/" << nCorrected << std::endl;
}

#endif // __TIMER__
