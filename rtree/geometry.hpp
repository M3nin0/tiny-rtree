#ifndef __GEOMETRY_HEADER__
#define __GEOMETRY_HEADER__

#include <array>
#include <cstddef>

struct DimensionalRectangle2D
{
public:
    DimensionalRectangle2D(double xmin, double xmax, double ymin, double ymax);

    double min(std::size_t axis);
    double max(std::size_t axis);

    // Retorna (dimensão minima, dimensão máxima)
    std::array<double, 2> axis(std::size_t ax);
private:
    double p_xmin, p_xmax, p_ymin, p_ymax;
};


class DimensionalRectangleAlgebra
{
public:

    /**
     * Método estático para cálculo de área de uma dimensão retangular
     */
    static double RectangleArea(DimensionalRectangle2D* rect);
    
    /**
     * Método para calcular o ganho de área que uma dimensão retangular terá ao adicionar um novo
     * retângulo em sua composição
     */
    static double AreaGain(DimensionalRectangle2D* actualSpace, DimensionalRectangle2D* newReact);
    
    /**
     * Método para juntar duas dimensões retangulares
     */
    static DimensionalRectangle2D* DimensionAppend(DimensionalRectangle2D* dim1, DimensionalRectangle2D* dim2);
};

/**
 * Classe genérica de geometria
 */
class Geometry
{
public:

    /**
     * Método criado para a geração de MBR de geometrias 2D
     * 
     * OBS: Método polimórfico criado para a possibilidade de generalização das geometrias
     * tratadas na árvore
     */
    virtual DimensionalRectangle2D*  mbr() = 0; // Indicando que esta estrutura é polimórfica
};

/**
 * Representação da geometria de retângulo. Por ser uma especialização da classe Geometry,
 * pertence ao conjunto de objetos que podem ser utilizados na RTree desenvolvida
 */
class Rectangle: public Geometry
{
public:
    Rectangle(double xmin, double xmax, double ymin, double ymax)
        : p_xmin(xmin), p_xmax(xmax), p_ymin(ymin), p_ymax(ymax)
    {
    }

private:
    double p_xmin, p_xmax, p_ymin, p_ymax;

public:
    virtual DimensionalRectangle2D* mbr()
    {
        return new DimensionalRectangle2D{p_xmin, p_xmax, p_ymin, p_ymax};
    }
};

#endif
