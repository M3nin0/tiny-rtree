#ifndef __RTREE_HEADER__
#define __RTREE_HEADER__

#include <vector>
#include <cstddef>
#include "geometry.hpp"

class RNode
{
public:
    RNode();
    RNode(std::size_t m, std::size_t M);
    RNode(std::size_t m, std::size_t M, RNode* parent);
    RNode(std::size_t m, std::size_t M, RNode* parent, bool isLeaf);

    // Métodos temporários
    RNode* parent() const;

    BaseRectangle* mbr(); // talvez esse não seja temporário
    void insert(RNode* nrnode);
    void setLeaf(bool isLeaf);
    void addMBR(BaseRectangle* mbr);

    bool isFull() const;
    bool isLeaf() const;
    std::vector<RNode*> children() const; // Isto como 'children' está um pouco estranho
                                          // vou alterar depois para ficar mais semântico
private:
    
    bool p_isleaf = false;
    std::size_t p_m, p_M;
    std::size_t p_size = 0;
    BaseRectangle *p_mbr = nullptr;

    RNode* child = nullptr; // Talvez isso aqui possar ser utilizado como 
                            // elemento para controlar se é ou não uma folha.
                            // Provavelmente isto vai passar a ser um vetor que possuí
                            // valores entre m e M e a variável p_chidren passar a ser algo
                            // como 'blocks' ou 'data'. Verificar
    RNode* p_parent = nullptr;
    std::vector<RNode*> p_children;

    void UpdateMBR(BaseRectangle* nBaseRectangle);
    
    // Métodos auxiliares da inserção
    // void AdjustTree(RNode* root, RNode* N, RNode* NN);
    
    // Posteriormente, estes algoritmos serão organizados e separados
    // std::vector<RNode*> QuadraticSplit(RNode* root); // vector para devolver os dois elementos
    // std::vector<RNode*> QuadraticPickSeeds(RNode* root);
    // RNode* QuadraticPickNext(RNode* root, RNode* E);
};

class RTree
{
public:
    RTree(std::size_t m, std::size_t M);

    // Esta parte, posteriormente, será substituída por uma
    // classe mais genérica, possibilitando a inserção de qualquer geometria
    // que tenha disponível um método do tipo `envelope` ou similar
    void insert(BaseRectangle* rect);
private:
    RNode* root;
    std::size_t p_m, p_M;
};

#endif
