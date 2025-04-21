// Author: Minh Pham
// Date: 04/20/2025

#include <iostream>
#include <cassert>
#include "RedBlackTree.h"

/**
 * This file provides the very first tests to ensure
 * basic construction and single-node insertion work correctly.
 * 
 * Specifically useful for verifying:
 *  - Default constructor (empty tree)
 *  - Insert() when adding the very first node
 *  - ToInfixString() string output formatting for single-node case
 * 
 * These tests should be used to debug before the full suite of tests
 * in RedBlackTreeTests.cpp is run.
 */

using namespace std;

// Tests whether the default constructor creates an empty tree
void TestSimpleConstructor(){
	cout << "Testing Simple Constructor... " << endl;
	RedBlackTree rbt = RedBlackTree();
	assert(rbt.ToInfixString() == ""); // no nodes = empty string
	cout << "PASSED!" << endl << endl;
}

// Tests insertion of the first node (should become black root)
// Also validates ToInfixString returns correct color and value format
void TestInsertFirstNode(){
	cout << "Testing Insert One Node..." << endl;
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	assert(rbt.ToInfixString() == " B30 "); // inserted value must be black root
	cout << "PASSED!" << endl << endl;
}

// Run both early-stage tests
int main(){
	TestSimpleConstructor();
	TestInsertFirstNode();
	cout << "ALL TESTS PASSED!!" << endl;
	return 0;
}
