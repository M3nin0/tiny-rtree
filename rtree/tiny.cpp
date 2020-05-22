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

RNode::RNode(std::size_t m, std::size_t M, RNode* parent, bool isLeaf)
    : p_m(m), p_M(M), p_parent(parent), p_isLeaf(isLeaf) 
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

void RNode::setIsLeaf(bool isLeaf)
{
    p_isLeaf = isLeaf;
}

bool RNode::isFullOfChildren() const
{
    return p_children.size() >= p_M;
}

void RNode::addChildren(RNode* child)
{
    child->p_parent = this; // Criando a associação entre os nós
    p_children.push_back(child);

    updateMBR_(); // mantém o MBR do nó atualizado
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
    for(std::size_t i = 0; i < p_children.size(); ++i)
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
    // AreaGain(N->mbr(), newRect); = Estava deixando a árvore desbalanceada
    double maxGainArea = std::numeric_limits<double>::max(); // AreaGain(N->mbr(), newRect);

    // isso aqui ocorreu em um dos testes que fiz
    // a inserção em um N fazia o MBR ser zero (O MBR de N era muito grande,
    // e o newRect pequeno, ai não mudava em nada o MBR)
    // Foi alterado acima, no lugar do AreaGain foi colocado o máximo do double
    // isso faz com que talvez esta operação possa ser removida
    if (maxGainArea == 0)
    {
        return N;
    }

    // Buscando o nó que possuí o menor crescimento do MBR
    for(auto node: N->p_children)
    {
        double areaGain = AreaGain(node->mbr(), newRect);

        if ( areaGain < maxGainArea && !node->isLeaf() )
        {
            selectedNode = node;
            maxGainArea = areaGain;
        }

        if (areaGain == maxGainArea && !node->isLeaf())
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

    // Adicionado para verificar se o nó de entrada sofreu mudanças.
    // Caso não tenha sofrido, indica que a busca está sendo feita no nível
    // das folhas, assim, o elemento N (Superior) deve ser devolvido.
    if (selectedNode == N)
        return N;

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
            indexOfSelectedNode = i; // apenas para remover o elemento selecionado 
            maxDifference = difference;
            nodeWithMaxDifference = entry;
        }
    }
    children.erase(children.begin() + indexOfSelectedNode);
    return nodeWithMaxDifference;
}

bool elementsIsInVector(std::vector<RNode*>& vec, RNode* el)
{
    for(auto vEl: vec)
    {
        if (vEl == el)
            return true;
    }
    return false;
}

std::vector<RNode*> RNode::quadraticSplit_(RNode* L)
{
    std::vector<RNode*> children = L->p_children;
    L->p_children.clear(); // pode limpar já que ele está sendo dividido
                           // e seu conteúdo será redistribuído na função abaixo

    // Cria os dois novos grupos (Nós folha)
    RNode* groupOne = L; // aponta para L, mantendo todas as suas características
    RNode* groupTwo = new RNode(p_m, p_M);

    // Encontrando o pior par para separar eles    
    std::vector<RNode*> wrongSeeds = quadraticPickSeeds_(children);

    groupOne->addChildren(wrongSeeds.at(0));
    groupTwo->addChildren(wrongSeeds.at(1));

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
            std::size_t elSize = (group->p_children.size() + children.size());
            if (elSize <= p_m)
            {
                for(std::size_t inode = 0; group->p_children.size() < p_m; ++inode)
                {
                    group->addChildren(children.at(inode));
                    children.erase(children.begin() + inode);
                }
                isFinish = true;
            }
        }
        if (isFinish)
            return std::vector<RNode*> ({ groupOne, groupTwo });

        // QS3 (Seleciona entrada para atribuir)
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
        if (!elementsIsInVector(selectedGroup->p_children, nextEntry))
            selectedGroup->addChildren(nextEntry);
    }

    return std::vector<RNode*> ({ groupOne, groupTwo });
}

void RNode::adjustTree_(RNode* root, RNode* N, RNode* NN)
{
    if(N == root)
        return;

    RNode* pParent = N->p_parent;
    pParent->updateMBR_();

    if (NN != nullptr)
    {
        // Se o pai não estiver cheio de filhos, adiciona o NN
        if (!pParent->isFullOfChildren())
        {
            pParent->addChildren(NN);
            adjustTree_(root, pParent, nullptr); // Não tem divisão, NN = nullprt
        }
        else
        {
            std::vector<RNode*> PAndPP = quadraticSplit_(pParent);
            adjustTree_(root, PAndPP.at(0), PAndPP.at(1));
        }
    }
}

/**
 * Criando a inserção de custo linear
 */
std::vector<RNode*> RNode::linearSplit_(RNode* L)
{
    // Por agora estou copiando o código todo do quadraticSplit
    // em seguida, podemos generalizar com um padrão Strategy ou algo do tipo
    std::vector<RNode*> children = L->p_children;
    L->p_children.clear(); // pode limpar já que ele está sendo dividido
                           // e seu conteúdo será redistribuído na função abaixo

    // Cria os dois novos grupos (Nós folha)
    RNode* groupOne = L; // aponta para L, mantendo todas as suas características
    RNode* groupTwo = new RNode(p_m, p_M);

    // Encontrando o pior par para separar eles    
    std::vector<RNode*> wrongSeeds = linearPickSeeds_(children);

    groupOne->addChildren(wrongSeeds.at(0));
    groupTwo->addChildren(wrongSeeds.at(1));

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
            std::size_t elSize = (group->p_children.size() + children.size());
            if (elSize <= p_m)
            {
                for(std::size_t inode = 0; group->p_children.size() < p_m; ++inode)
                {
                    group->addChildren(children.at(inode));
                    children.erase(children.begin() + inode);
                }
                isFinish = true;
            }
        }
        if (isFinish)
            return std::vector<RNode*> ({ groupOne, groupTwo });

        // QS3 (Seleciona entrada para atribuir)
        RNode* nextEntry = linearPickNext_(children);
    
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
        if (!elementsIsInVector(selectedGroup->p_children, nextEntry))
            selectedGroup->addChildren(nextEntry);
    }

    return std::vector<RNode*> ({ groupOne, groupTwo });
}

// A apresentação que você me mandou hj (20/05/2020) ajudou a resolver
// o código precisa ser arrumado e generalizado, mas por agora só a lógica
// já é o suficiente (eu acho)
std::vector<RNode*> RNode::linearPickSeeds_(std::vector<RNode*>& vec)
{
    // Buscando na dimensão X
    RNode* selectedNodeLadoBaixoMaisAltoX = vec.front(); // pega o primeiro para começar
    for(auto node: vec)
    {
        // Isso aqui pode ser generalizado para um método que devolve as dimensões
        // tipo o que é feito para a implementação das árvores KD-Tree
        if (selectedNodeLadoBaixoMaisAltoX->mbr()->xmin() < node->mbr()->xmin())
            selectedNodeLadoBaixoMaisAltoX = node;
    }

    // Buscando na dimensão X
    RNode* selectedNodeLadoAltoMaisBaixoX = vec.front(); // pega o primeiro para começar
    for(auto node: vec)
    {
        if (selectedNodeLadoAltoMaisBaixoX->mbr()->xmax() > node->mbr()->xmax())
            selectedNodeLadoAltoMaisBaixoX = node;
    }

    // Repetindo tudo para o eixo Y
    // Novamente, isso é só um esboço =D
    // Buscando na dimensão Y
    RNode* selectedNodeLadoBaixoMaisAltoY = vec.front(); // pega o primeiro para começar
    for(auto node: vec)
    {
        if (selectedNodeLadoBaixoMaisAltoY->mbr()->ymin() < node->mbr()->ymin())
            selectedNodeLadoBaixoMaisAltoY = node;
    }

    // Buscando na dimensão Y
    RNode* selectedNodeLadoAltoMaisBaixoY = vec.front(); // pega o primeiro para começar
    for(auto node: vec)
    {
        if (selectedNodeLadoAltoMaisBaixoY->mbr()->ymax() > node->mbr()->ymax())
            selectedNodeLadoAltoMaisBaixoY = node;
    }

    // Calculando as distâncias normalizadas
    double distanciaNormalizadaEmX = (
        (selectedNodeLadoBaixoMaisAltoX->mbr()->xmax() - selectedNodeLadoAltoMaisBaixoX->mbr()->xmin())
        / 
        (selectedNodeLadoBaixoMaisAltoX->mbr()->xmin() + selectedNodeLadoAltoMaisBaixoX->mbr()->xmax())
    );

    double distanciaNormalizadaEmY = (
        (selectedNodeLadoBaixoMaisAltoY->mbr()->ymax() - selectedNodeLadoAltoMaisBaixoY->mbr()->ymin())
        / 
        (selectedNodeLadoBaixoMaisAltoY->mbr()->ymin() + selectedNodeLadoAltoMaisBaixoY->mbr()->ymax())
    );

    if (distanciaNormalizadaEmX > distanciaNormalizadaEmY)
        return std::vector<RNode*>({ selectedNodeLadoBaixoMaisAltoX,  selectedNodeLadoAltoMaisBaixoX });
    else
        return std::vector<RNode*>({ selectedNodeLadoBaixoMaisAltoY, selectedNodeLadoAltoMaisBaixoY });
}

RNode* RNode::linearPickNext_(std::vector<RNode*>& children)
{
    // Apenas para materializar o método
    // aqui, recupero o que está disponível
    // Provavelmente isso vai ficar diretamente dentro do linearSplit_
    RNode* el = children.back();
    children.pop_back();

    return el;
}

RNode* RNode::insert_(RNode* nn)
{
    RNode* L = chooseLeaf_(this, nn->mbr());

    // Se está cheio não pode inserir NN, precisa realizar a operação de split
    if (L->isFullOfChildren())
    {
        L->addChildren(nn);

        std::vector<RNode*> LAndLL = linearSplit_(L);//quadraticSplit_(L);
        adjustTree_(this, LAndLL.at(0), LAndLL.at(1));
        // Dúvida: Aqui defini que um nó folha é aquele que possuí filhos
        // pq a dúvida ? A dúvida aqui veio por estarmos utilizando o mesmo
        // container para armazenar nós e folhas...quando penso sobre
        // as vezes parece não fazer diferença, mas fiquei com a dúvida..
        LAndLL.at(0)->setIsLeaf(LAndLL.at(0)->p_children.empty());
        LAndLL.at(1)->setIsLeaf(LAndLL.at(1)->p_children.empty());

        // Verificando se L é a raiz
        // Caso seja, uma divisão na raiz ocorreu
        if (L == this)
        {
            RNode* newRoot = new RNode(p_m, p_M, nullptr, false); // criando novo nó
            newRoot->addChildren(LAndLL.at(0));
            newRoot->addChildren(LAndLL.at(1));

            return newRoot;
        }
    } else
    {
        L->addChildren(nn);
    }
    return this;
}

/**
 * Definição da classe e operações da RTree propriamente dita
*/
RTree::RTree(std::size_t m, std::size_t M)
    : p_m(m), p_M(M)
{
    root = new RNode(m, M, nullptr);
    root->setIsLeaf(true);
}

void RTree::insert(BaseRectangle* rect)
{
    RNode* nn = new RNode(p_m, p_M, nullptr, true);
    nn->addMBR(rect);

    root = root->insert_(nn);
}
