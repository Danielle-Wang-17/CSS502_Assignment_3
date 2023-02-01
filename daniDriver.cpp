#include <iostream>
#include <fstream>
// #include "graphl.h"
#include "graphm.h"
using namespace std;

int main() {
    // part 1
	ifstream infile1("data31.txt");
	if (!infile1) {
		cout << "File could not be opened." << endl;
		return 1;
	}

    GraphM G;
    G.buildGraph(infile1);
}