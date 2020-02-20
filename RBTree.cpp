//
// Created by roman on 15.02.2020.
//

#include "RBTree.h"
#include <vector>
#include <iostream>

void RBTree::rotateLeft(RBNode *p) {
    RBNode *r = p->right;
    r->parent = p->parent;
    if (r->parent == null)
        root = r;
    else if (r->parent->right == p)
        r->parent->right = r;
    else r->parent->left = r;
    p->right = r->left;
    if (p->right != null)
        p->right->parent = p;
    r->left = p;
    p->parent = r;
}

void RBTree::rotateRight(RBNode *p) {
    RBNode *r = p->left;
    r->parent = p->parent;
    if (r->parent == null)
        root = r;
    else if (r->parent->right == p)
        r->parent->right = r;
    else r->parent->left = r;
    p->left = r->right;
    if (p->left != null)
        p->left->parent = p;
    r->right = p;
    p->parent = r;
}

bool RBTree::insert(RBNode *p) {
    if (root == null) {
        root = p;
        return true;
    }
    RBNode *t = root;
    while (t != null) {
        if (p->key < t->key) {
            if (t->left == null) {
                t->left = p, p->parent = t;
                break;
            }
            t = t->left;
        } else if (p->key > t->key) {
            if (t->right == null) {
                t->right = p, p->parent = t;
                break;
            }
            t = t->right;
        } else return false;
    }

    return true;
}

void RBTree::add(int key) {
    RBNode *n = new RBNode(key, null);
    if (insert(n)) {
        fixInsertion(n);
    }
}

void RBTree::print() {
    if (root == null)
        return;
    std::vector<std::pair<RBNode, int>> stk;
    stk.emplace_back(root, 0);
    while (!stk.empty()) {
        auto t = stk.back();
        stk.pop_back();
        for (int i = 0; i < t.second; ++i) std::cout << "  ";
        std::cout << t.first.toString() << std::endl;
        if (t.first.right != null) stk.emplace_back(t.first.right, t.second+1);
        if (t.first.left != null) stk.push_back({t.first.left, t.second+1});
    }
}

void RBTree::test_meth() {
    rotateLeft(root);
}

void RBTree::fixInsertion(RBNode *p) {
    RBNode *parent = null;
    RBNode *grandparent = null;
    RBNode *uncle;
    while (p != root && p->is_red && p->parent->is_red) {
        parent = p->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {
            uncle = grandparent->right;
            if (uncle->is_red) {
                uncle->is_red = false;
                parent->is_red = false;
                grandparent->is_red = true;
                p = grandparent;
            } else {
                if (p == parent->right) {
                    rotateLeft(parent);
                    p = parent;
                    parent = p->parent;
                }
                rotateRight(grandparent);
                std::swap(parent->is_red, grandparent->is_red);
                p = parent;
            }
        } else {
            uncle = grandparent->left;
            if (uncle->is_red) {
                uncle->is_red = false;
                parent->is_red = false;
                grandparent->is_red = true;
                p = grandparent;
            } else {
                if (p == parent->left) {
                    rotateRight(parent);
                    p = parent;
                    parent = p->parent;
                }
                rotateLeft(grandparent);
                std::swap(parent->is_red, grandparent->is_red);
                p = parent;
            }
        }
    }

    root->is_red = false;
}

RBNode *RBTree::find(int key) {
    RBNode *p = root;
    while (p != null) {
        if (p->key == key) return p;
        if (key < p->key) p = p->left;
        else p = p->right;
    }
    return p;
}

bool RBTree::contains(int key) {
    return find(key) != null;
}

void RBTree::remove(int key) {
    RBNode *p = find(key);
    if (p != null) {
        RBNode *q = remove(p);
        delete q;
    }
}

RBNode *RBTree::remove(RBNode *p) {
    RBNode *y; // Node, which we are going to delete
    RBNode *x; // Node, which will be left after deletion of y
    if (p->right == null || p->left == null)
        y = p;
    else y = successor(p);
    if (y->left != null)
        x = y->left;
    else x = y->right;
    x->parent = y->parent;
    if (y->parent == null)
        root = x;
    else if (y->parent->left == y)
        y->parent->left = x;
    else y->parent->right = x;
    if (y != p)
        p->key = y->key;
    if (!y->is_red)
        fixDeletion(x);
    return y;
}

RBNode *RBTree::treeMin(RBNode *p) {
    while (p != null && p->left != null) p = p->left;
    return p;
}

RBNode *RBTree::successor(RBNode *p) {
    if (p->right != null)
        return treeMin(p->right);
    RBNode *y = p->parent;
    while (y != null && p == y->right) {
        p = y;
        y = y->parent;
    }
    return y;
}

void RBTree::fixDeletion(RBNode *p) {
    while (p != root && !p->is_red) {
        if (p == p->parent->left) {
            RBNode *w = p->parent->right;
            if (w->is_red) {
                w->is_red = false;
                p->parent->is_red = true;
                rotateLeft(p->parent);
                w = p->parent->right;
            }
            if (!w->left->is_red && !w->right->is_red) {
                w->is_red = true;
                p = p->parent;
            } else {
                if (!w->right->is_red) {
                    w->left->is_red = false;
                    w->is_red = true;
                    rotateRight(w);
                    w = p->parent->right;
                }
                w->is_red = p->parent->is_red;
                p->parent->is_red = false;
                w->right->is_red = false;
                rotateLeft(p->parent);
                p = root;
            }
        } else {
            RBNode *w = p->parent->left;
            if (w->is_red) {
                w->is_red = false;
                p->parent->is_red = true;
                rotateRight(p->parent);
                w = p->parent->left;
            }
            if (!w->left->is_red && !w->right->is_red) {
                w->is_red = true;
                p = p->parent;
            } else {
                if (!w->left->is_red) {
                    w->right->is_red = false;
                    w->is_red = true;
                    rotateLeft(w);
                    w = p->parent->left;
                }
                w->is_red = p->parent->is_red;
                p->parent->is_red = false;
                w->left->is_red = false;
                rotateRight(p->parent);
                p = root;
            }
        }
    }

    p->is_red = false;
}
