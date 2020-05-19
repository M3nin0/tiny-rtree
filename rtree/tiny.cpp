#include "tiny.hpp"
#include <cstddef>
#include <algorithm>

RNode::RNode()
{
}

RNode::RNode(bool isLeaf)
    : p_isLeaf(isLeaf)
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
    return p_isLeaf;
}

bool RNode::setIsLeaf(bool isLeaf)
{
    p_isLeaf = isLeaf;
}

bool RNode::isFullOfChildren() const
{
    return p_children.size() == p_M;
}

void RNode::addChildren(RNode* child)
{
    child->p_parent = this; // Criando a associação entre os nós
    p_children.push_back(child);
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

void RNode::updateMBR_()
{
    BaseRectangle* b = p_children.at(0)->mbr();
    for(std::size_t i = 1; i <= p_children.size(); ++i)
    {
        b = RectangleAppend(b, p_children.at(i)->mbr());
    }

    p_mbr = b;
}

RNode* RNode::chooseLeaf_(RNode* N, BaseRectangle* newRect)
{
    if (N->isLeaf())
        return N;

    RNode* selectedNode = N;
    double maxGainArea = AreaGain(N->mbr(), newRect);

    // Buscando o nó que possuí o menor crescimento do MBR
    for(auto node: N->p_children)
    {
        double areaGain = AreaGain(node->mbr(), newRect);

        if ( areaGain < maxGainArea )
        {
            selectedNode = node;
            maxGainArea = areaGain;
        }

        if (areaGain == maxGainArea)
        {
            // caso seja igual, o problema será resolvido escolhendo o retângulo
            // de menor área
            double actualNodeArea = RectangleArea(selectedNode->mbr());
            double possibleNodeArea = RectangleArea(node->mbr());

            if (actualNodeArea > possibleNodeArea)
            {
                maxGainArea = areaGain;
                selectedNode = node;
            }
        }
    }
    // Realiza a operação até os nós folhas
    return chooseLeaf_(selectedNode, newRect);
}

std::vector<RNode*> RNode::quadraticPickSeeds_(std::vector<RNode*>& vec)
{
    RNode* wrongE1, *wrongE2;
    double d = std::numeric_limits<double>::min();

    // Buscando o pior par
    for(auto e1: vec)
    {
        for(auto e2: vec)
        {
            if (e1 != e2)
            {
                BaseRectangle* j = RectangleAppend(e1->mbr(), e2->mbr());
                double dFor = RectangleArea(j) - RectangleArea(e1->mbr()) - RectangleArea(e2->mbr());

                if (dFor > d)
                {
                    d = dFor;
                    wrongE1 = e1;
                    wrongE2 = e2;
                }
            }
        }
    }
    
    return std::vector<RNode*>({wrongE1, wrongE2});
}

RNode* RNode::quadraticPickNext_(std::vector<RNode*>& children, RNode* groupOne, RNode* groupTwo)
{

}

bool ElementIsInAVector(std::vector<RNode*>& vec, RNode* el)
{
    for(auto vEl: vec)
    {
        if (vEl == el)
            return true;
    }
    return false;
}

std::vector<RNode*> RNode::quadraticSplit_(std::vector<RNode*>& children)
{
    // Cria os dois novos grupos
    RNode* groupOne = new RNode();
    RNode* groupTwo = new RNode();

    // Encontrando o pior par para separar eles    
    std::vector<RNode*> wrongSeeds = quadraticPickSeeds_(children);

    groupOne->addChildren(wrongSeeds.at(0));
    groupTwo->addChildren(wrongSeeds.at(1));

    while (!children.empty())
    {
        // QS2 (Verificando se acabou)
        for(auto group: {groupOne, groupTwo})
        {
            // Verificando se algum dos grupos pode ficar sem a quantidade mínima de
            // elementos necessárias pela definição da árvore
            // "A quantidade de nós atuais no grupo consegue alcançar o mínimo quando somada
            // a quantidade de elementos que estão disponíveis para utilização"
            std::size_t elSize = (group->p_children.size() + children.size());
            if (elSize <= group->p_m)
            {
                for(std::size_t inode = 1; group->p_m <= elSize; inode++)
                {
                    group->addChildren(children.at(inode));
                    children.erase(children.begin() + inode);
                }
            }
        }

        RNode* nextEntry = quadraticPickNext_(children, groupOne, groupTwo);
    
        double areaGainG1 = AreaGain(groupOne->mbr(), nextEntry->mbr());
        double areaGainG2 = AreaGain(groupTwo->mbr(), nextEntry->mbr());

        // Seleciona o grupo que possuí o menor ganho de área
        // para inserir o elemento E
        RNode* selectedGroup;
        if (areaGainG1 > areaGainG2)
            selectedGroup = groupTwo;
        else if (areaGainG2 > areaGainG1)
            selectedGroup = groupOne;
        else if (areaGainG1 == areaGainG2)
        {
            // Se o ganho de área for igual, é preciso de uma forma de desempate
            // 1° - Quantidade de elementos no grupo
            std::size_t g1Size = groupOne->p_children.size();
            std::size_t g2Size = groupTwo->p_children.size();
            if (g1Size != g2Size)
            {
                // Verifica os tamanhos de cada grupo
                if (g1Size > g2Size)
                    selectedGroup = groupTwo;
                else if (g2Size > g1Size)
                    selectedGroup = groupOne;
            } else {
                // 2° Adiciona em qualquer grupo (Random)
                std::size_t groupIndex = rand() % 2 + 1;

                if (groupIndex == 1)
                    selectedGroup = groupOne;
                else
                    selectedGroup = groupTwo;
            }
        }
        // Insere no grupo selecionado com base nos critérios definidos no artigo
        if (!ElementIsInAVector(selectedGroup->p_children, nextEntry))
            selectedGroup->addChildren(nextEntry);
    }

    return std::vector<RNode*> ({ groupOne, groupTwo });
}

void RNode::insert_(RNode* nn)
{
    RNode* L = chooseLeaf_(this, nn->mbr());

    // Se está cheio não pode inserir NN, precisa realizar a operação de split
    if (L->isFullOfChildren())
    {
        L->addChildren(nn);
        std::vector<RNode*> LandLL = quadraticSplit_(L->p_children);

    } else
    {
        L->addChildren(nn);
    }
    updateMBR_();
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
    nn->setIsLeaf(true); // mover para o construtor

    root->insert_(nn);
}
