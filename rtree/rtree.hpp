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
    BaseRectangle* mbr();
    void insert(RNode* nrnode);
    void setLeaf(bool isLeaf);

    void addMBR(BaseRectangle* mbr);
private:
    bool p_isleaf = false;
    std::size_t p_m, p_M;
    BaseRectangle *p_mbr = nullptr;

    RNode* p_parent;
    std::vector<RNode*> p_children;
};

#endif
