#ifndef __GEOMETRY_HEADER__
#define __GEOMETRY_HEADER__

class BaseRectangle
{
public:
    BaseRectangle(double xmin, double xmax, double ymin, double ymax);

    double xmin() const;
    double xmax() const;
    double ymin() const;
    double ymax() const;
private:
    double p_xmin, p_xmax, p_ymin, p_ymax;
};

class DefinedGeometry
{
public:
    virtual BaseRectangle* envelope() = 0;
};

class DefinedPoint
{
public:
    DefinedPoint(double x, double y);

    double x();
    double y();

    BaseRectangle* envelope();
private:
    double p_x, p_y;
};

class DefinedRectangle
{
public:
    DefinedRectangle(double xmin, double xmax, double ymin, double ymax);
    
    double xmin();
    double xmax();
    double ymin();
    double ymax();

    BaseRectangle* envelope();
private:
    double p_xmin, p_xmax, p_ymin, p_ymax;
};

double RectangleArea(BaseRectangle* rect);
double AreaGain(BaseRectangle* space, BaseRectangle* newReact);

#endif
