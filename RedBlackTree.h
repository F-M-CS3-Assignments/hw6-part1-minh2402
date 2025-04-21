#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#define COLOR_RED 0
#define COLOR_BLACK 1
#define COLOR_DOUBLE_BLACK 2

#include <iostream>
#include <string>
using namespace std;

struct RBTNode {
	int data;
	unsigned short int color;
	RBTNode *left;
	RBTNode *right;
	RBTNode *parent;
	bool IsNullNode;

	// Custom constructor
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
		RedBlackTree();
		RedBlackTree(int newData);
		RedBlackTree(const RedBlackTree &rbt);

		string ToInfixString() const {return ToInfixString(root);};
		string ToPrefixString() const { return ToPrefixString(root);};
		string ToPostfixString() const { return ToPostfixString(root);};

		void Insert(int newData);
		bool Contains(int data) const;
		size_t Size() const {return numItems;};
		int GetMin() const;
		int GetMax() const;

	private: 
		unsigned long long int numItems = 0;
		RBTNode *root = nullptr;
		
		static string ToInfixString(const RBTNode *n);
		static string ToPrefixString(const RBTNode *n);
		static string ToPostfixString(const RBTNode *n);
		static string GetColorString(const RBTNode *n);
		static string GetNodeString(const RBTNode *n);

		void BasicInsert(RBTNode *node);
		void InsertFixUp(RBTNode *node);

		RBTNode *GetUncle(RBTNode *node) const;
		bool IsLeftChild(RBTNode *node) const;
		bool IsRightChild(RBTNode *node) const;

		void LeftRotate(RBTNode *node);
		void RightRotate(RBTNode *node);
		RBTNode *CopyOf(const RBTNode *node);
		RBTNode *Get(int data) const;
};

#endif
