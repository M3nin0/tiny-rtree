#include <iostream>

#include "tree.hpp"
#include "split.hpp"
#include "geometry.hpp"

int main()
{
    // Testando os primeiros passos da inserção
    RTree rTree(2, 4, new LinearSplitStrategy());
    
    // Os valores abaixo foram criados utilizando o programa rtree2.jnlp
    // junto ao código 'autortree.py'
    rTree.insert(new Rectangle(588.0, 1371.0, 180.0, 617.0));
    rTree.insert(new Rectangle(381.0, 700.0, 89.0, 314.0));
    rTree.insert(new Rectangle(504.0, 834.0, 525.0, 744.0));
    rTree.insert(new Rectangle(1213.0, 1491.0, 361.0, 671.0));
    rTree.insert(new Rectangle(227.0, 453.0, 378.0, 649.0));
    rTree.insert(new Rectangle(1413.0, 1615.0, 38.0, 212.0));
    rTree.insert(new Rectangle(1555.0, 1623.0, 719.0, 795.0));
    rTree.insert(new Rectangle(160.0, 262.0, 213.0, 290.0));
    rTree.insert(new Rectangle(113.0, 214.0, 658.0, 810.0));
    rTree.insert(new Rectangle(144.0, 502.0, 53.0, 166.0));
    rTree.insert(new Rectangle(1008.0, 1168.0, 16.0, 91.0));
    rTree.insert(new Rectangle(906.0, 1074.0, 708.0, 822.0));
    rTree.insert(new Rectangle(1582.0, 1647.0, 248.0, 360.0));
    rTree.insert(new Rectangle(852.0, 964.0, 26.0, 129.0));
    rTree.insert(new Rectangle(1642.0, 1696.0, 213.0, 505.0));
    rTree.insert(new Rectangle(366.0, 1302.0, 354.0, 819.0));
    rTree.insert(new Rectangle(1159.0, 1409.0, 132.0, 314.0));
    rTree.insert(new Rectangle(1047.0, 1309.0, 129.0, 286.0));
    rTree.insert(new Rectangle(1392.0, 1557.0, 74.0, 227.0));
    rTree.insert(new Rectangle(1122.0, 1454.0, 594.0, 836.0));
    rTree.insert(new Rectangle(80.0, 199.0, 396.0, 589.0));
    rTree.insert(new Rectangle(205.0, 289.0, 315.0, 383.0));
    rTree.insert(new Rectangle(342.0, 516.0, 335.0, 453.0));
    rTree.insert(new Rectangle(685.0, 867.0, 368.0, 536.0));

    // Os testes abaixo foram feitos inserido os retângulos
    // rTree.insert(new Rectangle(0, 3, 0, 5));
    // rTree.insert(new Rectangle(3, 6, 0, 1));
    // rTree.insert(new Rectangle(7, 16, 5, 51));
    // rTree.insert(new Rectangle(14, 16, 51, 510));
    
    // // Adiciona geometria com o nó raiz cheio
    // rTree.insert(new Rectangle(12, 13, 15, 21));

    // // Gerando segunda camada cheia
    // rTree.insert(new Rectangle(600, 620, 34, 67));
    // rTree.insert(new Rectangle(89, 98, 78, 99));

    // // testando o split com mais nós na árvore
    // rTree.insert(new Rectangle(700, 820, 999, 1090));

    // // Testando o split do segundo nível
    // rTree.insert(new Rectangle(400, 430, 600, 1080));
    // rTree.insert(new Rectangle(400, 700, 34, 1080));
    // rTree.insert(new Rectangle(400, 820, 600, 999));
    // rTree.insert(new Rectangle(430, 600, 700, 1090));
    // rTree.insert(new Rectangle(600, 625, 820, 999));
    // rTree.insert(new Rectangle(98, 500, 78, 99));
    // rTree.insert(new Rectangle(13, 21, 12, 99));
    // rTree.insert(new Rectangle(89, 99, 78, 1809));

    return 0;
}
