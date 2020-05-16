#include <iostream>
#include "rtree.hpp"
#include "geometry.hpp"


int main()
{
    // Testando os primeiros passos da inserção
    RTree rTree(2, 4);
    rTree.insert(new BaseRectangle(0, 3, 0, 5));
    rTree.insert(new BaseRectangle(3, 6, 0, 1));
    rTree.insert(new BaseRectangle(7, 16, 5, 51));
    rTree.insert(new BaseRectangle(14, 16, 51, 510));
    // Agora com o primeiro nó cheio
    rTree.insert(new BaseRectangle(12, 13, 15, 21));
    rTree.insert(new BaseRectangle(1, 2, 2, 670));
    rTree.insert(new BaseRectangle(122, 222, 678, 760));
    rTree.insert(new BaseRectangle(122, 222, 678, 760));

    // Calculando espansão de área
    // BaseRectangle* t1 = new BaseRectangle(0, 3, 0, 5);
    // BaseRectangle* t2 = new BaseRectangle(3, 5, 0, 5);
    
    // // Área de cada retângulo
    // std::cout << RectangleArea(t1) << std::endl;
    // std::cout << RectangleArea(t2) << std::endl;

    // std::cout << AreaGain(t1, t2) << std::endl;

    // Testando regras de calculo do MBR (Em níveis)
    // RNode level1a, level1b;
    // RNode level2a, level2b;
    // RNode level3a, level3b1, level3b2;

    // // Inserindo MBR level 3
    // level3a.addMBR(new BaseRectangle(1, 5, 2, 10));
    // level3b1.addMBR(new BaseRectangle(3, 7, 0, 9));
    // level3b2.addMBR(new BaseRectangle(1, 5, 6, 19));
    
    // level3a.setLeaf(true);
    // level3b1.setLeaf(true);
    // level3b2.setLeaf(true);

    // // Inserindo nós
    // level2a.insert(&level3a);
    // level2b.insert(&level3b1);
    // level2b.insert(&level3b2);

    // level1a.insert(&level2a);
    // level1b.insert(&level2b);

    // // testando o mbr
    // BaseRectangle* mbrTotal;

    // // lado a
    // mbrTotal = level1a.mbr();
    // std::cout << "MBR(" << mbrTotal->xmin() << "," << mbrTotal->xmax() << "," << mbrTotal->ymin() << "," << mbrTotal->ymax() << ")" << std::endl;

    // // lado b
    // mbrTotal = level1b.mbr();
    // std::cout << "MBR(" << mbrTotal->xmin() << "," << mbrTotal->xmax() << "," << mbrTotal->ymin() << "," << mbrTotal->ymax() << ")" << std::endl;

    // RNode r;
    // RNode r2;
    // RNode r3;

    // BaseRectangle* mbr1 = new BaseRectangle(2, 5, 1, 3);
    // BaseRectangle* mbr2 = new BaseRectangle(1, 3, 2, 7);
    // BaseRectangle* mbr3 = new BaseRectangle(5, 9, 5, 12);

    // r.addMBR(mbr1);
    // r2.addMBR(mbr2);
    // r3.addMBR(mbr3);

    // r.insert(&r2);
    // // r.insert(&r3);

    // BaseRectangle* mbrTotal = r.mbr();    
    // std::cout << "MBR(" << mbrTotal->xmin() << "," << mbrTotal->xmax() << "," << mbrTotal->ymin() << "," << mbrTotal->ymax() << ")" << std::endl;

    return 0;
}
