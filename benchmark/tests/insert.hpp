#include "../../rtree/tree.hpp"
#include "../../rtree/split.hpp"
#include "../../rtree/geometry.hpp"

#include <chrono>
#include <iostream>

#include "helper.hpp"

/**
 * Função de teste de inserção básica, para testes iniciais na r-tree implementada
 */
void doBaseInsertTest()
{
    std::cout << "Teste de inserção" << std::endl;

    { // Utilizando o ciclo de vida de objetos em C++
        std::cout << "C1 - Construção da árvore com 10 elementos - RTree(2, 4)" << std::endl;

        auto start = std::chrono::high_resolution_clock::now();

        // Testando os primeiros passos da inserção
        // A estratégia de split é passada por parâmetro
        RTree rTree(2, 4, new QuadraticSplitStrategy());

        // Os valores abaixo foram criados utilizando o programa rtree2.jnlp
        // junto ao código 'autortree.py'
        rTree.insert(new Rectangle(0.0, 40.0, 0.0, 35.0));
        rTree.insert(new Rectangle(10.0, 45.0, 210.0, 230.0));
        rTree.insert(new Rectangle(170.0, 200.0, 50.0, 150.0));
        rTree.insert(new Rectangle(75.0, 125.0, 110.0, 125.0));
        rTree.insert(new Rectangle(50.0, 65.0, 130.0, 160.0));
        rTree.insert(new Rectangle(15.0, 30.0, 140.0, 150.0));
        rTree.insert(new Rectangle(100.0, 130.0, 50.0, 90.0));
        rTree.insert(new Rectangle(150.0, 155.0, 40.0, 60.0));
        rTree.insert(new Rectangle(52.0, 75.0, 80.0, 90.0));
        rTree.insert(new Rectangle(62.0, 85.0, 65.0, 75.0));

        auto end = std::chrono::high_resolution_clock::now();
        printTreeHeight(rTree);
        printElementsInTree(rTree);
        printTimeLog(start, end);
    }

    { 
        std::cout << "C2 - Construção da árvore com 50 elementos - RTree(2, 4)" << std::endl;
        auto start = std::chrono::high_resolution_clock::now();

        RTree rTree(2, 4, new QuadraticSplitStrategy());

        rTree.insert(new Rectangle(0.0, 40.0, 0.0, 35.0));
        rTree.insert(new Rectangle(10.0, 45.0, 210.0, 230.0));
        rTree.insert(new Rectangle(170.0, 200.0, 50.0, 150.0));
        rTree.insert(new Rectangle(75.0, 125.0, 110.0, 125.0));
        rTree.insert(new Rectangle(50.0, 65.0, 130.0, 160.0));
        rTree.insert(new Rectangle(15.0, 30.0, 140.0, 150.0));
        rTree.insert(new Rectangle(100.0, 130.0, 50.0, 90.0));
        rTree.insert(new Rectangle(150.0, 155.0, 40.0, 60.0));
        rTree.insert(new Rectangle(52.0, 75.0, 80.0, 90.0));
        rTree.insert(new Rectangle(62.0, 85.0, 65.0, 75.0));
        rTree.insert(new Rectangle(20.0, 25.0, 75.0, 80.0));
        rTree.insert(new Rectangle(30.0, 50.0, 40.0, 80.0));
        rTree.insert(new Rectangle(102.0, 113.0, 155.0, 217.0));
        rTree.insert(new Rectangle(163.0, 272.0, 169.0, 264.0));
        rTree.insert(new Rectangle(303.0, 360.0, 80.0, 144.0));
        rTree.insert(new Rectangle(351.0, 385.0, 68.0, 90.0));
        rTree.insert(new Rectangle(355.0, 373.0, 111.0, 131.0));
        rTree.insert(new Rectangle(365.0, 388.0, 183.0, 204.0));
        rTree.insert(new Rectangle(373.0, 396.0, 235.0, 250.0));
        rTree.insert(new Rectangle(368.0, 388.0, 261.0, 282.0));
        rTree.insert(new Rectangle(379.0, 411.0, 295.0, 317.0));
        rTree.insert(new Rectangle(426.0, 438.0, 260.0, 271.0));
        rTree.insert(new Rectangle(447.0, 494.0, 204.0, 235.0));
        rTree.insert(new Rectangle(485.0, 519.0, 183.0, 208.0));
        rTree.insert(new Rectangle(518.0, 560.0, 106.0, 140.0));
        rTree.insert(new Rectangle(505.0, 559.0, 97.0, 135.0));
        rTree.insert(new Rectangle(481.0, 540.0, 21.0, 66.0));
        rTree.insert(new Rectangle(517.0, 590.0, 16.0, 47.0));
        rTree.insert(new Rectangle(573.0, 594.0, 242.0, 263.0));
        rTree.insert(new Rectangle(594.0, 629.0, 208.0, 243.0));
        rTree.insert(new Rectangle(584.0, 653.0, 161.0, 206.0));
        rTree.insert(new Rectangle(583.0, 613.0, 327.0, 335.0));
        rTree.insert(new Rectangle(629.0, 651.0, 297.0, 313.0));
        rTree.insert(new Rectangle(660.0, 691.0, 288.0, 309.0));
        rTree.insert(new Rectangle(696.0, 712.0, 262.0, 281.0));
        rTree.insert(new Rectangle(208.0, 257.0, 322.0, 347.0));
        rTree.insert(new Rectangle(319.0, 390.0, 332.0, 376.0));
        rTree.insert(new Rectangle(277.0, 320.0, 399.0, 422.0));
        rTree.insert(new Rectangle(251.0, 280.0, 367.0, 385.0));
        rTree.insert(new Rectangle(152.0, 185.0, 377.0, 395.0));
        rTree.insert(new Rectangle(142.0, 173.0, 399.0, 412.0));
        rTree.insert(new Rectangle(95.0, 121.0, 351.0, 360.0));
        rTree.insert(new Rectangle(99.0, 122.0, 303.0, 315.0));
        rTree.insert(new Rectangle(103.0, 151.0, 264.0, 293.0));
        rTree.insert(new Rectangle(245.0, 274.0, 278.0, 293.0));
        rTree.insert(new Rectangle(481.0, 514.0, 358.0, 382.0));
        rTree.insert(new Rectangle(516.0, 534.0, 314.0, 326.0));
        rTree.insert(new Rectangle(518.0, 533.0, 297.0, 301.0));
        rTree.insert(new Rectangle(577.0, 595.0, 363.0, 373.0));
        rTree.insert(new Rectangle(650.0, 669.0, 390.0, 406.0));

        auto end = std::chrono::high_resolution_clock::now();
        printTreeHeight(rTree);
        printElementsInTree(rTree);
        printTimeLog(start, end);
    }

    { 
        std::cout << "C3 - Construção da árvore com 70 elementos - RTree(2, 4)" << std::endl;
        auto start = std::chrono::high_resolution_clock::now();

        RTree rTree(2, 4, new QuadraticSplitStrategy());
        rTree.insert(new Rectangle(0.0, 40.0, 0.0, 35.0));
        rTree.insert(new Rectangle(10.0, 45.0, 210.0, 230.0));
        rTree.insert(new Rectangle(170.0, 200.0, 50.0, 150.0));
        rTree.insert(new Rectangle(75.0, 125.0, 110.0, 125.0));
        rTree.insert(new Rectangle(50.0, 65.0, 130.0, 160.0));
        rTree.insert(new Rectangle(15.0, 30.0, 140.0, 150.0));
        rTree.insert(new Rectangle(100.0, 130.0, 50.0, 90.0));
        rTree.insert(new Rectangle(150.0, 155.0, 40.0, 60.0));
        rTree.insert(new Rectangle(52.0, 75.0, 80.0, 90.0));
        rTree.insert(new Rectangle(62.0, 85.0, 65.0, 75.0));
        rTree.insert(new Rectangle(20.0, 25.0, 75.0, 80.0));
        rTree.insert(new Rectangle(30.0, 50.0, 40.0, 80.0));
        rTree.insert(new Rectangle(102.0, 113.0, 155.0, 217.0));
        rTree.insert(new Rectangle(163.0, 272.0, 169.0, 264.0));
        rTree.insert(new Rectangle(303.0, 360.0, 80.0, 144.0));
        rTree.insert(new Rectangle(351.0, 385.0, 68.0, 90.0));
        rTree.insert(new Rectangle(355.0, 373.0, 111.0, 131.0));
        rTree.insert(new Rectangle(365.0, 388.0, 183.0, 204.0));
        rTree.insert(new Rectangle(373.0, 396.0, 235.0, 250.0));
        rTree.insert(new Rectangle(368.0, 388.0, 261.0, 282.0));
        rTree.insert(new Rectangle(379.0, 411.0, 295.0, 317.0));
        rTree.insert(new Rectangle(426.0, 438.0, 260.0, 271.0));
        rTree.insert(new Rectangle(447.0, 494.0, 204.0, 235.0));
        rTree.insert(new Rectangle(485.0, 519.0, 183.0, 208.0));
        rTree.insert(new Rectangle(518.0, 560.0, 106.0, 140.0));
        rTree.insert(new Rectangle(505.0, 559.0, 97.0, 135.0));
        rTree.insert(new Rectangle(481.0, 540.0, 21.0, 66.0));
        rTree.insert(new Rectangle(517.0, 590.0, 16.0, 47.0));
        rTree.insert(new Rectangle(573.0, 594.0, 242.0, 263.0));
        rTree.insert(new Rectangle(594.0, 629.0, 208.0, 243.0));
        rTree.insert(new Rectangle(584.0, 653.0, 161.0, 206.0));
        rTree.insert(new Rectangle(583.0, 613.0, 327.0, 335.0));
        rTree.insert(new Rectangle(629.0, 651.0, 297.0, 313.0));
        rTree.insert(new Rectangle(660.0, 691.0, 288.0, 309.0));
        rTree.insert(new Rectangle(696.0, 712.0, 262.0, 281.0));
        rTree.insert(new Rectangle(208.0, 257.0, 322.0, 347.0));
        rTree.insert(new Rectangle(319.0, 390.0, 332.0, 376.0));
        rTree.insert(new Rectangle(277.0, 320.0, 399.0, 422.0));
        rTree.insert(new Rectangle(251.0, 280.0, 367.0, 385.0));
        rTree.insert(new Rectangle(152.0, 185.0, 377.0, 395.0));
        rTree.insert(new Rectangle(142.0, 173.0, 399.0, 412.0));
        rTree.insert(new Rectangle(95.0, 121.0, 351.0, 360.0));
        rTree.insert(new Rectangle(99.0, 122.0, 303.0, 315.0));
        rTree.insert(new Rectangle(103.0, 151.0, 264.0, 293.0));
        rTree.insert(new Rectangle(245.0, 274.0, 278.0, 293.0));
        rTree.insert(new Rectangle(481.0, 514.0, 358.0, 382.0));
        rTree.insert(new Rectangle(516.0, 534.0, 314.0, 326.0));
        rTree.insert(new Rectangle(518.0, 533.0, 297.0, 301.0));
        rTree.insert(new Rectangle(577.0, 595.0, 363.0, 373.0));
        rTree.insert(new Rectangle(650.0, 669.0, 390.0, 406.0));
        rTree.insert(new Rectangle(669.0, 684.0, 354.0, 363.0));
        rTree.insert(new Rectangle(655.0, 671.0, 362.0, 372.0));
        rTree.insert(new Rectangle(663.0, 682.0, 92.0, 108.0));
        rTree.insert(new Rectangle(654.0, 683.0, 36.0, 51.0));
        rTree.insert(new Rectangle(611.0, 640.0, 351.0, 368.0));
        rTree.insert(new Rectangle(667.0, 686.0, 271.0, 281.0));
        rTree.insert(new Rectangle(728.0, 758.0, 197.0, 210.0));
        rTree.insert(new Rectangle(804.0, 841.0, 178.0, 219.0));
        rTree.insert(new Rectangle(888.0, 906.0, 237.0, 260.0));
        rTree.insert(new Rectangle(926.0, 944.0, 319.0, 340.0));
        rTree.insert(new Rectangle(960.0, 968.0, 366.0, 377.0));
        rTree.insert(new Rectangle(974.0, 981.0, 405.0, 418.0));
        rTree.insert(new Rectangle(936.0, 946.0, 443.0, 454.0));
        rTree.insert(new Rectangle(826.0, 834.0, 457.0, 467.0));
        rTree.insert(new Rectangle(739.0, 751.0, 470.0, 476.0));
        rTree.insert(new Rectangle(694.0, 696.0, 470.0, 476.0));
        rTree.insert(new Rectangle(596.0, 598.0, 474.0, 478.0));
        rTree.insert(new Rectangle(492.0, 514.0, 472.0, 487.0));
        rTree.insert(new Rectangle(445.0, 446.0, 474.0, 478.0));
        rTree.insert(new Rectangle(354.0, 363.0, 476.0, 482.0));

        auto end = std::chrono::high_resolution_clock::now();
        printTreeHeight(rTree);
        printElementsInTree(rTree);
        printTimeLog(start, end);
    }

    { 
        std::cout << "C4 - Construção da árvore com 50 elementos - RTree(1, 4)" << std::endl;
        auto start = std::chrono::high_resolution_clock::now();

        RTree rTree(1, 4, new QuadraticSplitStrategy());

        rTree.insert(new Rectangle(0.0, 40.0, 0.0, 35.0));
        rTree.insert(new Rectangle(10.0, 45.0, 210.0, 230.0));
        rTree.insert(new Rectangle(170.0, 200.0, 50.0, 150.0));
        rTree.insert(new Rectangle(75.0, 125.0, 110.0, 125.0));
        rTree.insert(new Rectangle(50.0, 65.0, 130.0, 160.0));
        rTree.insert(new Rectangle(15.0, 30.0, 140.0, 150.0));
        rTree.insert(new Rectangle(100.0, 130.0, 50.0, 90.0));
        rTree.insert(new Rectangle(150.0, 155.0, 40.0, 60.0));
        rTree.insert(new Rectangle(52.0, 75.0, 80.0, 90.0));
        rTree.insert(new Rectangle(62.0, 85.0, 65.0, 75.0));
        rTree.insert(new Rectangle(20.0, 25.0, 75.0, 80.0));
        rTree.insert(new Rectangle(30.0, 50.0, 40.0, 80.0));
        rTree.insert(new Rectangle(102.0, 113.0, 155.0, 217.0));
        rTree.insert(new Rectangle(163.0, 272.0, 169.0, 264.0));
        rTree.insert(new Rectangle(303.0, 360.0, 80.0, 144.0));
        rTree.insert(new Rectangle(351.0, 385.0, 68.0, 90.0));
        rTree.insert(new Rectangle(355.0, 373.0, 111.0, 131.0));
        rTree.insert(new Rectangle(365.0, 388.0, 183.0, 204.0));
        rTree.insert(new Rectangle(373.0, 396.0, 235.0, 250.0));
        rTree.insert(new Rectangle(368.0, 388.0, 261.0, 282.0));
        rTree.insert(new Rectangle(379.0, 411.0, 295.0, 317.0));
        rTree.insert(new Rectangle(426.0, 438.0, 260.0, 271.0));
        rTree.insert(new Rectangle(447.0, 494.0, 204.0, 235.0));
        rTree.insert(new Rectangle(485.0, 519.0, 183.0, 208.0));
        rTree.insert(new Rectangle(518.0, 560.0, 106.0, 140.0));
        rTree.insert(new Rectangle(505.0, 559.0, 97.0, 135.0));
        rTree.insert(new Rectangle(481.0, 540.0, 21.0, 66.0));
        rTree.insert(new Rectangle(517.0, 590.0, 16.0, 47.0));
        rTree.insert(new Rectangle(573.0, 594.0, 242.0, 263.0));
        rTree.insert(new Rectangle(594.0, 629.0, 208.0, 243.0));
        rTree.insert(new Rectangle(584.0, 653.0, 161.0, 206.0));
        rTree.insert(new Rectangle(583.0, 613.0, 327.0, 335.0));
        rTree.insert(new Rectangle(629.0, 651.0, 297.0, 313.0));
        rTree.insert(new Rectangle(660.0, 691.0, 288.0, 309.0));
        rTree.insert(new Rectangle(696.0, 712.0, 262.0, 281.0));
        rTree.insert(new Rectangle(208.0, 257.0, 322.0, 347.0));
        rTree.insert(new Rectangle(319.0, 390.0, 332.0, 376.0));
        rTree.insert(new Rectangle(277.0, 320.0, 399.0, 422.0));
        rTree.insert(new Rectangle(251.0, 280.0, 367.0, 385.0));
        rTree.insert(new Rectangle(152.0, 185.0, 377.0, 395.0));
        rTree.insert(new Rectangle(142.0, 173.0, 399.0, 412.0));
        rTree.insert(new Rectangle(95.0, 121.0, 351.0, 360.0));
        rTree.insert(new Rectangle(99.0, 122.0, 303.0, 315.0));
        rTree.insert(new Rectangle(103.0, 151.0, 264.0, 293.0));
        rTree.insert(new Rectangle(245.0, 274.0, 278.0, 293.0));
        rTree.insert(new Rectangle(481.0, 514.0, 358.0, 382.0));
        rTree.insert(new Rectangle(516.0, 534.0, 314.0, 326.0));
        rTree.insert(new Rectangle(518.0, 533.0, 297.0, 301.0));
        rTree.insert(new Rectangle(577.0, 595.0, 363.0, 373.0));
        rTree.insert(new Rectangle(650.0, 669.0, 390.0, 406.0));

        auto end = std::chrono::high_resolution_clock::now();
        printTreeHeight(rTree);
        printElementsInTree(rTree);
        printTimeLog(start, end);
    }

    { 
        std::cout << "C5 - Construção da árvore com 50 elementos - RTree(3, 6)" << std::endl;
        auto start = std::chrono::high_resolution_clock::now();

        RTree rTree(3, 6, new QuadraticSplitStrategy());

        rTree.insert(new Rectangle(0.0, 40.0, 0.0, 35.0));
        rTree.insert(new Rectangle(10.0, 45.0, 210.0, 230.0));
        rTree.insert(new Rectangle(170.0, 200.0, 50.0, 150.0));
        rTree.insert(new Rectangle(75.0, 125.0, 110.0, 125.0));
        rTree.insert(new Rectangle(50.0, 65.0, 130.0, 160.0));
        rTree.insert(new Rectangle(15.0, 30.0, 140.0, 150.0));
        rTree.insert(new Rectangle(100.0, 130.0, 50.0, 90.0));
        rTree.insert(new Rectangle(150.0, 155.0, 40.0, 60.0));
        rTree.insert(new Rectangle(52.0, 75.0, 80.0, 90.0));
        rTree.insert(new Rectangle(62.0, 85.0, 65.0, 75.0));
        rTree.insert(new Rectangle(20.0, 25.0, 75.0, 80.0));
        rTree.insert(new Rectangle(30.0, 50.0, 40.0, 80.0));
        rTree.insert(new Rectangle(102.0, 113.0, 155.0, 217.0));
        rTree.insert(new Rectangle(163.0, 272.0, 169.0, 264.0));
        rTree.insert(new Rectangle(303.0, 360.0, 80.0, 144.0));
        rTree.insert(new Rectangle(351.0, 385.0, 68.0, 90.0));
        rTree.insert(new Rectangle(355.0, 373.0, 111.0, 131.0));
        rTree.insert(new Rectangle(365.0, 388.0, 183.0, 204.0));
        rTree.insert(new Rectangle(373.0, 396.0, 235.0, 250.0));
        rTree.insert(new Rectangle(368.0, 388.0, 261.0, 282.0));
        rTree.insert(new Rectangle(379.0, 411.0, 295.0, 317.0));
        rTree.insert(new Rectangle(426.0, 438.0, 260.0, 271.0));
        rTree.insert(new Rectangle(447.0, 494.0, 204.0, 235.0));
        rTree.insert(new Rectangle(485.0, 519.0, 183.0, 208.0));
        rTree.insert(new Rectangle(518.0, 560.0, 106.0, 140.0));
        rTree.insert(new Rectangle(505.0, 559.0, 97.0, 135.0));
        rTree.insert(new Rectangle(481.0, 540.0, 21.0, 66.0));
        rTree.insert(new Rectangle(517.0, 590.0, 16.0, 47.0));
        rTree.insert(new Rectangle(573.0, 594.0, 242.0, 263.0));
        rTree.insert(new Rectangle(594.0, 629.0, 208.0, 243.0));
        rTree.insert(new Rectangle(584.0, 653.0, 161.0, 206.0));
        rTree.insert(new Rectangle(583.0, 613.0, 327.0, 335.0));
        rTree.insert(new Rectangle(629.0, 651.0, 297.0, 313.0));
        rTree.insert(new Rectangle(660.0, 691.0, 288.0, 309.0));
        rTree.insert(new Rectangle(696.0, 712.0, 262.0, 281.0));
        rTree.insert(new Rectangle(208.0, 257.0, 322.0, 347.0));
        rTree.insert(new Rectangle(319.0, 390.0, 332.0, 376.0));
        rTree.insert(new Rectangle(277.0, 320.0, 399.0, 422.0));
        rTree.insert(new Rectangle(251.0, 280.0, 367.0, 385.0));
        rTree.insert(new Rectangle(152.0, 185.0, 377.0, 395.0));
        rTree.insert(new Rectangle(142.0, 173.0, 399.0, 412.0));
        rTree.insert(new Rectangle(95.0, 121.0, 351.0, 360.0));
        rTree.insert(new Rectangle(99.0, 122.0, 303.0, 315.0));
        rTree.insert(new Rectangle(103.0, 151.0, 264.0, 293.0));
        rTree.insert(new Rectangle(245.0, 274.0, 278.0, 293.0));
        rTree.insert(new Rectangle(481.0, 514.0, 358.0, 382.0));
        rTree.insert(new Rectangle(516.0, 534.0, 314.0, 326.0));
        rTree.insert(new Rectangle(518.0, 533.0, 297.0, 301.0));
        rTree.insert(new Rectangle(577.0, 595.0, 363.0, 373.0));
        rTree.insert(new Rectangle(650.0, 669.0, 390.0, 406.0));

        auto end = std::chrono::high_resolution_clock::now();
        printTreeHeight(rTree);
        printElementsInTree(rTree);
        printTimeLog(start, end);
    }

    { 
        std::cout << "C6 - Construção da árvore com 70 elementos - RTree(4, 8)" << std::endl;
        auto start = std::chrono::high_resolution_clock::now();

        RTree rTree(4, 8, new QuadraticSplitStrategy());
        rTree.insert(new Rectangle(0.0, 40.0, 0.0, 35.0));
        rTree.insert(new Rectangle(10.0, 45.0, 210.0, 230.0));
        rTree.insert(new Rectangle(170.0, 200.0, 50.0, 150.0));
        rTree.insert(new Rectangle(75.0, 125.0, 110.0, 125.0));
        rTree.insert(new Rectangle(50.0, 65.0, 130.0, 160.0));
        rTree.insert(new Rectangle(15.0, 30.0, 140.0, 150.0));
        rTree.insert(new Rectangle(100.0, 130.0, 50.0, 90.0));
        rTree.insert(new Rectangle(150.0, 155.0, 40.0, 60.0));
        rTree.insert(new Rectangle(52.0, 75.0, 80.0, 90.0));
        rTree.insert(new Rectangle(62.0, 85.0, 65.0, 75.0));
        rTree.insert(new Rectangle(20.0, 25.0, 75.0, 80.0));
        rTree.insert(new Rectangle(30.0, 50.0, 40.0, 80.0));
        rTree.insert(new Rectangle(102.0, 113.0, 155.0, 217.0));
        rTree.insert(new Rectangle(163.0, 272.0, 169.0, 264.0));
        rTree.insert(new Rectangle(303.0, 360.0, 80.0, 144.0));
        rTree.insert(new Rectangle(351.0, 385.0, 68.0, 90.0));
        rTree.insert(new Rectangle(355.0, 373.0, 111.0, 131.0));
        rTree.insert(new Rectangle(365.0, 388.0, 183.0, 204.0));
        rTree.insert(new Rectangle(373.0, 396.0, 235.0, 250.0));
        rTree.insert(new Rectangle(368.0, 388.0, 261.0, 282.0));
        rTree.insert(new Rectangle(379.0, 411.0, 295.0, 317.0));
        rTree.insert(new Rectangle(426.0, 438.0, 260.0, 271.0));
        rTree.insert(new Rectangle(447.0, 494.0, 204.0, 235.0));
        rTree.insert(new Rectangle(485.0, 519.0, 183.0, 208.0));
        rTree.insert(new Rectangle(518.0, 560.0, 106.0, 140.0));
        rTree.insert(new Rectangle(505.0, 559.0, 97.0, 135.0));
        rTree.insert(new Rectangle(481.0, 540.0, 21.0, 66.0));
        rTree.insert(new Rectangle(517.0, 590.0, 16.0, 47.0));
        rTree.insert(new Rectangle(573.0, 594.0, 242.0, 263.0));
        rTree.insert(new Rectangle(594.0, 629.0, 208.0, 243.0));
        rTree.insert(new Rectangle(584.0, 653.0, 161.0, 206.0));
        rTree.insert(new Rectangle(583.0, 613.0, 327.0, 335.0));
        rTree.insert(new Rectangle(629.0, 651.0, 297.0, 313.0));
        rTree.insert(new Rectangle(660.0, 691.0, 288.0, 309.0));
        rTree.insert(new Rectangle(696.0, 712.0, 262.0, 281.0));
        rTree.insert(new Rectangle(208.0, 257.0, 322.0, 347.0));
        rTree.insert(new Rectangle(319.0, 390.0, 332.0, 376.0));
        rTree.insert(new Rectangle(277.0, 320.0, 399.0, 422.0));
        rTree.insert(new Rectangle(251.0, 280.0, 367.0, 385.0));
        rTree.insert(new Rectangle(152.0, 185.0, 377.0, 395.0));
        rTree.insert(new Rectangle(142.0, 173.0, 399.0, 412.0));
        rTree.insert(new Rectangle(95.0, 121.0, 351.0, 360.0));
        rTree.insert(new Rectangle(99.0, 122.0, 303.0, 315.0));
        rTree.insert(new Rectangle(103.0, 151.0, 264.0, 293.0));
        rTree.insert(new Rectangle(245.0, 274.0, 278.0, 293.0));
        rTree.insert(new Rectangle(481.0, 514.0, 358.0, 382.0));
        rTree.insert(new Rectangle(516.0, 534.0, 314.0, 326.0));
        rTree.insert(new Rectangle(518.0, 533.0, 297.0, 301.0));
        rTree.insert(new Rectangle(577.0, 595.0, 363.0, 373.0));
        rTree.insert(new Rectangle(650.0, 669.0, 390.0, 406.0));
        rTree.insert(new Rectangle(669.0, 684.0, 354.0, 363.0));
        rTree.insert(new Rectangle(655.0, 671.0, 362.0, 372.0));
        rTree.insert(new Rectangle(663.0, 682.0, 92.0, 108.0));
        rTree.insert(new Rectangle(654.0, 683.0, 36.0, 51.0));
        rTree.insert(new Rectangle(611.0, 640.0, 351.0, 368.0));
        rTree.insert(new Rectangle(667.0, 686.0, 271.0, 281.0));
        rTree.insert(new Rectangle(728.0, 758.0, 197.0, 210.0));
        rTree.insert(new Rectangle(804.0, 841.0, 178.0, 219.0));
        rTree.insert(new Rectangle(888.0, 906.0, 237.0, 260.0));
        rTree.insert(new Rectangle(926.0, 944.0, 319.0, 340.0));
        rTree.insert(new Rectangle(960.0, 968.0, 366.0, 377.0));
        rTree.insert(new Rectangle(974.0, 981.0, 405.0, 418.0));
        rTree.insert(new Rectangle(936.0, 946.0, 443.0, 454.0));
        rTree.insert(new Rectangle(826.0, 834.0, 457.0, 467.0));
        rTree.insert(new Rectangle(739.0, 751.0, 470.0, 476.0));
        rTree.insert(new Rectangle(694.0, 696.0, 470.0, 476.0));
        rTree.insert(new Rectangle(596.0, 598.0, 474.0, 478.0));
        rTree.insert(new Rectangle(492.0, 514.0, 472.0, 487.0));
        rTree.insert(new Rectangle(445.0, 446.0, 474.0, 478.0));
        rTree.insert(new Rectangle(354.0, 363.0, 476.0, 482.0));

        auto end = std::chrono::high_resolution_clock::now();
        printTreeHeight(rTree);
        printElementsInTree(rTree);
        printTimeLog(start, end);
    }

    { 
        std::cout << "C7 - Construção da árvore com 70 elementos - RTree(1, 2)" << std::endl;
        auto start = std::chrono::high_resolution_clock::now();

        RTree rTree(1, 2, new QuadraticSplitStrategy());
        rTree.insert(new Rectangle(0.0, 40.0, 0.0, 35.0));
        rTree.insert(new Rectangle(10.0, 45.0, 210.0, 230.0));
        rTree.insert(new Rectangle(170.0, 200.0, 50.0, 150.0));
        rTree.insert(new Rectangle(75.0, 125.0, 110.0, 125.0));
        rTree.insert(new Rectangle(50.0, 65.0, 130.0, 160.0));
        rTree.insert(new Rectangle(15.0, 30.0, 140.0, 150.0));
        rTree.insert(new Rectangle(100.0, 130.0, 50.0, 90.0));
        rTree.insert(new Rectangle(150.0, 155.0, 40.0, 60.0));
        rTree.insert(new Rectangle(52.0, 75.0, 80.0, 90.0));
        rTree.insert(new Rectangle(62.0, 85.0, 65.0, 75.0));
        rTree.insert(new Rectangle(20.0, 25.0, 75.0, 80.0));
        rTree.insert(new Rectangle(30.0, 50.0, 40.0, 80.0));
        rTree.insert(new Rectangle(102.0, 113.0, 155.0, 217.0));
        rTree.insert(new Rectangle(163.0, 272.0, 169.0, 264.0));
        rTree.insert(new Rectangle(303.0, 360.0, 80.0, 144.0));
        rTree.insert(new Rectangle(351.0, 385.0, 68.0, 90.0));
        rTree.insert(new Rectangle(355.0, 373.0, 111.0, 131.0));
        rTree.insert(new Rectangle(365.0, 388.0, 183.0, 204.0));
        rTree.insert(new Rectangle(373.0, 396.0, 235.0, 250.0));
        rTree.insert(new Rectangle(368.0, 388.0, 261.0, 282.0));
        rTree.insert(new Rectangle(379.0, 411.0, 295.0, 317.0));
        rTree.insert(new Rectangle(426.0, 438.0, 260.0, 271.0));
        rTree.insert(new Rectangle(447.0, 494.0, 204.0, 235.0));
        rTree.insert(new Rectangle(485.0, 519.0, 183.0, 208.0));
        rTree.insert(new Rectangle(518.0, 560.0, 106.0, 140.0));
        rTree.insert(new Rectangle(505.0, 559.0, 97.0, 135.0));
        rTree.insert(new Rectangle(481.0, 540.0, 21.0, 66.0));
        rTree.insert(new Rectangle(517.0, 590.0, 16.0, 47.0));
        rTree.insert(new Rectangle(573.0, 594.0, 242.0, 263.0));
        rTree.insert(new Rectangle(594.0, 629.0, 208.0, 243.0));
        rTree.insert(new Rectangle(584.0, 653.0, 161.0, 206.0));
        rTree.insert(new Rectangle(583.0, 613.0, 327.0, 335.0));
        rTree.insert(new Rectangle(629.0, 651.0, 297.0, 313.0));
        rTree.insert(new Rectangle(660.0, 691.0, 288.0, 309.0));
        rTree.insert(new Rectangle(696.0, 712.0, 262.0, 281.0));
        rTree.insert(new Rectangle(208.0, 257.0, 322.0, 347.0));
        rTree.insert(new Rectangle(319.0, 390.0, 332.0, 376.0));
        rTree.insert(new Rectangle(277.0, 320.0, 399.0, 422.0));
        rTree.insert(new Rectangle(251.0, 280.0, 367.0, 385.0));
        rTree.insert(new Rectangle(152.0, 185.0, 377.0, 395.0));
        rTree.insert(new Rectangle(142.0, 173.0, 399.0, 412.0));
        rTree.insert(new Rectangle(95.0, 121.0, 351.0, 360.0));
        rTree.insert(new Rectangle(99.0, 122.0, 303.0, 315.0));
        rTree.insert(new Rectangle(103.0, 151.0, 264.0, 293.0));
        rTree.insert(new Rectangle(245.0, 274.0, 278.0, 293.0));
        rTree.insert(new Rectangle(481.0, 514.0, 358.0, 382.0));
        rTree.insert(new Rectangle(516.0, 534.0, 314.0, 326.0));
        rTree.insert(new Rectangle(518.0, 533.0, 297.0, 301.0));
        rTree.insert(new Rectangle(577.0, 595.0, 363.0, 373.0));
        rTree.insert(new Rectangle(650.0, 669.0, 390.0, 406.0));
        rTree.insert(new Rectangle(669.0, 684.0, 354.0, 363.0));
        rTree.insert(new Rectangle(655.0, 671.0, 362.0, 372.0));
        rTree.insert(new Rectangle(663.0, 682.0, 92.0, 108.0));
        rTree.insert(new Rectangle(654.0, 683.0, 36.0, 51.0));
        rTree.insert(new Rectangle(611.0, 640.0, 351.0, 368.0));
        rTree.insert(new Rectangle(667.0, 686.0, 271.0, 281.0));
        rTree.insert(new Rectangle(728.0, 758.0, 197.0, 210.0));
        rTree.insert(new Rectangle(804.0, 841.0, 178.0, 219.0));
        rTree.insert(new Rectangle(888.0, 906.0, 237.0, 260.0));
        rTree.insert(new Rectangle(926.0, 944.0, 319.0, 340.0));
        rTree.insert(new Rectangle(960.0, 968.0, 366.0, 377.0));
        rTree.insert(new Rectangle(974.0, 981.0, 405.0, 418.0));
        rTree.insert(new Rectangle(936.0, 946.0, 443.0, 454.0));
        rTree.insert(new Rectangle(826.0, 834.0, 457.0, 467.0));
        rTree.insert(new Rectangle(739.0, 751.0, 470.0, 476.0));
        rTree.insert(new Rectangle(694.0, 696.0, 470.0, 476.0));
        rTree.insert(new Rectangle(596.0, 598.0, 474.0, 478.0));
        rTree.insert(new Rectangle(492.0, 514.0, 472.0, 487.0));
        rTree.insert(new Rectangle(445.0, 446.0, 474.0, 478.0));
        rTree.insert(new Rectangle(354.0, 363.0, 476.0, 482.0));

        auto end = std::chrono::high_resolution_clock::now();
        printTreeHeight(rTree);
        printElementsInTree(rTree);
        printTimeLog(start, end);
    }
}
