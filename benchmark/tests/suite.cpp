#include "../../rtree/tree.hpp"
#include "../../rtree/split.hpp"
#include "../../rtree/geometry.hpp"

#include <chrono>
#include <iostream>

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

    std::cout << (finalTime - initialTime) << std::endl;
}

int main()
{
    { // Utilizando o ciclo de vida de objetos em C++
        std::cout << "C1 - Construção da árvore com 10 elementos" << std::endl;

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
        printTimeLog(start, end);
    }

    { 
        std::cout << "C2 - Construção da árvore com 50 elementos" << std::endl;
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
        printTimeLog(start, end);
    }

    { 
        std::cout << "C3 - Construção da árvore com 124 elementos" << std::endl;
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
        rTree.insert(new Rectangle(270.0, 293.0, 461.0, 482.0));
        rTree.insert(new Rectangle(191.0, 203.0, 446.0, 461.0));
        rTree.insert(new Rectangle(133.0, 138.0, 447.0, 454.0));
        rTree.insert(new Rectangle(478.0, 542.0, 375.0, 402.0));
        rTree.insert(new Rectangle(607.0, 638.0, 341.0, 355.0));
        rTree.insert(new Rectangle(711.0, 742.0, 287.0, 303.0));
        rTree.insert(new Rectangle(781.0, 819.0, 232.0, 251.0));
        rTree.insert(new Rectangle(859.0, 891.0, 159.0, 166.0));
        rTree.insert(new Rectangle(903.0, 914.0, 95.0, 99.0));
        rTree.insert(new Rectangle(928.0, 952.0, 69.0, 87.0));
        rTree.insert(new Rectangle(880.0, 893.0, 45.0, 76.0));
        rTree.insert(new Rectangle(798.0, 808.0, 84.0, 105.0));
        rTree.insert(new Rectangle(733.0, 747.0, 94.0, 103.0));
        rTree.insert(new Rectangle(694.0, 746.0, 117.0, 161.0));
        rTree.insert(new Rectangle(569.0, 577.0, 247.0, 260.0));
        rTree.insert(new Rectangle(446.0, 468.0, 249.0, 264.0));
        rTree.insert(new Rectangle(415.0, 443.0, 192.0, 213.0));
        rTree.insert(new Rectangle(442.0, 465.0, 188.0, 203.0));
        rTree.insert(new Rectangle(342.0, 364.0, 110.0, 128.0));
        rTree.insert(new Rectangle(273.0, 287.0, 55.0, 64.0));
        rTree.insert(new Rectangle(200.0, 237.0, 25.0, 50.0));
        rTree.insert(new Rectangle(191.0, 225.0, 67.0, 110.0));
        rTree.insert(new Rectangle(233.0, 254.0, 199.0, 228.0));
        rTree.insert(new Rectangle(149.0, 157.0, 312.0, 334.0));
        rTree.insert(new Rectangle(96.0, 99.0, 337.0, 361.0));
        rTree.insert(new Rectangle(60.0, 65.0, 375.0, 404.0));
        rTree.insert(new Rectangle(55.0, 135.0, 406.0, 460.0));
        rTree.insert(new Rectangle(128.0, 167.0, 460.0, 480.0));
        rTree.insert(new Rectangle(325.0, 400.0, 179.0, 217.0));
        rTree.insert(new Rectangle(440.0, 476.0, 200.0, 231.0));
        rTree.insert(new Rectangle(502.0, 523.0, 238.0, 281.0));
        rTree.insert(new Rectangle(558.0, 578.0, 297.0, 312.0));
        rTree.insert(new Rectangle(621.0, 649.0, 325.0, 338.0));
        rTree.insert(new Rectangle(687.0, 712.0, 357.0, 368.0));
        rTree.insert(new Rectangle(747.0, 778.0, 377.0, 389.0));
        rTree.insert(new Rectangle(819.0, 838.0, 401.0, 412.0));
        rTree.insert(new Rectangle(890.0, 995.0, 427.0, 463.0));
        rTree.insert(new Rectangle(990.0, 1013.0, 126.0, 146.0));
        rTree.insert(new Rectangle(1000.0, 1017.0, 101.0, 116.0));
        rTree.insert(new Rectangle(1010.0, 1043.0, 67.0, 84.0));
        rTree.insert(new Rectangle(1019.0, 1046.0, 52.0, 70.0));
        rTree.insert(new Rectangle(1009.0, 1036.0, 321.0, 336.0));
        rTree.insert(new Rectangle(1011.0, 1029.0, 325.0, 357.0));
        rTree.insert(new Rectangle(962.0, 992.0, 294.0, 348.0));
        rTree.insert(new Rectangle(838.0, 884.0, 318.0, 362.0));
        rTree.insert(new Rectangle(802.0, 841.0, 304.0, 337.0));
        rTree.insert(new Rectangle(744.0, 804.0, 295.0, 327.0));
        rTree.insert(new Rectangle(682.0, 745.0, 273.0, 321.0));
        rTree.insert(new Rectangle(631.0, 676.0, 268.0, 309.0));
        rTree.insert(new Rectangle(572.0, 619.0, 252.0, 284.0));
        rTree.insert(new Rectangle(553.0, 644.0, 211.0, 260.0));
        rTree.insert(new Rectangle(581.0, 672.0, 199.0, 268.0));
        rTree.insert(new Rectangle(512.0, 602.0, 169.0, 221.0));
        rTree.insert(new Rectangle(454.0, 572.0, 127.0, 182.0));

        auto end = std::chrono::high_resolution_clock::now();
        printTimeLog(start, end);
    }

    return 0;
}
