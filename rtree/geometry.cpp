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
