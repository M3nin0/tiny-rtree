#include <cstddef>

#include "geometry.hpp"
#include "rtree.hpp"
#include <algorithm>

RNode::RNode()
{
}

RNode::RNode(std::size_t m, std::size_t M)
    : p_m(m), p_M(M)
{
}

RNode::RNode(std::size_t m, std::size_t M, RNode* parent)
    : p_m(m), p_M(M), p_parent(parent)
{
}

RNode::RNode(std::size_t m, std::size_t M, RNode* parent, bool isLeaf)
    : p_m(m), p_M(M), p_parent(parent), p_isleaf(isLeaf)
{
}

void RNode::setLeaf(bool isLeaf)
{
    p_isleaf = isLeaf;
}

void RNode::insert(RNode* nrnode)
{
    nrnode->p_parent = nrnode; // definindo o pai
    p_children.push_back(nrnode);
}

BaseRectangle* RNode::mbr()
{
    if (p_isleaf)
        return p_mbr;

    // encontrando os valores mínimos de x e y
    // forma mais simples =D
    std::vector<double> xs;
    std::vector<double> ys;

    for(auto node: p_children)
    {
        xs.push_back(node->mbr()->xmin());
        xs.push_back(node->mbr()->xmax());
        ys.push_back(node->mbr()->ymin());
        ys.push_back(node->mbr()->ymax());
    }

    // selecionado os maiores e menores
    double xmin = *std::min_element(xs.begin(), xs.end());
    double xmax = *std::max_element(xs.begin(), xs.end());
    double ymin = *std::min_element(ys.begin(), ys.end());
    double ymax = *std::max_element(ys.begin(), ys.end());

    return new BaseRectangle(
        xmin, xmax, ymin, ymax
    );
}

void RNode::addMBR(BaseRectangle* mbr)
{
    p_mbr = mbr;
}
