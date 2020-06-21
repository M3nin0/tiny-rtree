#include "../../rtree/tree.hpp"
#include "../../rtree/split.hpp"
#include "../../rtree/geometry.hpp"

#include <chrono>
#include <iostream>
#include <cassert>

#include "helper.hpp"

/**
 * Função de teste de busca básica, para testes iniciais na r-tree implementada
 */
void doBaseSearchTest()
{
    std::cout << "Teste de busca" << std::endl;

    {
        std::cout << "B1 - Busca na árvore com 5 elementos - RTree(2, 4)" << std::endl;

        RTree rTree(2, 4, new QuadraticSplitStrategy());
        rTree.insert(new Rectangle(1., 2., 3., 5.));
        rTree.insert(new Rectangle(3., 7., 4., 6.));
        rTree.insert(new Rectangle(3., 9., 1., 3.));
        rTree.insert(new Rectangle(8., 9., 3.5, 6.));
        rTree.insert(new Rectangle(3., 7.5, 3.3, 3.9));

        auto start = std::chrono::high_resolution_clock::now();
        std::vector<RNode*> els = rTree.search(new Rectangle(1.5, 4.5, 4.7, 5.7));
        auto end = std::chrono::high_resolution_clock::now();

        assert(els.size() == 2);

        printTreeHeight(rTree);
        printElementsInTree(rTree);
        printTimeLog(start, end);
        printRecoveredElements(els, 2);
    }

    {
        std::cout << "B2 - Busca na árvore com 5 elementos - RTree(1, 2)" << std::endl;

        RTree rTree(1, 2, new QuadraticSplitStrategy());
        rTree.insert(new Rectangle(1., 2., 3., 5.));
        rTree.insert(new Rectangle(3., 7., 4., 6.));
        rTree.insert(new Rectangle(3., 9., 1., 3.));
        rTree.insert(new Rectangle(8., 9., 3.5, 6.));
        rTree.insert(new Rectangle(3., 7.5, 3.3, 3.9));

        auto start = std::chrono::high_resolution_clock::now();
        std::vector<RNode*> els = rTree.search(new Rectangle(1.5, 4.5, 4.7, 5.7));
        auto end = std::chrono::high_resolution_clock::now();

        assert(els.size() == 2);

        printTreeHeight(rTree);
        printElementsInTree(rTree);
        printTimeLog(start, end);
        printRecoveredElements(els, 2);
    }

    {
        std::cout << "B3 - Busca na árvore com 7 elementos - RTree(3, 6)" << std::endl;

        RTree rTree(3, 6, new QuadraticSplitStrategy());
        rTree.insert(new Rectangle(1., 2., 3., 5.));
        rTree.insert(new Rectangle(3., 7., 4., 6.));
        rTree.insert(new Rectangle(3., 9., 1., 3.));
        rTree.insert(new Rectangle(8., 9., 3.5, 6.));
        rTree.insert(new Rectangle(3., 7.5, 3.3, 3.9));
        rTree.insert(new Rectangle(1.5, 4.5, 1.5, 2.9));
        rTree.insert(new Rectangle(2.1, 2.9, 1, 6.7));

        auto start = std::chrono::high_resolution_clock::now();
        std::vector<RNode*> els = rTree.search(new Rectangle(1., 2.9, 1.2, 5.9));
        auto end = std::chrono::high_resolution_clock::now();

        assert(els.size() == 3);

        printTreeHeight(rTree);
        printElementsInTree(rTree);
        printTimeLog(start, end);
        printRecoveredElements(els, 3);
    }

    {
        std::cout << "B4 - Busca na árvore com 9 elementos - RTree(4, 8)" << std::endl;

        RTree rTree(4, 8, new QuadraticSplitStrategy());
        rTree.insert(new Rectangle(1., 2., 3., 5.));
        rTree.insert(new Rectangle(3., 7., 4., 6.));
        rTree.insert(new Rectangle(3., 9., 1., 3.));
        rTree.insert(new Rectangle(8., 9., 3.5, 6.));
        rTree.insert(new Rectangle(3., 7.5, 3.3, 3.9));
        rTree.insert(new Rectangle(1.5, 4.5, 1.5, 2.9));
        rTree.insert(new Rectangle(2.1, 2.9, 1, 6.7));
        rTree.insert(new Rectangle(4.1, 8.7, 6.2, 7.1));
        rTree.insert(new Rectangle(3.7, 4.8, 4.9, 7.6));

        auto start = std::chrono::high_resolution_clock::now();
        std::vector<RNode*> els = rTree.search(new Rectangle(3.4, 4.9, 5.2, 5.9));
        auto end = std::chrono::high_resolution_clock::now();

        assert(els.size() == 2);

        printTreeHeight(rTree);
        printElementsInTree(rTree);
        printTimeLog(start, end);
        printRecoveredElements(els, 2);
    }

    {
        std::cout << "B5 - Busca na árvore com 9 elementos - RTree(2, 8)" << std::endl;

        RTree rTree(2, 8, new QuadraticSplitStrategy());
        rTree.insert(new Rectangle(1., 2., 3., 5.));
        rTree.insert(new Rectangle(3., 7., 4., 6.));
        rTree.insert(new Rectangle(3., 9., 1., 3.));
        rTree.insert(new Rectangle(8., 9., 3.5, 6.));
        rTree.insert(new Rectangle(3., 7.5, 3.3, 3.9));
        rTree.insert(new Rectangle(1.5, 4.5, 1.5, 2.9));
        rTree.insert(new Rectangle(2.1, 2.9, 1, 6.7));
        rTree.insert(new Rectangle(4.1, 8.7, 6.2, 7.1));
        rTree.insert(new Rectangle(3.7, 4.8, 4.9, 7.6));

        auto start = std::chrono::high_resolution_clock::now();
        std::vector<RNode*> els = rTree.search(new Rectangle(7.7, 8.1, 3.8, 4.5));
        auto end = std::chrono::high_resolution_clock::now();

        assert(els.size() == 1);

        printTreeHeight(rTree);
        printElementsInTree(rTree);
        printTimeLog(start, end);
        printRecoveredElements(els, 1);
    }

    {
        std::cout << "B6 - Busca na árvore com 9 elementos - RTree(3, 10)" << std::endl;

        RTree rTree(3, 10, new QuadraticSplitStrategy());
        rTree.insert(new Rectangle(1., 2., 3., 5.));
        rTree.insert(new Rectangle(3., 7., 4., 6.));
        rTree.insert(new Rectangle(3., 9., 1., 3.));
        rTree.insert(new Rectangle(8., 9., 3.5, 6.));
        rTree.insert(new Rectangle(3., 7.5, 3.3, 3.9));
        rTree.insert(new Rectangle(1.5, 4.5, 1.5, 2.9));
        rTree.insert(new Rectangle(2.1, 2.9, 1, 6.7));
        rTree.insert(new Rectangle(4.1, 8.7, 6.2, 7.1));
        rTree.insert(new Rectangle(3.7, 4.8, 4.9, 7.6));

        auto start = std::chrono::high_resolution_clock::now();
        std::vector<RNode*> els = rTree.search(new Rectangle(2.6, 3.9, 1.7, 2.2));
        auto end = std::chrono::high_resolution_clock::now();

        assert(els.size() == 3);
        printTreeHeight(rTree);
        printElementsInTree(rTree);
        printTimeLog(start, end);
        printRecoveredElements(els, 3);
    }

    {
        std::cout << "B7 - Busca na árvore com 10 elementos - RTree(1, 2)" << std::endl;

        RTree rTree(1, 2, new QuadraticSplitStrategy());
        rTree.insert(new Rectangle(1., 2., 3., 5.));
        rTree.insert(new Rectangle(3., 7., 4., 6.));
        rTree.insert(new Rectangle(3., 9., 1., 3.));
        rTree.insert(new Rectangle(8., 9., 3.5, 6.));
        rTree.insert(new Rectangle(3., 7.5, 3.3, 3.9));
        rTree.insert(new Rectangle(1.5, 4.5, 1.5, 2.9));
        rTree.insert(new Rectangle(2.1, 2.9, 1, 6.7));
        rTree.insert(new Rectangle(4.1, 8.7, 6.2, 7.1));
        rTree.insert(new Rectangle(3.7, 4.8, 4.9, 7.6));
        rTree.insert(new Rectangle(6.1, 6.9, 1.8, 6.99));

        auto start = std::chrono::high_resolution_clock::now();
        std::vector<RNode*> els = rTree.search(new Rectangle(2.9, 8.02, 4.9, 5.5));
        auto end = std::chrono::high_resolution_clock::now();

        assert(els.size() == 5);
        printTreeHeight(rTree);
        printElementsInTree(rTree);
        printTimeLog(start, end);
        printRecoveredElements(els, 5);
    }

    {
        std::cout << "B8 - Busca na árvore com 16 elementos - RTree(1, 2)" << std::endl;

        RTree rTree(1, 2, new QuadraticSplitStrategy());
        rTree.insert(new Rectangle(1., 2., 3., 5.));
        rTree.insert(new Rectangle(3., 7., 4., 6.));
        rTree.insert(new Rectangle(3., 9., 1., 3.));
        rTree.insert(new Rectangle(8., 9., 3.5, 6.));
        rTree.insert(new Rectangle(3., 7.5, 3.3, 3.9));
        rTree.insert(new Rectangle(1.5, 4.5, 1.5, 2.9));
        rTree.insert(new Rectangle(2.1, 2.9, 1, 6.7));
        rTree.insert(new Rectangle(4.1, 8.7, 6.2, 7.1));
        rTree.insert(new Rectangle(3.7, 4.8, 4.9, 7.6));
        rTree.insert(new Rectangle(6.1, 6.9, 1.8, 6.99));
        rTree.insert(new Rectangle(3.5, 3.9, 4.1, 4.4));
        rTree.insert(new Rectangle(4.5, 4.9, 4.2, 4.7));
        rTree.insert(new Rectangle(5.3, 5.7, 3.7, 4.8));
        rTree.insert(new Rectangle(3.2, 9.1, 1.74, 2.7));
        rTree.insert(new Rectangle(6.3, 6.8, 2.2, 2.6));
        rTree.insert(new Rectangle(7.8, 7.9, 1.9, 5.2));

        auto start = std::chrono::high_resolution_clock::now();
        std::vector<RNode*> els = rTree.search(new Rectangle(2.1, 9.2, 2.5, 5.5));
        auto end = std::chrono::high_resolution_clock::now();
        assert(els.size() == 14);

        printTreeHeight(rTree);
        printElementsInTree(rTree);
        printTimeLog(start, end);
        printRecoveredElements(els, 14);
    }
}
