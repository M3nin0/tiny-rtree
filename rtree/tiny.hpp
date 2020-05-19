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

    void addChildren(RNode* child);

    // Temporário
    void addMBR(BaseRectangle* mbr); // Vai para o construtor depois
    BaseRectangle* mbr() const;

    bool isLeaf() const;
    bool setIsLeaf(bool isLeaf);
    bool isFullOfChildren() const;

    friend class RTree;
private:
    bool p_isLeaf = false;
    std::size_t p_m, p_M; // passar para constante
    RNode* p_parent = nullptr;

    std::vector<RNode*> p_dataBlock;
    std::vector<RNode*> p_children;

    BaseRectangle* p_mbr = nullptr;

    // Métodos de operação no nó
    void insert_(RNode* nn);

    // Métodos de controle da estrutura do nó
    static RNode* chooseLeaf_(RNode* root, BaseRectangle* newRect);
    static std::vector<RNode*> quadraticPickSeeds_(std::vector<RNode*>& vec);
    static RNode* quadraticPickNext_(std::vector<RNode*>& children, RNode* groupOne, RNode* groupTwo);
    static std::vector<RNode*> quadraticSplit_(std::vector<RNode*>& children);
    
    // Métodos de controle geométrico do nó
    void updateMBR_();
};

class RTree
{
public:
    RTree(std::size_t m, std::size_t M);

    void insert(BaseRectangle* rect);
private:
    RNode* root;
    std::size_t p_m, p_M;
};


#endif