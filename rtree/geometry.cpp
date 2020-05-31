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

// Retorna (dimensão minima, dimensão máxima)
// std::array<double, 2> axis(std::size_t ax);

double DimensionalRectangleAlgebra::RectangleArea(DimensionalRectangle2D* dimSpace)
{
    // Calculando a área
    double base = dimSpace->max(0) - dimSpace->max(0);
    double height = dimSpace->max(1) - dimSpace->min(1);

    return base * height;
}

DimensionalRectangle2D* DimensionalRectangleAlgebra::DimensionAppend(DimensionalRectangle2D* rect1, 
                                                                        DimensionalRectangle2D* rect2)
{
    std::array<double, 4> xs({ rect1->min(0), rect2->min(0), rect1->max(0), rect2->max(0) });
    std::array<double, 4> ys({ rect1->min(1), rect2->min(1), rect1->max(1), rect2->max(1) });

    // Encontrando os novos mínimos e máximos dos retângulos
    // O que gera novo espaço retangular
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
