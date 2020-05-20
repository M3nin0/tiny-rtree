#ifndef __RTREE_TINY__
#define __RTREE_TINY__

#include <vector>
#include <cstddef>
#include "geometry.hpp"

class RNode
{
public:
    RNode();
    RNode(bool isLeaf);
    RNode(std::size_t m, std::size_t M); // estudar a necessidade do nó receber m e M
    RNode(std::size_t m, std::size_t M, RNode* parent);
    RNode(std::size_t m, std::size_t M, RNode* parent, bool isLeaf);

    void addParent(RNode* child);
    void addChildren(RNode* child);

    // Temporário
    void addMBR(BaseRectangle* mbr); // Vai para o construtor depois
    BaseRectangle* mbr() const;

    bool isLeaf() const;
    void setIsLeaf(bool isLeaf);
    bool isFullOfChildren() const;

    friend class RTree;
private:
    bool p_isLeaf = true; // gera um warning
    std::size_t p_m, p_M; // passar para constante
    RNode* p_parent = nullptr; // gera um warning

    std::vector<RNode*> p_children;
    BaseRectangle* p_mbr = nullptr;

    // Métodos de operação no nó
    RNode* insert_(RNode* nn);

    // Métodos de controle da estrutura do nó
    RNode* chooseLeaf_(RNode* root, BaseRectangle* newRect);
    void adjustTree_(RNode* root, RNode* N, RNode* NN);
    std::vector<RNode*> quadraticPickSeeds_(std::vector<RNode*>& vec);
    RNode* quadraticPickNext_(std::vector<RNode*>& children, RNode* groupOne, RNode* groupTwo);
    // std::vector<RNode*> quadraticSplit_(std::vector<RNode*>& children); esse estava com a lógica errada
    std::vector<RNode*> quadraticSplit_(RNode* L);

    // Método de busca
    std::vector<RNode*> search_(std::vector<RNode*>& vec, BaseRectangle* rect);
    std::vector<RNode* overslaps_>; // provisório
    
    // Métodos de controle geométrico do nó
    void updateMBR_();
};

class RTree
{
public:
    // ToDo: Validar se a entrada de 'm' faz sentido com a entrada de M
    RTree(std::size_t m, std::size_t M);

    void insert(BaseRectangle* rect);
    void search(BaseRectangle* rect);
private:
    RNode* root;
    std::size_t p_m, p_M;
};


#endif
