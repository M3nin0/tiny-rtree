#include <iostream>
#include "tiny.hpp"
#include "geometry.hpp"

int main()
{
    // Testando os primeiros passos da inserção
    RTree rTree(2, 4);
    rTree.insert(new BaseRectangle(0, 3, 0, 5));
    rTree.insert(new BaseRectangle(3, 6, 0, 1));
    rTree.insert(new BaseRectangle(7, 16, 5, 51));
    rTree.insert(new BaseRectangle(14, 16, 51, 510));
    
    // Adiciona geometria com o nó raiz cheio
    rTree.insert(new BaseRectangle(12, 13, 15, 21));

    // Gerando segunda camada cheia
    rTree.insert(new BaseRectangle(600, 620, 34, 67));
    rTree.insert(new BaseRectangle(89, 98, 78, 99));

    // testando o split com mais nós na árvore
    rTree.insert(new BaseRectangle(700, 820, 999, 1090));

    // Testando o split do segundo nível
    rTree.insert(new BaseRectangle(700, 820, 999, 1090));

    return 0;
}
