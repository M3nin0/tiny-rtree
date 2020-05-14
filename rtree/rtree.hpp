#ifndef __RTREE_HEADER__
#define __RTREE_HEADER__

#include <vector>
#include <cstddef>
#include "geometry.hpp"

class RNode
{
public:
    RNode();
    RNode(std::size_t m, std::size_t M);
    RNode(std::size_t m, std::size_t M, RNode* parent);
    RNode(std::size_t m, std::size_t M, RNode* parent, bool isLeaf);

    // Métodos temporários
    BaseRectangle* mbr(); // talvez esse não seja temporário
    void insert(RNode* nrnode);
    void setLeaf(bool isLeaf);
    void addMBR(BaseRectangle* mbr);

    bool isFull() const;
    bool isLeaf() const;
    std::vector<RNode*> children() const;
private:
    bool p_isleaf = false;
    std::size_t p_m, p_M;
    std::size_t p_size = 0;
    BaseRectangle *p_mbr = nullptr;

    RNode* p_parent = nullptr;
    std::vector<RNode*> p_children;

    void UpdateMBR(BaseRectangle* nBaseRectangle);
};

class RTree
{
public:
    RTree(std::size_t m, std::size_t M);

    // Esta parte, posteriormente, será substituída por uma
    // classe mais genérica, possibilitando a inserção de qualquer geometria
    // que tenha disponível um método do tipo `envelope` ou similar
    void insert(BaseRectangle* rect);
private:
    std::size_t p_m, p_M;

    RNode* root;
};

#endif
