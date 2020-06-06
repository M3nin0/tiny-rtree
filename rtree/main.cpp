#include <iostream>
#include "rtree.hpp"
#include "geometry.hpp"

int main()
{
    // Testando os primeiros passos da inserção
    RTree rTree(2, 4);
    rTree.insert(new BaseRectangle(0, 3, 0, 5));
    std::cout << "print 1" << std::endl; //teste
    rTree.print();
    rTree.insert(new BaseRectangle(3, 6, 0, 1));
    rTree.insert(new BaseRectangle(7, 16, 5, 51));
    std::cout << "print 2" << std::endl;
    rTree.print();
    rTree.insert(new BaseRectangle(14, 16, 51, 510));
    std::cout << "print 3" << std::endl;
    rTree.print();
    
    // Adiciona geometria com o nó raiz cheio
    rTree.insert(new BaseRectangle(12, 13, 15, 21));
    std::cout << "print 4" << std::endl;
    rTree.print();

    // Gerando segunda camada cheia
    rTree.insert(new BaseRectangle(600, 620, 34, 67));
    std::cout << "print 5" << std::endl;
    rTree.print();
    rTree.insert(new BaseRectangle(89, 98, 78, 99));
    std::cout << "print 6" << std::endl;
    rTree.print();

    // Testando a busca 
    rTree.search(new BaseRectangle(12,14,16,22));
    
    return 0;
}
