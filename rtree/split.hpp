#ifndef __SPLIT_STRATEGY_HEADER__
#define __SPLIT_STRATEGY_HEADER__

#include <vector>
#include <stdexcept>

#include "tree.hpp"
#include "geometry.hpp"
#include "SplitStrategy.hpp"

class SplitStrategy
{
public:
    SplitStrategy() {  };

    std::vector<RNode*> split(RNode* L)
        {
            return split_(L);
        }
    
    std::vector<RNode*> pickSeeds(std::vector<RNode*>& vec)
    {
        return pickSeeds_(vec);
    }

    RNode* pickNext(std::vector<RNode*>& vec)
    {
        return pickNext_(vec);
    }

    RNode* pickNext(std::vector<RNode*>& children, RNode* groupOne, RNode* groupTwo)
    {
        return pickNext_(children, groupOne, groupTwo);
    }

private:
    virtual std::vector<RNode*> split_(RNode* L) = 0;
    virtual std::vector<RNode*> pickSeeds_(std::vector<RNode*>& vec) = 0;

    virtual RNode* pickNext_(std::vector<RNode*>& children) = 0;
    virtual RNode* pickNext_(std::vector<RNode*>& children, RNode* groupOne, RNode* groupTwo) = 0;
};

/**
 * Função auxiliar para buscar o maior elemento do lado mais baixo da dimensão selecionada.
 * Exemplo: Imagine um quadrado 2D, "Buscar o valor mais alto, do lado mais baixo" é buscar
 * o valor de xmin mais alto.
 * 
 * No artigo de Guttman (1984), esta busca é apresentada na regra LPS1
 */
RNode* selectHighestBass(std::vector<RNode*>& vec, std::size_t axis)
{
    RNode* selectedHighestBassNAxis = vec.front();

    for(auto node: vec)
    {
        if (selectedHighestBassNAxis->mbr()->min(axis) < node->mbr()->min(0))
            selectedHighestBassNAxis = node;
    }
    return selectedHighestBassNAxis;
}

/**
 * Função auxiliar para buscar o maior elemento do lado mais baixo da dimensão selecionada.
 * Exemplo: Imagine um quadrado 2D, "Buscar o valor mais baixo, do lado mais alto" é buscar
 * o valor de xmax menor.
 * 
 * No artigo de Guttman (1984), esta busca é apresentada na regra LPS1
 */
RNode* selectLowestHigh(std::vector<RNode*>& vec, std::size_t axis)
{
    RNode* selectedHighestBassNAxis = vec.front();
    for(auto node: vec)
    {
        if (selectedHighestBassNAxis->mbr()->max(axis) > node->mbr()->max(axis))
            selectedHighestBassNAxis = node;
    }
    return selectedHighestBassNAxis;
}

/**
 * Função auxiliar para a aplicação da normalização das dimensões filtradas da regra LPS1 do artigo
 * de Guttman (1984).
 * 
 * Esta função materializa a regra LPS2
 */
double normalizedDistanceNAxis(RNode* selectedLowestHigh, RNode* selectedHighestBass, std::size_t axis)
{
    DimensionalRectangle2D* selectedLowestHighMBR = selectedLowestHigh->mbr();
    DimensionalRectangle2D* selectedHighestBassMBR = selectedHighestBass->mbr();

    return (
        (selectedHighestBassMBR->max(axis) - selectedLowestHighMBR->min(axis))
        /
        (selectedHighestBassMBR->min(axis) + selectedLowestHighMBR->max(axis))
    );
}

/**
 * Método auxiliar para verificar se um elemento com uma certa referência
 * está presente no vector
 * 
 * ToDo: Melhorar
 */
bool elementsIsInVector(std::vector<RNode*> vecx, RNode* el)
{
    for(auto vEl: vecx)
    {
        if (vEl == el)
            return true;
    }
    return false;
}

class LinearSplitStrategy: public SplitStrategy
{
public:
    LinearSplitStrategy(): SplitStrategy() {};

private:
    virtual RNode* pickNext_(std::vector<RNode*>& children, RNode* groupOne, RNode* groupTwo)
    {
        throw std::runtime_error("Este método não está implementado para este classe!");
    }

    virtual RNode* pickNext_(std::vector<RNode*>& children)
    {
        RNode* el = children.at(0);
        children.erase(children.begin());
        
        return el;
    }

    /**
     *  Este método implementa as regras de Split apresentadas no método
     * de tempo linear no artigo de Guttman (1984). Neste, o conjunto de regras
     * {LPS1, LPS2, LPS3} são utilizados
     */
    virtual std::vector<RNode*> pickSeeds_(std::vector<RNode*>& vec)
    {
        // LPS1
        RNode* selectedLowestHighX = selectLowestHigh(vec, 0);
        RNode* selectedLowestHighY = selectLowestHigh(vec, 1);
        RNode* selectedHighestBassX = selectHighestBass(vec, 0);
        RNode* selectedHighestBassY = selectHighestBass(vec, 1);

        // LPS2 - Gerando as distâncias normalizadas
        double normalizedDistanceInX = normalizedDistanceNAxis(selectedLowestHighX, selectedHighestBassX, 0);
        double normalizedDistanceInY = normalizedDistanceNAxis(selectedLowestHighY, selectedHighestBassY, 1);

        // LPS3
        if (normalizedDistanceInX > normalizedDistanceInY)
            return std::vector<RNode*>({ selectedHighestBassX,  selectedLowestHighX });
        else
            return std::vector<RNode*>({ selectedHighestBassY, selectedLowestHighY });
    }

    virtual std::vector<RNode*> split_(RNode* L)
    {
        std::size_t m = L->m();
        std::size_t M = L->M();

        // Por agora estou copiando o código todo do quadraticSplit
        // Mas o código pode ser generalizado em um segundo momento
        std::vector<RNode*> children = L->children();
        L->children().clear();

        // Cria os dois novos grupos (Nós folha)
        RNode* groupOne = L; // aponta para L, mantendo todas as suas características
        RNode* groupTwo = new RNode(m, M, L->strategy());
        
        // Encontrando o pior par para separar eles    
        std::vector<RNode*> wrongSeeds = pickSeeds_(children);

        groupOne->addChild(wrongSeeds.at(0));
        groupTwo->addChild(wrongSeeds.at(1));

        bool isFinish = false;
        while (!children.empty())
        {
            // QS2 (Verificando se acabou)
            for(auto group: {groupOne, groupTwo})
            {
                // Verificando se algum dos grupos pode ficar sem a quantidade mínima de
                // elementos necessárias pela definição da árvore
                // "A quantidade de nós atuais no grupo consegue alcançar o mínimo quando somada
                // a quantidade de elementos que estão disponíveis para utilização"
                std::size_t elSize = (group->children().size() + children.size());
                if (elSize <= m)
                {
                    for(std::size_t inode = 0; group->children().size() < m; ++inode)
                    {
                        group->addChild(children.at(inode));
                        children.erase(children.begin() + inode);
                    }
                    isFinish = true;
                }
            }
            if (isFinish)
                return std::vector<RNode*> ({ groupOne, groupTwo });

            // QS3 (Seleciona entrada para atribuir)
            RNode* nextEntry = pickNext_(children);
        
            double areaGainG1 = DimensionalRectangleAlgebra::AreaGain(groupOne->mbr(), nextEntry->mbr());
            double areaGainG2 = DimensionalRectangleAlgebra::AreaGain(groupTwo->mbr(), nextEntry->mbr());

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
            if (!elementsIsInVector(selectedGroup->children(), nextEntry))
                selectedGroup->addChild(nextEntry);
        }

        return std::vector<RNode*> ({ groupOne, groupTwo });
    }
};

// class QuadraticSplitStrategy: public SplitStrategy
// {
    
// };

#endif
