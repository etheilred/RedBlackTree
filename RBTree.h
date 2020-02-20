//
// Created by roman on 15.02.2020.
//

#ifndef REDBLACKTREE_RBTREE_H
#define REDBLACKTREE_RBTREE_H

#include "RBNode.h"

class RBTree {
    RBNode *root;
    RBNode *null = new RBNode(0);
    void rotateLeft(RBNode *p);
    void rotateRight(RBNode *p);
    void fixInsertion(RBNode *p);
    void fixDeletion(RBNode *p);
    RBNode *treeMin(RBNode *p);
    RBNode *successor(RBNode *p);
    RBNode *remove(RBNode *p);
    bool insert(RBNode *p);
    RBNode *find(int key);
public:
    RBTree() {
        null->is_red = false;
        root = null;
    }
    void add(int key);
    void remove(int key);
    void print();
    bool contains(int key);
    void test_meth();
    bool empty() {
        return root == null;
    }
};


#endif //REDBLACKTREE_RBTREE_H
