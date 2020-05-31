#include <cstddef>
#include <algorithm>

#include "SplitStrategy.hpp"
#include "split.hpp"

#include "tree.hpp"

RTree::RTree(std::size_t m, std::size_t M, SplitStrategy* splitStrategy)
    : p_m(m), p_M(M)
{
    p_root = new RNode(m, M, true, splitStrategy);
}

void RTree::insert(Geometry* geom)
{
    RNode* nn = new RNode(p_m, p_M, true, p_root->strategy());
    nn->addMBR(geom->mbr()); // ToDo: Generalizar o armazenamento do nó

    p_root = p_root->insert_(nn);
}


RNode::RNode(std::size_t m, std::size_t M, bool isLeaf, SplitStrategy* splitStrategy)
    : p_m(m), p_M(M), p_isLeaf(isLeaf), p_splitStrategy(splitStrategy)
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
        ys.push_back(node->mbr()->min(1)); // y
        xs.push_back(node->mbr()->max(0)); // x
        ys.push_back(node->mbr()->max(1)); // y
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

std::vector<RNode*>& RNode::children()
{
    return p_children;
}

SplitStrategy* RNode::strategy() const
{
    return p_splitStrategy;
}

RNode* RNode::parent() const
{
    return p_parent;
}

/**
 * DESCRIPTION: Função auxiliar para a seleção do nó onde os novos elements serão inseridos
 * 
 * OBSERVATION: Os passos implementados nesta função, representam os passos { CL1, CL2, CL3 e CL4 }
 * descrito no artigo de Guttman (1984).
 */
RNode* RNodeAdjuster::chooseLeaf(RNode* N, DimensionalRectangle2D* ngeom)
{
    // N no parâmetro representa CL1
    // CL2
    if (N->isLeaf())
        return N;

    RNode* selectedNode = N;
    // pega um elemento fora do domínio para começar
    double maxGainArea = std::numeric_limits<double>::max(); 

    // CL3 (Buscando o nó que possuí o menor crescimento do MBR)
    for(auto node: N->children())
    {
        double areaGain = DimensionalRectangleAlgebra::AreaGain(node->mbr(), ngeom);

        if ( areaGain < maxGainArea && !node->isLeaf() )
        {
            selectedNode = node;
            maxGainArea = areaGain;
        }

        if (areaGain == maxGainArea && !node->isLeaf())
        {
            // caso seja igual, o problema será resolvido escolhendo o retângulo
            // de menor área, como apresentado no CL3
            double possibleNodeArea = DimensionalRectangleAlgebra::RectangleArea(node->mbr());
            double actualNodeArea = DimensionalRectangleAlgebra::RectangleArea(selectedNode->mbr());

            if (actualNodeArea > possibleNodeArea)
            {
                maxGainArea = areaGain;
                selectedNode = node;
            }
        }
    }

    // Adicionado para verificar se o nó de entrada sofreu mudanças.
    // Caso não tenha sofrido, indica que a busca está sendo feita no nível
    // das folhas, assim, o elemento N (Superior) deve ser devolvido.
    if (selectedNode == N)
        return N;

    // Realiza a operação até os nós folhas
    return chooseLeaf(selectedNode, ngeom);
}

/**
 * 
 */
void RNodeAdjuster::adjustTree(RNode* root, RNode* N, RNode* NN)
{
    if(N == root)
        return;

    RNode* pParent = N->parent();
    pParent->updateMBR_();

    if (NN != nullptr)
    {
        // Se o pai não estiver cheio de filhos, adiciona o NN
        if (!pParent->isFullOfChildren())
        {
            pParent->addChild(NN);
            adjustTree(root, pParent, nullptr); // Não tem divisão, NN = nullprt
        }
        else
        {
            // Para o split, a estratégia presente no nó é utilizada
            std::vector<RNode*> PAndPP = root->p_splitStrategy->split(pParent);
            adjustTree(root, PAndPP.at(0), PAndPP.at(1));
        }
    }
}

/**
 * DESCRIPTION: Método para a inserção de elementos no nó
 * 
 * OBSERVATION: Os passos implementados neste método são descritos em Guttman (1984).
 */
RNode* RNode::insert_(RNode* nn)
{
    RNode* L = RNodeAdjuster::chooseLeaf(this, nn->mbr());

    // Se está cheio não pode inserir NN, precisa realizar a operação de split
    if (L->isFullOfChildren())
    {
        L->addChild(nn);

        std::vector<RNode*> LAndLL = p_splitStrategy->split(L);
        RNodeAdjuster::adjustTree(this, LAndLL.at(0), LAndLL.at(1));
        
        LAndLL.at(0)->setIsLeaf(LAndLL.at(0)->p_children.empty());
        LAndLL.at(1)->setIsLeaf(LAndLL.at(1)->p_children.empty());

        // Caso particular da raiz
        // Se for raiz, então, uma divisão é realizada
        if (L == this)
        {
            RNode* newRoot = new RNode(p_m, p_M, false, this->p_splitStrategy); 
            newRoot->addChild(LAndLL.at(0));
            newRoot->addChild(LAndLL.at(1));

            return newRoot;
        }
    } else
    {
        L->addChild(nn);
    }
    return this;
}
