// Author: Minh Pham
// Date: 04/20/2025

#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#define COLOR_RED 0
#define COLOR_BLACK 1
#define COLOR_DOUBLE_BLACK 2

#include <iostream>
#include <string>
using namespace std;

// Struct representing a node in the red-black tree
struct RBTNode {
	int data;
	unsigned short int color;
	RBTNode *left;
	RBTNode *right;
	RBTNode *parent;
	bool IsNullNode;

	// Constructor used to ensure correct initialization
	RBTNode(int d, unsigned short int c) {
		data = d;
		color = c;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		IsNullNode = false;
	}
};

class RedBlackTree {
	
	public:
		RedBlackTree(); // Default constructor
		RedBlackTree(int newData); // Constructor to create a one-node tree
		RedBlackTree(const RedBlackTree &rbt); // Deep copy constructor

		// Traversal string methods used to verify tree structure in tests
		string ToInfixString() const { return ToInfixString(root); };
		string ToPrefixString() const { return ToPrefixString(root); };
		string ToPostfixString() const { return ToPostfixString(root); };

		// Core public API
		void Insert(int newData); // Insert while preserving RBT properties
		bool Contains(int data) const; // Returns true if data is in the tree
		size_t Size() const { return numItems; }; // Total # of nodes
		int GetMin() const; // Minimum value in tree
		int GetMax() const; // Maximum value in tree

	private: 
		unsigned long long int numItems = 0;
		RBTNode *root = nullptr;

		// Recursive helper traversal functions
		static string ToInfixString(const RBTNode *n);
		static string ToPrefixString(const RBTNode *n);
		static string ToPostfixString(const RBTNode *n);
		static string GetColorString(const RBTNode *n);
		static string GetNodeString(const RBTNode *n);

		// Helpers for insertion
		void BasicInsert(RBTNode *node); // Simple BST insert
		void InsertFixUp(RBTNode *node); // RBT rule fix (rotations, recolors)

		// Utilities for RBT property maintenance
		RBTNode *GetUncle(RBTNode *node) const;
		bool IsLeftChild(RBTNode *node) const;
		bool IsRightChild(RBTNode *node) const;

		void LeftRotate(RBTNode *node);  // Rotate node left
		void RightRotate(RBTNode *node); // Rotate node right

		// Deep copy helper
		RBTNode *CopyOf(const RBTNode *node);

		// Search helper
		RBTNode *Get(int data) const;
};

#endif
