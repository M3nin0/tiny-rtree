#ifndef __RTREE_HEADER__
#define __RTREE_HEADER__

#include <vector>
#include <cstddef>

#include "geometry.hpp"
#include "SplitStrategy.hpp"

/**
 * Representação de um nó da RTree. Esta classe é uma 
 * generalização dos nós apresentados por Guttman (1984)
 */
class RNode
{

// Construtores
public:
    // Definir de acordo com a necessidade e depois
    // generalizar
    // ToDo: Colocar no construtor verificação da relação m <= M/2
    // ToDo: Adicionar estratégia de split
    // RNode();
    RNode(std::size_t m, std::size_t M, SplitStrategy* splitStrategy);

// Manipulação de parentesco
public:
    void addChild(RNode* child);
    void addParent(RNode* parent);

// Manipulação geométrica
public:
    DimensionalRectangle2D* mbr() const;
    void addMBR(DimensionalRectangle2D* mbr);

// Status/Características do nó
public:
    std::size_t m() const;
    std::size_t M() const;
    SplitStrategy* strategy() const;
    std::vector<RNode*> children() const;

    bool isLeaf() const;
    void setIsLeaf(bool isLeaf);
    bool isFullOfChildren() const;

// Características do nó
private:
    bool p_isLeaf;
    std::size_t p_m, p_M;
    SplitStrategy* p_splitStrategy;
    DimensionalRectangle2D* p_mbr;

// Parentesco
private:
    RNode* p_parent;
    std::vector<RNode*> p_children;
    
private:
    void updateMBR_();
    void insert_(RNode* nn);
};

class RTree
{
public:
    RTree(std::size_t m, std::size_t M);
};

#endif
