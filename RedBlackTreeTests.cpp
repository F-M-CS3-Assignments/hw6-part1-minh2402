// Author: Minh Pham
// Date: 04/20/2025

#include <iostream>
#include <cassert>
#include <random>
#include "RedBlackTree.h"

using namespace std;

// Sanity check for default constructor — tree should start empty
void TestSimpleConstructor(){
	cout << "Testing Simple Constructor... " << endl;
	RedBlackTree rbt = RedBlackTree();
	assert(rbt.ToInfixString() == "");
	cout << "PASSED!"<< endl << endl;
}

// Constructor with one value should create a valid black root
void TestConstructor(){
	cout << "Testing Constructor W/Int Input..." << endl;
	RedBlackTree rbt = RedBlackTree(15);
	assert(rbt.ToPrefixString() == " B15 ");
	cout << "PASSED!"<< endl << endl;
}

// Insert one value — should become black root automatically
void TestInsertFirstNode(){
	cout << "Testing Insert One Node..." << endl;
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	assert(rbt.ToPrefixString() == " B30 ");
	cout << "PASSED!" << endl << endl;
}

// Two-node insert tests both left and right child cases — verifies red coloring of child
void TestInsertSecondNode(){
	cout << "Testing Insert Second Node..." << endl;

	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15); // left child
	assert(rbt->ToPrefixString() == " B30  R15 ");
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45); // right child
	assert(rbt->ToPrefixString() == " B30  R45 ");
	delete rbt;

	cout << "PASSED!" << endl << endl;
}

// Covers four key balancing cases: LL, LR, RL, RR
// Helps verify rotations + recoloring are handled correctly
void TestInsertThirdNode(){
	cout << "Testing Insert Third Node..." << endl;

	// Left-Left (causes single right rotation)
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(10);
	assert(rbt->ToPrefixString() == " B15  R10  R30 ");
	delete rbt;

	// Right-Left (requires right then left rotation)
	rbt = new RedBlackTree(); 
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(25);
	assert(rbt->ToPrefixString() == " B25  R15  R30 ");
	delete rbt;

	// Left-Right (requires left then right rotation)
	rbt = new RedBlackTree(); 
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(20);
	assert(rbt->ToPrefixString() == " B20  R15  R30 ");
	delete rbt;

	// Right-Right (causes single left rotation)
	rbt = new RedBlackTree(); 
	rbt->Insert(30);
	rbt->Insert(45);
	rbt->Insert(60);
	assert(rbt->ToPrefixString() == " B45  R30  R60 ");
	delete rbt;

	cout << "PASSED!" << endl << endl;
}

// Placeholder — you can test 4-node trees here for more complex balancing
void TestInsertFourthNode(){
	cout << "Testing Insert Fourth Node..." << endl;

	cout << "TESTS MISSING" << endl << endl;
	cout << "PASSED!" << endl << endl;
}

// Verifies tree size and color structure after inserting 5 nodes
// Based on a known-good example from lecture/visualizer
void TestInsertFifthNode(){
	cout << "Testing Insert Fifth Node..." << endl;

	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(10);
	rbt->Insert(25);
	assert(rbt->ToPrefixString() == " B30  B15  R10  R25  B45 ");
	delete rbt;

	cout << "TESTS MISSING" << endl << endl;
	cout << "PASSED!" << endl << endl;
}

// Verifies all traversal orders match expected tree shape
void TestToStrings(){
	cout << "Testing ToString Methods..." << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(12);
	rbt.Insert(11);
	rbt.Insert(15);
	rbt.Insert(5);
	rbt.Insert(13);
	rbt.Insert(7);

	assert(rbt.ToPrefixString() == " B12  B7  R5  R11  B15  R13 ");
	assert(rbt.ToInfixString() == " R5  B7  R11  B12  R13  B15 ");
	assert(rbt.ToPostfixString() == " R5  R11  B7  R13  B15  B12 ");

	cout << "PASSED!" << endl << endl;
}

// Does not test logic — just ensures inserts don't crash
// Run with valgrind to check for leaks
void TestInsertRandomTests(){
	cout << "Testing Random Insert Stuff..." << endl;
	cout << "\t This test passes if it doesn't crash and valgrind reports no issues" << endl;

	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(15);
	rbt->Insert(13);
	rbt->Insert(20);
	rbt->Insert(12);
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(12);
	rbt->Insert(11);
	rbt->Insert(15);
	rbt->Insert(5);
	rbt->Insert(13);
	rbt->Insert(7);
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(12);
	rbt->Insert(10);
	rbt->Insert(8);
	delete rbt;

	cout << "PASSED!" << endl << endl;
}

// Tests deep copy and pointer independence between two trees
void TestCopyConstructor(){
	cout << "Testing Copy Constructor..." << endl;

	RedBlackTree rbt1 = RedBlackTree();
	rbt1.Insert(11);
	rbt1.Insert(23);
	rbt1.Insert(9);
	rbt1.Insert(52);
	rbt1.Insert(31);
	rbt1.Insert(4);
	assert(rbt1.ToPrefixString() == " B11  B9  R4  B31  R23  R52 ");

	RedBlackTree rbt2 = RedBlackTree(rbt1);
	assert(rbt2.ToPrefixString() == rbt1.ToPrefixString());

	rbt1.Insert(200); // mutate original
	assert(rbt2.ToPrefixString() != rbt1.ToPrefixString()); // copy must stay same

	cout << "PASSED!" << endl << endl;
}

// Tests whether search (Contains) returns accurate results
void TestContains(){
	cout << "Testing Contains..." << endl;

	RedBlackTree *rbt = new RedBlackTree();
	assert(rbt->Contains(6) == false); // tree is empty
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(40);
	rbt->Insert(22);
	rbt->Insert(15);
	rbt->Insert(31);
	rbt->Insert(55);
	rbt->Insert(12);
	rbt->Insert(17);
	rbt->Insert(29);
	rbt->Insert(34);
	assert(rbt->Contains(34)); // test for existing value
	delete rbt;

	cout << "TESTS MISSING" << endl << endl;
	cout << "PASSED!" << endl << endl;
}

// Placeholder — implement tests for GetMin() and GetMax()
void TestGetMinimumMaximum(){
	cout << "Testing Get Minimum and Get Maximum..." << endl;

	cout << "TESTS MISSING" << endl << endl;
	cout << "PASSED!" << endl << endl;
}

// Run all tests
int main(){
	TestSimpleConstructor();
	TestConstructor();
	TestInsertFirstNode();
	TestInsertSecondNode();
	TestInsertThirdNode();
	TestInsertFourthNode();
	TestInsertFifthNode();
	TestToStrings();
	TestInsertRandomTests();
	TestCopyConstructor();
	TestContains();
	TestGetMinimumMaximum();

	cout << "ALL TESTS PASSED!!" << endl;
	return 0;
}
