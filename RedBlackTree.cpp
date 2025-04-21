#include "RedBlackTree.h"
#include <stdexcept>
#include <sstream>

RedBlackTree::RedBlackTree() {
    root = nullptr;
    numItems = 0;
}

RedBlackTree::RedBlackTree(int newData) {
    root = new RBTNode{newData, COLOR_BLACK};
    numItems = 1;
}

RedBlackTree::RedBlackTree(const RedBlackTree &rbt) {
    root = CopyOf(rbt.root);
    numItems = rbt.numItems;
}

RBTNode* RedBlackTree::CopyOf(const RBTNode *node) {
    if (!node) return nullptr;
    RBTNode *copy = new RBTNode{node->data, node->color};
    copy->IsNullNode = node->IsNullNode;
    copy->left = CopyOf(node->left);
    if (copy->left) copy->left->parent = copy;
    copy->right = CopyOf(node->right);
    if (copy->right) copy->right->parent = copy;
    return copy;
}

void RedBlackTree::Insert(int newData) {
    if (Contains(newData)) throw invalid_argument("Duplicate value");
    RBTNode* newNode = new RBTNode{newData, COLOR_RED};
    BasicInsert(newNode);
    InsertFixUp(newNode);
    ++numItems;
}

void RedBlackTree::BasicInsert(RBTNode *node) {
    if (!root) {
        node->color = COLOR_BLACK;
        root = node;
        return;
    }
    RBTNode *curr = root;
    while (true) {
        if (node->data < curr->data) {
            if (!curr->left) {
                curr->left = node;
                break;
            }
            curr = curr->left;
        } else {
            if (!curr->right) {
                curr->right = node;
                break;
            }
            curr = curr->right;
        }
    }
    node->parent = curr;
}

void RedBlackTree::InsertFixUp(RBTNode *node) {
    while (node != root && node->parent->color == COLOR_RED) {
        RBTNode *grandparent = node->parent->parent;
        if (IsLeftChild(node->parent)) {
            RBTNode *uncle = grandparent->right;
            if (uncle && uncle->color == COLOR_RED) {
                node->parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                node = grandparent;
            } else {
                if (IsRightChild(node)) {
                    node = node->parent;
                    LeftRotate(node);
                }
                node->parent->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                RightRotate(grandparent);
            }
        } else {
            RBTNode *uncle = grandparent->left;
            if (uncle && uncle->color == COLOR_RED) {
                node->parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                node = grandparent;
            } else {
                if (IsLeftChild(node)) {
                    node = node->parent;
                    RightRotate(node);
                }
                node->parent->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                LeftRotate(grandparent);
            }
        }
    }
    root->color = COLOR_BLACK;
}

bool RedBlackTree::Contains(int data) const {
    return Get(data) != nullptr;
}

RBTNode* RedBlackTree::Get(int data) const {
    RBTNode *curr = root;
    while (curr) {
        if (data == curr->data) return curr;
        curr = (data < curr->data) ? curr->left : curr->right;
    }
    return nullptr;
}

int RedBlackTree::GetMin() const {
    if (!root) throw invalid_argument("Tree is empty");
    RBTNode *curr = root;
    while (curr->left) curr = curr->left;
    return curr->data;
}

int RedBlackTree::GetMax() const {
    if (!root) throw invalid_argument("Tree is empty");
    RBTNode *curr = root;
    while (curr->right) curr = curr->right;
    return curr->data;
}

void RedBlackTree::LeftRotate(RBTNode *x) {
    RBTNode *y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (IsLeftChild(x)) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void RedBlackTree::RightRotate(RBTNode *x) {
    RBTNode *y = x->left;
    x->left = y->right;
    if (y->right) y->right->parent = x;
    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (IsRightChild(x)) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

string RedBlackTree::ToInfixString(const RBTNode *n) {
    if (!n) return "";
    return ToInfixString(n->left) + GetNodeString(n) + ToInfixString(n->right);
}

string RedBlackTree::ToPrefixString(const RBTNode *n) {
    if (!n) return "";
    return GetNodeString(n) + ToPrefixString(n->left) + ToPrefixString(n->right);
}

string RedBlackTree::ToPostfixString(const RBTNode *n) {
    if (!n) return "";
    return ToPostfixString(n->left) + ToPostfixString(n->right) + GetNodeString(n);
}

string RedBlackTree::GetNodeString(const RBTNode *n) {
    if (!n) return "";
    stringstream ss;
    ss << " " << (n->color == COLOR_RED ? "R" : "B") << n->data << " ";
    return ss.str();
}

bool RedBlackTree::IsLeftChild(RBTNode *n) const {
    return n->parent && n->parent->left == n;
}

bool RedBlackTree::IsRightChild(RBTNode *n) const {
    return n->parent && n->parent->right == n;
}
