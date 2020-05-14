#include <cstddef>

#include "geometry.hpp"
#include "rtree.hpp"
#include <algorithm>
#include <iostream>

/**
 * Definição da classe e operações de nó
 */
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
    p_size += 1;
    nrnode->p_parent = nrnode; // definindo o pai
    p_children.push_back(nrnode);

    if (p_mbr == nullptr)
    {
        p_mbr = nrnode->p_mbr;
    }

    // Atualiza o MBR do nó atual para que a mudança feita na inserção
    // reflita em todo o restante da árvore
    UpdateMBR(nrnode->p_mbr);
}

BaseRectangle* RNode::mbr()
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

void RNode::addMBR(BaseRectangle* mbr)
{
    p_mbr = mbr;
}

void RNode::UpdateMBR(BaseRectangle* nBaseRectangle)
{
    p_mbr = RectangleAppend(p_mbr, nBaseRectangle);
}

bool RNode::isLeaf() const
{
    // Quando chega ao máximo
    // entende-se que o nó deixa de ser uma folha, 
    // pois vai ser dividido.
    // Talvez o membro de dados p_isleaf pode ser utilizado
    // para representar de forma mais natural o crescimento da árvore
    return p_size <= p_M;
}

// Buscar entender a forma do "isEmpty()"
bool RNode::isFull() const
{
    // Alterado para >= para testes
    return p_children.size() >= p_M;
}

std::vector<RNode*> RNode::children() const
{
    return p_children;
}

/**
 * Definição da classe e operações da RTree propriamente dita
*/
RTree::RTree(std::size_t m, std::size_t M)
    : p_m(m), p_M(M)
{
    root = new RNode(m, M, nullptr);
}

RNode* ChooseLeaf(RNode* root, BaseRectangle* newRect)
{
    if (root->isLeaf())
        return root;

    RNode* selectedNode = root;
    double maxGainArea = AreaGain(root->mbr(), newRect);

    // Buscando o nó que possuí o menor crescimento do MBR
    for(auto node: root->children())
    {
        double areaGain = AreaGain(node->mbr(), newRect);

        if (areaGain < maxGainArea )
        {
            selectedNode = node;
            maxGainArea = areaGain;
        }
    }

    return ChooseLeaf(selectedNode, newRect);
}

void RNode::AdjustTree(RNode* root, RNode* N, RNode* NN)
{
    if (N == root)
        return;

    RNode* en = new RNode();
    en->p_m = root->p_m;
    en->p_M = root->p_M;
    // en->p

}


void RTree::insert(BaseRectangle* rect)
{
    RNode* newRNode = new RNode(p_m, p_M);
    newRNode->addMBR(rect);

    RNode* L = ChooseLeaf(root, rect);
    std::cout << L << std::endl;

    if (L->isFull())
        // SplitTree deve vir aqui...
        std::cout << "Tratar, o nó está cheio" << std::endl;
    else
        L->insert(newRNode);
    
    // AdjustTree deve vir aqui...
}
