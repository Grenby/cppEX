#ifndef UNTITLED_REDBACKTREE_H
#define UNTITLED_REDBACKTREE_H


#include "AbstractTree.h"

template <typename T>
class RedBackTree :AbstractTree<T>{
public:
    ~RedBackTree() override;

    bool insert(const T &n) override;

    bool find(const T &n) override;

    bool erase(const T &n) override;

};


#endif
