//
// Created by roman on 15.02.2020.
//

#ifndef REDBLACKTREE_RBNODE_H
#define REDBLACKTREE_RBNODE_H

#include <string>

struct RBNode {
    RBNode(RBNode *pNode) {
        left = pNode->left;
        right = pNode->right;
        parent = pNode->parent;
        is_red = pNode->is_red;
        key = pNode->key;
    }

    RBNode *left, *right, *parent;
    int key;
    bool is_red = true;
    explicit RBNode(int Key) : key(Key) {
        left = right = parent = nullptr;
    }
    RBNode(int Key, RBNode *defaultNull) : key(Key) {
        left = right = parent = defaultNull;
    }
    std::string toString() {
        return std::to_string(key) + " : " + (is_red ? "RED" : "BLACK");
    }
};


#endif //REDBLACKTREE_RBNODE_H
