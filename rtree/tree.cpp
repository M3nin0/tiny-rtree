#include <cstddef>
#include <algorithm>

#include "tree.hpp"
#include "geometry.hpp"

RNode::RNode(std::size_t m, std::size_t M, SplitStrategy* splitStrategy)
    : p_m(m), p_M(M), p_splitStrategy(splitStrategy)
{
}

void RNode::addMBR(DimensionalRectangle2D* mbr)
{
    p_mbr = mbr;
}

DimensionalRectangle2D* RNode::mbr() const
{
    if (p_isLeaf)
        return p_mbr;

    std::vector<double> xs;
    std::vector<double> ys;

    for(auto node: p_children)
    {
        xs.push_back(node->mbr()->min(0)); // x
        xs.push_back(node->mbr()->min(1)); // y
        xs.push_back(node->mbr()->max(0)); // x
        xs.push_back(node->mbr()->max(1)); // y
    }

    // Seleciona as maiores e menores coordenadas
    double xmin = *std::min_element(xs.begin(), xs.end());
    double xmax = *std::max_element(xs.begin(), xs.end());
    double ymin = *std::min_element(ys.begin(), ys.end());
    double ymax = *std::max_element(ys.begin(), ys.end());

    return new DimensionalRectangle2D(
        xmin, xmax, ymin, ymax
    );
}

void RNode::updateMBR_()
{
    DimensionalRectangle2D* base = p_children.at(0)->mbr();

    for(std::size_t i = 0; i < p_children.size(); ++i)
    {
        base = DimensionalRectangleAlgebra::DimensionAppend(base, p_children.at(i)->mbr());
    }
    p_mbr = base;
}

bool RNode::isLeaf() const 
{
    return p_isLeaf;
}

void RNode::setIsLeaf(bool isLeaf)
{
    p_isLeaf = isLeaf;
}

bool RNode::isFullOfChildren() const
{
    return p_children.size() >= p_M;
}

void RNode::addChild(RNode* child)
{
    child->p_parent = this;
    p_children.push_back(child);

    updateMBR_();
}

std::size_t RNode::m() const
{
    return p_m;
}

std::size_t RNode::M() const
{
    return p_M;
}

std::vector<RNode*> RNode::children() const
{
    return p_children;
}

SplitStrategy* RNode::strategy() const
{
    return p_splitStrategy;
}
