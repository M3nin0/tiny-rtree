#include "tiny.hpp"
#include <cstddef>
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

void RNode::addMBR(BaseRectangle* mbr)
{
    p_mbr = mbr;
}

bool RNode::isLeaf() const
{
    return p_children.empty();
}

BaseRectangle* RNode::mbr() const
{
    if (isLeaf())
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

void RNode::updateMBR_(BaseRectangle* nBaseRectangle)
{
    p_mbr = RectangleAppend(p_mbr, nBaseRectangle);
}

RNode* RNode::chooseLeaf_(RNode* root, BaseRectangle* newRect)
{

}

std::vector<RNode*> RNode::quadraticPickSeeds_(std::vector<RNode*>& vec)
{

}

RNode* RNode::quadraticPickNext_(std::vector<RNode*>& children, RNode* groupOne, RNode* groupTwo)
{

}

std::vector<RNode*> RNode::quadraticSplit_(std::vector<RNode*>& children)
{

}

void RNode::insert_(RNode* nn)
{
    RNode* L = chooseLeaf_(this, nn->mbr());

}

/**
 * Definição da classe e operações da RTree propriamente dita
*/
RTree::RTree(std::size_t m, std::size_t M)
    : p_m(m), p_M(M)
{
    root = new RNode(m, M, nullptr);
}

void RTree::insert(BaseRectangle* rect)
{
    RNode* nn = new RNode(p_m, p_M, nullptr);
    nn->addMBR(rect);

    root->insert_(nn);
}
