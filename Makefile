all:
	g++ -std=c++11 RedBlackTree.cpp RedBlackTreeTestsFirstStep.cpp -o rbt-first
	g++ -std=c++11 RedBlackTree.cpp RedBlackTreeTests.cpp -o rbt-full

run:
	./rbt-first
	./rbt-full

try: all run
