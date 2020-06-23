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
friend class RTree;

// Construtores
public:
    RNode(std::size_t m, std::size_t M, bool isLeaf, SplitStrategy* splitStrategy);

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
    RNode* parent() const;
    std::size_t m() const;
    std::size_t M() const;
    SplitStrategy* strategy() const;
    std::vector<RNode*>& children();

    bool isLeaf() const;
    void setIsLeaf(bool isLeaf);
    bool isFullOfChildren() const;

// Características do nó
private:
    std::size_t p_height;
    std::size_t p_m, p_M;
    bool p_isLeaf;
    SplitStrategy* p_splitStrategy;
    DimensionalRectangle2D* p_mbr;

// Parentesco
private:
    RNode* p_parent;
    std::vector<RNode*> p_children;

private:
    void updateMBR_();
    void print_(RNode* root);
    RNode* insert_(RNode* nn);
};

/**
 * DESCRIPTION: Representação da RTree no código. Responsável pelo facade das inserções e o
 * controle das estruturas
 */
class RTree
{

// Construtores
public:
    RTree(std::size_t m, std::size_t M, SplitStrategy* splitStrategy);

// Métodos para o controle da estrutura da árvore
public:
    static RNode* adjustTree(RNode* root, RNode* N, RNode* NN);
    static RNode* chooseLeaf(RNode* N, DimensionalRectangle2D* ngeom);

public:
    void print() const;
    std::size_t count() const;
    std::size_t height() const;
    void insert(Geometry* geom);
    std::vector<RNode*> search(Geometry* geom) const;

private:
    int count(RNode* root) const;
    void search_(RNode* root, DimensionalRectangle2D* geom, std::vector<RNode*>& overlaps_) const;

private:
    RNode *p_root;
    std::size_t p_m, p_M;
};

#endif
