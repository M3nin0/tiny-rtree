#include <vector>
#include <algorithm>
#include "geometry.hpp"

BaseRectangle::BaseRectangle(double xmin, double xmax, double ymin, double ymax)
    : p_xmin(xmin), p_xmax(xmax), p_ymin(ymin), p_ymax(ymax)
{
}

double BaseRectangle::xmin() const
{
    return p_xmin;
}

double BaseRectangle::xmax() const
{
    return p_xmax;
}

double BaseRectangle::ymin() const
{
    return p_ymin;
}

double BaseRectangle::ymax() const
{
    return p_ymax;
}

double RectangleArea(BaseRectangle* rect)
{
    // Calculando a área
    double base = rect->xmax() - rect->xmin();
    double height = rect->ymax() - rect->ymin();

    return base * height;
}

BaseRectangle* RectangleAppend(BaseRectangle* rect1, BaseRectangle* rect2)
{
    std::vector<double> xs({ rect1->xmin(), rect2->xmin(), rect1->xmax(), rect2->xmax() });
    std::vector<double> ys({ rect1->ymin(), rect2->ymin(), rect1->ymax(), rect2->ymax() });

    double xmin = *std::min_element(xs.begin(), xs.end());
    double xmax = *std::max_element(xs.begin(), xs.end());
    double ymin = *std::min_element(ys.begin(), ys.end());
    double ymax = *std::max_element(ys.begin(), ys.end());
    
    return new BaseRectangle(
        xmin, xmax, ymin, ymax
    );
}

double AreaGain(BaseRectangle* space, BaseRectangle* newReact)
{
    // Criar novo espaço para entender o quanto cresceu
    BaseRectangle* newSpace = RectangleAppend(space, newReact);

    double actualSpaceArea = RectangleArea(space);
    double gainSpaceArea = RectangleArea(newSpace);

    return gainSpaceArea - actualSpaceArea;
}
