// Author: Minh Pham
// Date: 04/20/2025

#include "RedBlackTree.h"
#include <stdexcept>
#include <sstream>

// Default constructor — starts with empty tree
RedBlackTree::RedBlackTree() {
	root = nullptr;
	numItems = 0;
}

// One-node constructor — useful for testing
RedBlackTree::RedBlackTree(int newData) {
	root = new RBTNode(newData, COLOR_BLACK); // Root is always black in a valid RBT
	numItems = 1;
}

// Copy constructor — recursively duplicates all nodes
RedBlackTree::RedBlackTree(const RedBlackTree &rbt) {
	root = CopyOf(rbt.root);
	numItems = rbt.numItems;
}

// Recursively copies an RBT subtree
RBTNode *RedBlackTree::CopyOf(const RBTNode *node) {
	if (node == nullptr) return nullptr;

	RBTNode *copy = new RBTNode(node->data, node->color);
	copy->IsNullNode = node->IsNullNode;

	copy->left = CopyOf(node->left);
	if (copy->left) copy->left->parent = copy;

	copy->right = CopyOf(node->right);
	if (copy->right) copy->right->parent = copy;

	return copy;
}

// Insert a new value into the tree
void RedBlackTree::Insert(int newData) {
	// Avoid duplicate keys — required by assignment spec
	if (Contains(newData)) throw invalid_argument("Duplicate value");

	RBTNode *newNode = new RBTNode(newData, COLOR_RED); // New node is always red
	BasicInsert(newNode);     // Insert as if BST
	InsertFixUp(newNode);     // Restore RBT rules
	numItems++;
}

// Binary search tree insert (no balancing)
void RedBlackTree::BasicInsert(RBTNode *node) {
	if (root == nullptr) {
		// Special case — first node becomes black root
		node->color = COLOR_BLACK;
		root = node;
		return;
	}

	RBTNode *curr = root;
	while (true) {
		if (node->data < curr->data) {
			if (curr->left == nullptr) {
				curr->left = node;
				break;
			}
			curr = curr->left;
		} else {
			if (curr->right == nullptr) {
				curr->right = node;
				break;
			}
			curr = curr->right;
		}
	}
	node->parent = curr;
}

// Fixes red-black violations after insert
// Algorithm follows standard RBT insert fix logic (ZyBook 16.3.1, Lecture @ 15:52)
void RedBlackTree::InsertFixUp(RBTNode *node) {
	while (node != root && node->parent->color == COLOR_RED) {
		RBTNode *grandparent = node->parent->parent;

		// Parent is left child
		if (IsLeftChild(node->parent)) {
			RBTNode *uncle = grandparent->right;

			// Case 1: Uncle is red — push blackness down
			if (uncle && uncle->color == COLOR_RED) {
				node->parent->color = COLOR_BLACK;
				uncle->color = COLOR_BLACK;
				grandparent->color = COLOR_RED;
				node = grandparent; // Repeat upward
			} else {
				// Case 2: Node is right child — rotate to prepare for case 3
				if (IsRightChild(node)) {
					node = node->parent;
					LeftRotate(node);
				}
				// Case 3: Rotate and recolor
				node->parent->color = COLOR_BLACK;
				grandparent->color = COLOR_RED;
				RightRotate(grandparent);
			}
		}
		// Parent is right child
		else {
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

// Check for membership
bool RedBlackTree::Contains(int data) const {
	return Get(data) != nullptr;
}

// Search helper
RBTNode *RedBlackTree::Get(int data) const {
	RBTNode *curr = root;
	while (curr) {
		if (data == curr->data) return curr;
		curr = (data < curr->data) ? curr->left : curr->right;
	}
	return nullptr;
}

// Returns minimum value by traversing left
int RedBlackTree::GetMin() const {
	if (!root) throw invalid_argument("Tree is empty");
	RBTNode *curr = root;
	while (curr->left) curr = curr->left;
	return curr->data;
}

// Returns maximum value by traversing right
int RedBlackTree::GetMax() const {
	if (!root) throw invalid_argument("Tree is empty");
	RBTNode *curr = root;
	while (curr->right) curr = curr->right;
	return curr->data;
}

// Left rotation (ZyBook 16.3.2 and standard RBT sources)
// Used to rebalance when right-heavy
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

// Right rotation — mirror of LeftRotate
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

// Traversal functions used for tree validation
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

// Formats a node's value + color as a string, e.g., " R15 "
string RedBlackTree::GetNodeString(const RBTNode *n) {
	if (!n) return "";
	stringstream ss;
	ss << " " << (n->color == COLOR_RED ? "R" : "B") << n->data << " ";
	return ss.str();
}

// True if node is a left child of its parent
bool RedBlackTree::IsLeftChild(RBTNode *n) const {
	return n->parent && n->parent->left == n;
}

// True if node is a right child of its parent
bool RedBlackTree::IsRightChild(RBTNode *n) const {
	return n->parent && n->parent->right == n;
}
