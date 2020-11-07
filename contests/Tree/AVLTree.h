#ifndef UNTITLED_AVLTREE_H
#define UNTITLED_AVLTREE_H

#include "AbstractTree.h"

template <typename T>
class AVLTree : AbstractTree<T> {
public:

    AVLTree();

    ~AVLTree() override;

    bool insert(const T &n) override;

    bool find(const T &n) override;

    bool erase(const T &n) override;

};


#endif
