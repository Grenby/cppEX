#ifndef UNTITLED_ABSTRACTTREE_H
#define UNTITLED_ABSTRACTTREE_H


template <typename T>

class AbstractTree{
public:
    virtual ~AbstractTree();

    virtual bool insert(const T& n);
    virtual bool find(const T& n);
    virtual bool erase(const T& n);
};


#endif