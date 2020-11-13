#include <iostream>
#include <deque>
#include "Trees.h"
/**
 * Описание абстрактного дерева
 *
 */
template<typename T>
void AbstractTree<T>::insert(const T &key) {
    std::cout<<"You're doing something right:)"<<std::endl;
}

template<typename T>
bool AbstractTree<T>::find(const T &key) {
    std::cout<<"You're doing something right:)"<<std::endl;
    return false;

}

template<typename T>
void AbstractTree<T>::erase(const T &key) {
    std::cout<<"You're doing something right:)"<<std::endl;
}

template<typename T>
void AbstractTree<T>::clear() {
    std::cout<<"You're doing something right:)"<<std::endl;
}

template<typename T>
std::vector<T> AbstractTree<T>::dump() {
    std::cout<<"You're doing something right:)"<<std::endl;
    return std::vector<T>{};
}

/**
 * Описание бинарного дерева
 */
template<typename T>
node<T> *BinaryTree<T>::rotateLeft(node<T> *n) {
    return nullptr;
}

template<typename T>
node<T> *BinaryTree<T>::rotateRight(node<T> *n) {
    return nullptr;
}

template<typename T>
node<T> *BinaryTree<T>::remove(node<T> *n, const T &key) {
    return nullptr;
}


template<typename T>
node<T>* BinaryTree<T>::findNode(const T &key) {
    node<T>* p = root;
    while (p) {
        if (p->key < key)p = p->right;
        else if (key < p->key)p = p->left;
        else return p;
    }
    return nullptr;
}

template<typename T>
node<T> *BinaryTree<T>::insertNode(node<T> *_root, node<T> *n) {
    if (_root == nullptr)
        return n;
    if (n->key < _root->key) {
        _root->left = insertNode(_root->left, n);
        _root->left->parent = _root;
    } else if (_root->key < n->key) {
        _root->right = insertNode(_root->right, n);
        _root->right->parent = _root;
    }
    return _root;
}

template<typename T>
node<T> *BinaryTree<T>::findMinNode(node<T> *n) {
    node<T> *ptr = n;
    while (ptr->left != nullptr)
        ptr = ptr->left;
    return ptr;
}

template<typename T>
node<T> *BinaryTree<T>::findMaxNode(node<T> *n) {
    node<T> *ptr = n;
    while (ptr->right != nullptr)
        ptr = ptr->right;
    return ptr;
}

template<typename T>
std::vector<T> BinaryTree<T>::dump() {
    std::deque<node<T>*> q;
    std::vector<T> v;
    q.push_back(root);
    while (!q.empty()) {
        node<T>* p = q.front();
        if (p->left)q.push_back(p->left);
        if (p->right)q.push_back(p->right);
        v.push_back(p->key);
        q.pop_front();
    }
    return v;
}

template<typename T>
void BinaryTree<T>::clear() {
    if (!root)return;
    std::deque<node<T>*> q;
    q.push_back(root);
    while (!q.empty()) {
        node<T>* p = q.front();
        if (p->left)q.push_back(p->left);
        if (p->right)q.push_back(p->right);
        delete p;
        q.pop_front();
    }
}

template<typename T>
void BinaryTree<T>::cl() {
    clear();
}

template<typename T>
BinaryTree<T>::BinaryTree(const std::vector<T> &args) {
}

template<typename T>
BinaryTree<T>::~BinaryTree() {
    cl();
}

template<typename T>
void BinaryTree<T>::insert(const T &key) {
}

template<typename T>
bool BinaryTree<T>::find(const T &key) {
    return findNode(key);
}

template<typename T>
void BinaryTree<T>::erase(const T &key) {
}

/**
 * описание кч дерева
*/
template<typename T>
char RedBackTree<T>::getColor(node<T> *n) {
    if (!n)
        return BLACK;
    return n->param;
}

template<typename T>
void RedBackTree<T>::setColor(node<T> *n, unsigned char color) {
    if (!n)
        return;
    n->param = color;
}

template<typename T>
bool RedBackTree<T>::hasRedChild(node<T> *n) {
    return (n->left != nullptr && getColor(n->left) == RED) ||
           (n->right != nullptr && getColor(n->right) == RED);
}

template<typename T>
bool RedBackTree<T>::isOnLeft(node<T> *n) {
    return n == n->parent->left;
}

template<typename T>
node<T> *RedBackTree<T>::getSibling(node<T> *n) {
    if (n->parent == nullptr)
        return nullptr;
    if (isOnLeft(n))
        return n->parent->right;
    return n->parent->left;
}

template<typename T>
node<T> *RedBackTree<T>::getN(node<T> *n) {
    if (n->left != nullptr && n->right != nullptr)
        return this->findMinNode(n->right);
    if (n->left == nullptr && n->right == nullptr)
        return nullptr;
    if (n->left != nullptr)
        return n->left;
    else
        return n->right;
}

template<typename T>
void RedBackTree<T>::fixInsertRBTree(node<T> *n) {
    node<T> *parent = nullptr;
    node<T> *grandparent = nullptr;
    while (n != this->root && getColor(n) == RED && getColor(n->parent) == RED) {
        parent = n->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {
            node<T> *uncle = grandparent->right;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                n = grandparent;
            } else {
                if (n == parent->right) {
                    rotateLeft(parent);
                    n = parent;
                    parent = n->parent;
                }
                rotateRight(grandparent);
                std::swap(parent->param, grandparent->param);
                n = parent;
            }
        } else {
            node<T> *uncle = grandparent->left;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                n = grandparent;
            } else {
                if (n == parent->left) {
                    rotateRight(parent);
                    n = parent;
                    parent = n->parent;
                }
                rotateLeft(grandparent);
                std::swap(parent->param, grandparent->param);
                n = parent;
            }
        }
    }
    setColor(this->root, BLACK);
}

template<typename T>
void RedBackTree<T>::fixDeleteRBTree(node<T> *n) {
    if (n == this->root)
        return;
    node<T> *sibling = getSibling(n), *parent = n->parent;
    if (sibling == nullptr){
        fixDeleteRBTree(parent);
    }else{
        if (getColor(sibling) == RED) {
            setColor(parent,RED);
            setColor(sibling,BLACK);
            if (isOnLeft(sibling)) {
                rotateRight(parent);
            } else {
                rotateLeft(parent);
            }
            fixDeleteRBTree(n);
        } else {
            if (hasRedChild(sibling)) {
                if (sibling->left != nullptr && getColor(sibling->left) == RED) {
                    if (isOnLeft(sibling)) {
                        setColor(sibling->left,getColor(sibling));
                        setColor(sibling,getColor(parent));
                        rotateRight(parent);
                    } else {
                        setColor(sibling->left,getColor(parent));
                        rotateRight(sibling);
                        rotateLeft(parent);
                    }
                } else {
                    if (isOnLeft(sibling)) {
                        setColor(sibling->right,getColor(parent));
                        rotateLeft(sibling);
                        rotateRight(parent);
                    } else {
                        setColor(sibling->right, getColor(sibling));
                        setColor(sibling, getColor(parent));
                        rotateLeft(parent);
                    }
                }
                setColor(parent, BLACK);
            } else {
                setColor(sibling, RED);
                if (getColor(parent) == BLACK)
                    fixDeleteRBTree(parent);
                else
                    setColor(parent, BLACK);
            }
        }
    }
}

template<typename T>
node<T> *RedBackTree<T>::rotateLeft(node<T> *p) {
    node<T> *right_child = p->right;
    p->right = right_child->left;

    if (p->right != nullptr)
        p->right->parent = p;

    right_child->parent = p->parent;

    if (p->parent == nullptr)
        this->root = right_child;
    else if (p == p->parent->left)
        p->parent->left = right_child;
    else
        p->parent->right = right_child;

    right_child->left = p;
    p->parent = right_child;
    return nullptr;
}

template<typename T>
node<T> *RedBackTree<T>::rotateRight(node<T> *ptr) {

    node<T> *left_child = ptr->left;
    ptr->left = left_child->right;

    if (ptr->left != nullptr)
        ptr->left->parent = ptr;

    left_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        this->root = left_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = left_child;
    else
        ptr->parent->right = left_child;

    left_child->right = ptr;
    ptr->parent = left_child;
    return nullptr;
}

template<typename T>
node<T> *RedBackTree<T>::remove(node<T> *r, const T &data) {
    node<T> * v =this->findNode(data);
    if (v == nullptr)
        return nullptr;
    node<T> *u = getN(v);
    bool uvBlack = ((u == nullptr || getColor(u) == BLACK) && (getColor(v) == BLACK));
    node<T> *parent = v->parent;
    if (u == nullptr) {
        if (v == this->root) {
            this->root = nullptr;
        }else {
            if (uvBlack){
                fixDeleteRBTree(v);
            }else {
                if (getSibling(v) != nullptr) {
                    setColor(getSibling(v), RED);
                }
            }
            if (isOnLeft(v))parent->left = nullptr;
            else parent->right = nullptr;
        }
        delete v;
    }
    return nullptr;
}

template<typename T>
void RedBackTree<T>::in(const T &key) {
    insert(key);
}

template<typename T>
void RedBackTree<T>::insert(const T &key) {
    auto *n = new node<T>(key);
    n->param = RED;
    this->root = this->insertNode(this->root, n);
    fixInsertRBTree(n);
}

template<typename T>
void RedBackTree<T>::erase(const T &key) {
    remove(this->root,key);
}

/**
 * описание авл дерева
*/

template<typename T>
unsigned char AVLTree<T>::height(node<T> *p) {
    return p ? p->param : 0;
}

template<typename T>
int AVLTree<T>::bFactor(node<T> *p) {
    return height(p->right)-height(p->left);
}

template<typename T>
void AVLTree<T>::fixHeight(node<T> *p) {
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->param = (hl > hr ? hl : hr) + 1;
}

template<typename T>
node<T> *AVLTree<T>::balance(node<T> *p) {
    fixHeight(p);
    if(bFactor(p) == 2 ){
        if(bFactor(p->right) < 0 )
            p->right = rotateRight(p->right);
        return rotateLeft(p);
    }
    if(bFactor(p) == -2 ){
        if(bFactor(p->left) > 0  )
            p->left = rotateLeft(p->left);
        return rotateRight(p);
    }
    return p;
}

template<typename T>
node<T> *AVLTree<T>::insert(node<T> *p, const T &k) {
    if( !p ) return new node<T>(k);
    if (k<p->key)
        p->left = insert(p->left,k);
    else if(p->key<k)
        p->right = insert(p->right,k);
    return balance(p);
}

template<typename T>
node<T> *AVLTree<T>::rotateRight(node<T> *p) {
    node<T>* q = p->left;
    p->left = q->right;
    q->right = p;
    fixHeight(p);
    fixHeight(q);
    return q;
}

template<typename T>
node<T> *AVLTree<T>::rotateLeft(node<T> *q) {
    node<T>* p = q->right;
    q->right = p->left;
    p->left = q;
    fixHeight(q);
    fixHeight(p);
    return p;
}

template<typename T>
node<T> *AVLTree<T>::removeMin(node<T> *p) {
    if( p->left== nullptr )
        return p->right;
    p->left = removeMin(p->left);
    return balance(p);
}

template<typename T>
node<T> *AVLTree<T>::remove(node<T> *p, const T &k) {
    if( !p ) return nullptr;
    if( k < p->key )p->left = remove(p->left,k);
    else if( p->key < k)p->right = remove(p->right,k);
    else{
        node<T>* q = p->left;
        node<T>* r = p->right;
        delete p;
        if (!r) return q;
        node<T>* min = this->findMinNode(r);
        min->right = removeMin(r);
        min->left = q;
        return min;
    }
    return p;
}

template<typename T>
void AVLTree<T>::in(const T &key) {
    insert(key);
}

template<typename T>
void AVLTree<T>::insert(const T &key) {
    this->root = insert(this->root, key);
}

template<typename T>
void AVLTree<T>::erase(const T &key) {
    this->root = remove(this->root, key);
}
