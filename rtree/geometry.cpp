#include <vector>
#include <array>
#include <algorithm>
#include <stdexcept>

#include "geometry.hpp"

DimensionalRectangle2D::DimensionalRectangle2D(double xmin, double xmax, double ymin, double ymax)
    : p_xmin(xmin), p_xmax(xmax), p_ymin(ymin), p_ymax(ymax)
{
}

double DimensionalRectangle2D::min(std::size_t axis)
{
    if (axis == 0)
        return p_xmin;
    else if (axis == 1)
        return p_ymin;
    throw std::domain_error("Dimensão inválida");
}

double DimensionalRectangle2D::max(std::size_t axis)
{
    if (axis == 0)
        return p_xmax;
    else if (axis == 1)
        return p_ymax;
    throw std::domain_error("Dimensão inválida!");
}

double DimensionalRectangleAlgebra::RectangleArea(DimensionalRectangle2D* dimSpace)
{
    // Calculando a área
    double base = dimSpace->max(0) - dimSpace->min(0); // x
    double height = dimSpace->max(1) - dimSpace->min(1); // y

    return base * height;
}

DimensionalRectangle2D* DimensionalRectangleAlgebra::DimensionAppend(DimensionalRectangle2D* rect1, 
                                                                        DimensionalRectangle2D* rect2)
{
    std::array<double, 4> xs({ rect1->min(0), rect2->min(0), rect1->max(0), rect2->max(0) });
    std::array<double, 4> ys({ rect1->min(1), rect2->min(1), rect1->max(1), rect2->max(1) });

    // Encontrando os novos mínimos e máximos dos retângulos
    // O que gera novo espaço retangular
    // Isso remove aquele monte de 'if' da versão 0.1
    double xmin = *std::min_element(xs.begin(), xs.end());
    double xmax = *std::max_element(xs.begin(), xs.end());
    double ymin = *std::min_element(ys.begin(), ys.end());
    double ymax = *std::max_element(ys.begin(), ys.end());

    return new DimensionalRectangle2D(
        xmin, xmax, ymin, ymax
    );
}

double DimensionalRectangleAlgebra::AreaGain(DimensionalRectangle2D* actualSpace, DimensionalRectangle2D* newReact)
{
    // Criar novo espaço para entender o quanto cresceu
    DimensionalRectangle2D* newSpace = DimensionAppend(actualSpace, newReact);

    double actualSpaceArea = RectangleArea(actualSpace);
    double gainSpaceArea = RectangleArea(newSpace);

    return gainSpaceArea - actualSpaceArea;
}

int DimensionalRectangleAlgebra::Overlaps(DimensionalRectangle2D* rect1, DimensionalRectangle2D* rect2)
{
    // Verificando em intervalos em X e Y
    // bool overlapsInX = (rect2->min(0) >= rect1->min(0) && rect2->min(0) <= rect1->max(0)) ||
    //                   (rect2->max(0) >= rect1->min(0) && rect2->max(0) <= rect1->max(0));
    // bool overlapsInY = (rect2->min(1) >= rect1->min(1) && rect2->min(1) <= rect1->max(1)) ||
    //                   (rect2->max(1) >= rect1->min(1) && rect2->max(1) <= rect1->max(1));
    // return overlapsInX && overlapsInY;
    
    // Mapear os casos por intervalo estava causando problemas na busca.
    // Então, seguindo as ideias vistas na aula de kd-tree do Gilberto ("Filtrar pelo que não é")
    // Na versão 0.5 o código que mapeava o que era estava sendo usado, mas nos testes com mais dados
    // problemas começaram a aparecer, por isso a mudança foi realizada.
    bool overlapsInX = (rect1->min(0) > rect2->max(0) || rect2->min(0) > rect1->max(0));
    bool overlapsInY = (rect1->min(1) > rect2->max(1) || rect2->min(1) > rect1->max(1));

    return !(overlapsInX || overlapsInY);
}
