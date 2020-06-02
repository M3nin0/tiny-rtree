#ifndef __SPLIT_STRATEGY_HEADER__
#define __SPLIT_STRATEGY_HEADER__

#include <vector>
#include <limits>
#include <stdexcept>

#include "tree.hpp"
#include "SplitStrategy.hpp"

class SplitStrategy
{
public:
    SplitStrategy() {  };

    /**
     * DESCRIPTION: Facade com as implementações especializadas das estratégias de split
     */
    std::vector<RNode*> split(RNode* L)
        {
            return split_(L);
        }

    /**
     * DESCRIPTION: Facade com as implementações especializadas das estratégias de pickSeed
     */
    std::vector<RNode*> pickSeeds(std::vector<RNode*>& vec)
    {
        return pickSeeds_(vec);
    }

    /**
     * DESCRIPTION: Facade com as implementações especializadas das estratégias de pickNext
     */
    RNode* pickNext(std::vector<RNode*>& children,  
                                        RNode* groupOne = nullptr, RNode* groupTwo = nullptr)
    {
        return pickNext_(children, groupOne, groupTwo);
    }

private:

    /**
     * DESCRIPTION: Método a ser sobrescrito pelas classes descendentes para gerar o comportamento
     * de split da estratégia que está sendo implementada
     */
    virtual std::vector<RNode*> split_(RNode* L) = 0;
    
    /**
     *DESCRIPTION:  Método a ser sobrescrito pelas classes descendentes para gerar o comportamento
     * de pickSeed da estratégia implementada
     */
    virtual std::vector<RNode*> pickSeeds_(std::vector<RNode*>& vec) = 0;

    /**
     * DESCRIPTION: Método a ser sobrescrito pelas classes descendentes para gerar o comportamento
     * de pickNext da estratégia implementada.
     * 
     * OBSERVATION: A assinatura deste método é geral, podendo ser consumida por diferentes estratégias
     * de split. Por exemplo, mesmo utilizando a estratégia linear ou quadrática, todos os
     * parâmetros serão passados, mesmo que não utilizados, o que evita a criação e o tratamento
     * de múltiplos métodos *pickNext* 
     */
    virtual RNode* pickNext_(std::vector<RNode*>& children, 
                                        RNode* groupOne = nullptr, RNode* groupTwo = nullptr) = 0;
};

/**
 * DESCRIPTION: Classe com a implementação base para o funcionamento das 
 * estratégias de Split da RTree apresentadas por Guttmann (1984).
 */
class GuttmanMethod: public SplitStrategy
{
public:
    /**
     * DESCRIPTION: Método auxiliar para verificar se um elemento com uma certa referência
     * está presente no vector
     * 
     * TODO: Verificar necessidade
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

    /**
     * DESCRIPTION: Método auxiliar para remover os elementos selecionados como os iniciais dos 
     * dois grupos durante o split, este método evita que há elementos duplicados na árvore
     * 
     * TODO: Verificar necessidade
     */
    void removeFromVector(std::vector<RNode*>& vecx, RNode* el)
    {
        std::size_t i;
        for(i = 0; i < vecx.size(); ++i)
        {
            if (vecx.at(i) == el)
                break;
        }
        vecx.erase(vecx.begin() + i);
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
        RNode* groupTwo = new RNode(m, M, true, L->strategy());
        
        // Encontrando o pior par para separar eles    
        std::vector<RNode*> wrongSeeds = pickSeeds(children);

        groupOne->addChild(wrongSeeds.at(0));
        groupTwo->addChild(wrongSeeds.at(1));

        // Removendo os elementos para evitar duplicadas
        removeFromVector(children, wrongSeeds.at(0));
        removeFromVector(children, wrongSeeds.at(1));

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
            RNode* nextEntry = pickNext(children, groupOne, groupTwo);
        
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
            // ToDo: Rever a necessidade deste método, uma vez que os elementos duplicados são removidos
            // no início
            if (!elementsIsInVector(selectedGroup->children(), nextEntry))
                selectedGroup->addChild(nextEntry);
        }

        return std::vector<RNode*> ({ groupOne, groupTwo });
    }
};

/**
 * Estratégia de split em tempo linear
 */
class LinearSplitStrategy: public GuttmanMethod
{
public:
    LinearSplitStrategy(): GuttmanMethod() {};

private:
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
            if (selectedHighestBassNAxis->mbr()->min(axis) < node->mbr()->min(axis))
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
     * DESCRIPTION: Função auxiliar para a aplicação da normalização das dimensões filtradas da regra LPS1 do artigo
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

    virtual RNode* pickNext_(std::vector<RNode*>& children, RNode* groupOne, RNode* groupTwo)
    {
        RNode* el = children.at(0);
        children.erase(children.begin());
        
        return el;
    }

    /**
     * DESCRIPTION: Este método implementa as regras de Split apresentadas no método
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
};

/**
 * Estratégia de split em tempo quadrático
 */
class QuadraticSplitStrategy: public GuttmanMethod
{
public:
    QuadraticSplitStrategy(): GuttmanMethod() {};

private:
   virtual RNode* pickNext_(std::vector<RNode*>& children, RNode* groupOne, RNode* groupTwo)
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
            double gainGroupOne = DimensionalRectangleAlgebra::AreaGain(groupOne->mbr(), entry->mbr());
            double gainGroupTwo = DimensionalRectangleAlgebra::AreaGain(groupTwo->mbr(), entry->mbr());
            double difference = std::abs(gainGroupOne - gainGroupTwo);

            if (difference > maxDifference)
            {
                indexOfSelectedNode = i; // Para ajudar a remover o elemento selecionado
                maxDifference = difference;
                nodeWithMaxDifference = entry;
            }
        }
        children.erase(children.begin() + indexOfSelectedNode);
        return nodeWithMaxDifference;
    }

    /**
     * DESCRIPTION: Este método implementa as regras de Split apresentadas no método
     * de tempo quadrático no artigo de Guttman (1984). Neste, o conjunto de regras
     * {PS1, PS2} são utilizados
     */
    virtual std::vector<RNode*> pickSeeds_(std::vector<RNode*>& vec)
    {
        RNode* wrongE1, *wrongE2;
        double d = std::numeric_limits<double>::min();

        // PS1 - Busca a pior combinação de nós
        for(auto e1: vec)
        {
            for(auto e2: vec)
            {
                if (e1 != e2)
                {
                    double e1Area = DimensionalRectangleAlgebra::RectangleArea(e1->mbr());
                    double e2Area = DimensionalRectangleAlgebra::RectangleArea(e2->mbr());

                    DimensionalRectangle2D* base = DimensionalRectangleAlgebra::DimensionAppend(e1->mbr(), e2->mbr());
                    double dFor = DimensionalRectangleAlgebra::RectangleArea(base) - e1Area - e2Area;

                    // PS2 - Escolhendo o pior par
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
};

#endif
