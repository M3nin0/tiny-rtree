#include <cstddef>

#include "geometry.hpp"
#include "rtree.hpp"
#include <algorithm>
#include <iostream>
#include <limits>
#include <stdlib.h>

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

RNode* RNode::parent() const
{
    return p_parent;
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

        if ( areaGain < maxGainArea )
        {
            selectedNode = node;
            maxGainArea = areaGain;
        }
    }

    return ChooseLeaf(selectedNode, newRect);
}

void AdjustTree(RNode* root, RNode* N, RNode* NN)
{
    if (N == root)
        return;



    // Necessita do Split para testar
    // RNode* en = new RNode();
    // en->p_m = root->p_m;
    // en->p_M = root->p_M;
    // en->p

}

std::vector<RNode*> QuadraticPickSeeds(RNode* root)
{
    double d = std::numeric_limits<double>::min();
    RNode* wrongE1, *wrongE2;

    // Buscando o pior par
    for(auto e1: root->children())
    {
        for(auto e2: root->children())
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

RNode* QuadraticPickNext(std::vector<RNode*>& children, RNode* groupOne, RNode* groupTwo)
{
    std::size_t indexOfSelectedNode = -1; // Para auxiliar a remoção do elemento selecionado
    RNode* nodeWithMaxDifference = nullptr;
    double maxDifference = std::numeric_limits<double>::min();

    for(std::size_t i = 0; i < children.size(); ++i)
    {
        RNode* entry = children.at(i);

        // Calculando a diferença do ganho de área em cada grupo
        // em seguida, determina se a diferença (Colocada como absoluta para evitar erros)
        // é a máxima, caso seja, salva o nó
        double gainGroupOne = AreaGain(groupOne->mbr(), entry->mbr());
        double gainGroupTwo = AreaGain(groupTwo->mbr(), entry->mbr());
        double difference = std::abs(gainGroupOne - gainGroupTwo);

        if (difference > maxDifference)
        {
            indexOfSelectedNode = i;
            maxDifference = difference;
            nodeWithMaxDifference = entry;
        }
    }
    children.erase(children.begin() + indexOfSelectedNode);
    return nodeWithMaxDifference;
}


// ToDo: Trocar esta função
// Método feito APENAS PARA TESTE
// O Código é MUITO RUIM E NÃO CONSOME A API DO C++ corretamente
bool ElementIsInAVector(std::vector<RNode*>& vec, RNode* el)
{
    for(auto vEl: vec)
    {
        if (vEl == el)
            return true;
    }
    return false;
}

/**
 * Este método faz o split utilizando o QuadraticSplit. No estado atual do método
 * ainda não é feito o 'balanceamento' para verificar a quantidade de elementos em cada um dos
 * grupos e se os mesmos possuem o mínimo necessário para o funcionamento, tal operação será
 * revisitada mais tarde.
 */
std::vector<RNode*> QuadraticSplit(RNode* root)
{
    // Cria os dois novos grupos
    RNode* groupOne = new RNode();
    RNode* groupTwo = new RNode();

    // Encontrando o pior par para ficarem separados    
    std::vector<RNode*> wrongSeeds = QuadraticPickSeeds(root);

    groupOne->insert(wrongSeeds.at(0));
    groupTwo->insert(wrongSeeds.at(1));
    std::vector<RNode*> children = root->children();
 
    // Percorrendo todos os elementos para inserir os mesmos dentro de cada um dos grupos criados
    while (!children.empty()) // Com isto, estou garantindo que todos os elementos serão percorridos.
    {
        RNode* nextEntry = QuadraticPickNext(children, groupOne, groupTwo);
    
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
            std::size_t g1Size = groupOne->children().size();
            std::size_t g2Size = groupTwo->children().size();
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
        std::vector<RNode*> vec = selectedGroup->children();
        if (!ElementIsInAVector(vec, nextEntry))
            selectedGroup->insert(nextEntry);
    }

    return std::vector<RNode*> ({ groupOne, groupTwo });
}

void RTree::insert(BaseRectangle* rect)
{
    RNode* newRNode = new RNode(p_m, p_M);
    newRNode->addMBR(rect);

    RNode* L = ChooseLeaf(root, rect);
    RNode* LL = nullptr; // separando espaço para L e LL
    std::cout << L << std::endl;

    if (L->isFull())
    {
        // L->insert(newRNode);
        //l->

        std::vector<RNode*> nAndNN = QuadraticSplit(L);
        // Define L e LL como sendo os novos nós, gerados através do split
        L = nAndNN.at(0);
        LL = nAndNN.at(1);
    }
    else
        L->insert(newRNode);
    
    // AdjustTree deve vir aqui
    AdjustTree(root, L, LL);
}
