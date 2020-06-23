#include <cstddef>
#include <iostream>
#include <algorithm>

#include "SplitStrategy.hpp"
#include "split.hpp"

#include "tree.hpp"

RTree::RTree(std::size_t m, std::size_t M, SplitStrategy* splitStrategy)
    : p_m(m), p_M(M)
{
    p_root = new RNode(m, M, true, splitStrategy);
    p_root->p_height = 0; // Só para a raiz que isso é válido
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

void RNode::addParent(RNode* parent)
{
    p_parent = parent;
}

DimensionalRectangle2D* RNode::mbr() const
{
    return p_mbr;
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
    return p_children.size() == p_M;
}

void RNode::addChild(RNode* child)
{
    child->p_parent = this;
    p_children.push_back(child);

    updateMBR_(); // evita que o método "mbr" fique recalculando
                  // como era feito na versão 0.4
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
RNode* RTree::chooseLeaf(RNode* N, DimensionalRectangle2D* ngeom)
{
    // N no parâmetro representa CL1
    // CL2
    if (N->isLeaf())
        return N;

    // Precisa ser nulo, na versão 0.1 era selectedNode = N (O que gerou problemas e 'ifs' extras)
    RNode* selectedNode = nullptr;
    // pega um elemento fora do domínio para começar (Isso aqui é tipo a representação do infinito no livro do Ziviane)
    double maxGainArea = std::numeric_limits<double>::max(); 

    // CL3 (Buscando o nó que possuí o menor crescimento do MBR)
    for(auto node: N->children())
    {
        double areaGain = DimensionalRectangleAlgebra::AreaGain(node->mbr(), ngeom);

        if (areaGain == maxGainArea)
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

        if ( areaGain < maxGainArea)
        {
            selectedNode = node;
            maxGainArea = areaGain;
        }
    }

    // Realiza a operação até os nós folhas
    return chooseLeaf(selectedNode, ngeom);
}

/**
 * DESCRIPTION: Função auxiliar para o ajuste da estrutura da árvore após uma inserção (Com ou sem split)
 * 
 * OBSERVATION: Implementação do algoritmo de ajuste (Bottom-Up) proposto por Guttman (1984). Na lógica original do artigo, ao que parece, esta função não precisa
 * retornar nenhum valor, porém, seguindo a estrutura de implementação deste código, inicialmente nenhum valor era retornado
 * o que causava problemas de perdas dos nós, uma vez que o split era realizado e então não era adicionado ao
 * nó final
 */
RNode* RTree::adjustTree(RNode* root, RNode* N, RNode* NN)
{
    if(N == root)
        return NN;

    RNode* p = N->parent();
    RNode* pp = nullptr;
    
    // AT3. Para cada filho em p, fazer sua atualização
    // (Essa parte, mais que qualquer outra parte do código, foi muito empírico, eu não conseguia entender
    // o que o guttman queria dizer, até que quando fiz dessa forma, as coisas fizeram mais sentido, no funcionamento
    // e entendimento do artigo)
    // O que estou fazendo é atualizar o MBR de cada filho e depois do pai
    for(auto ppt: p->p_children)
        ppt->updateMBR_();
    p->updateMBR_(); // nos testes não fez diferença, mas não consigo mapear todos os casos

    if (NN != nullptr)
    {
        // Se o pai não estiver cheio de filhos, adiciona o NN
        if (!p->isFullOfChildren())
            p->addChild(NN);
            // Aqui só o P é considerado, PP vai entrar no adjustTree como null
        else
        {
            // Para o split, a estratégia presente no nó é utilizada
            p->addChild(NN);
            std::vector<RNode*> PAndPP = root->p_splitStrategy->split(p);

            // salva os resultados em P e PP para que o adjustTree seja utilizado
            p = PAndPP.at(0);
            pp = PAndPP.at(1);
        }
    }
    // AT4. Propaga a divisão dos nós para cima
    return adjustTree(root, p, pp); 
}

/**
 * DESCRIPTION: Método para a inserção de elementos no nó
 * 
 * OBSERVATION: Os passos implementados neste método são descritos em Guttman (1984).
 */
RNode* RNode::insert_(RNode* nn)
{
    RNode* secondNode = nullptr;
    RNode* L = RTree::chooseLeaf(this, nn->mbr());

    // Se está cheio não pode inserir NN, precisa realizar a operação de split
    // Os dois casos chamam o "adjustTree", isto é feito para que os elementos alterados
    // tenham seu MBR atualizado e se necessário a realização do split
    if (L->isFullOfChildren())
    {
        L->addChild(nn);
        std::vector<RNode*> LAndLL = p_splitStrategy->split(L);
        secondNode = RTree::adjustTree(this, LAndLL.at(0), LAndLL.at(1));
    } else
    {
        L->addChild(nn);
        secondNode = RTree::adjustTree(this, L, nullptr);
    }
    
    if (secondNode != nullptr)
    {
        RNode* newRoot = new RNode(p_m, p_M, false, this->p_splitStrategy); 
        // Com o entendimento do funcionamento percebi que a cada split que ocorre na raiz
        // o nível da árvore aumenta. Então, para controlar sua altura o que fiz foi, toda vez
        // que o split chega na raiz é contado 1, indicando que a altura da árvore subiu.
        // Fiz os testes e parece estar consistente.
        newRoot->p_height = this->p_height + 1;

        newRoot->addChild(this);
        newRoot->addChild(secondNode);
        return newRoot;
    }

    return this;
}

/**
 * DESCRIPTION: Mecanismo para contar a quantidade de elementos que está disponível na árvore.
 */
int RTree::count(RNode *root) const
{
    if (root->isLeaf()) // Ponto de parada da recursão
    {
        int elementsInLeaf = 0;
        for(std::size_t i = 0; i < root->children().size(); ++i)
        {
            elementsInLeaf += 1;
        }
        return elementsInLeaf;
    }

    int result = 0;
    for(std::size_t i = 0; i < root->children().size(); ++i)
    {
        result += count(root->children().at(i));
    }
    return result;
}


/**
 * DESCRIPTION: Método para buscar os retângulos que sobrepõem o retângulo em questão
 */
void RTree::search_(RNode* root, DimensionalRectangle2D* geom, std::vector<RNode*>& overlaps_) const
{
    // S2. Busca nos nós folha (Buscando nos conteúdos)
    if(root->isLeaf())
    {
        for(std::size_t i = 0; i < root->children().size(); ++i) // vou passar por todos os elementos do vector e imprimir o mbr de cada um
        {
            if(DimensionalRectangleAlgebra::Overlaps(root->children().at(i)->mbr(), geom)) // vendo se os retângulos das entradas sobrepõem o que eu to buscando
                overlaps_.push_back(root->children().at(i)); // se sim, adiciona num vector pra armazenar
        }
    }
    // S1. Busca nas subárvores (Buscando nos intermediários)
    // Se não é uma folha, verifica cada uma das entradas do nó e determina se este sobrepõe S
    else
    {
        for(auto node: root->children())
        {
            // Para todas as entradas que sobrepoe S, chama o search
            if (DimensionalRectangleAlgebra::Overlaps(node->mbr(), geom))
                search_(node, geom, overlaps_);
        }
    }
    // Da forma abaixo, acredito que todos os elementos estavam sendo verificandos
    // for(std::size_t i=0; i<root->children().size(); ++i)
    //     return search_(root->children().at(i), geom, overlaps_); 
}

std::vector<RNode*> RTree::search(Geometry* geom) const
{
    std::vector<RNode*> result;
    search_(p_root, geom->mbr(), result);

    return result;
}

/**
 * DESCRIPTION: Mecanismo para imprimir os nós da árvore
 */
void RNode::print_(RNode* root)
{
    if(root->isLeaf()) // Se é folha busca só nos elementos  (Buscando nos conteúdos)
    {
        for(std::size_t i=0; i<root->children().size(); ++i)
        {
            std::cout << root->children().at(i)->mbr()->min(0) << "\t";
            std::cout << root->children().at(i)->mbr()->max(0) << "\t";
            std::cout << root->children().at(i)->mbr()->min(1) << "\t";
            std::cout << root->children().at(i)->mbr()->max(1) << std::endl;
        }
    }
    else
    {
        for(auto node: root->children())
        {
            print_(node);
        }
    }
}

/**
 * DESCRIPTION: Função para contar a quantidade de elementos que está disponível na árvore.
 */
std::size_t RTree::count() const
{
    return count(p_root);
}

/**
 * DESCRIPTION: Altura da árvore
 */
std::size_t RTree::height() const
{
    return p_root->p_height;
}
