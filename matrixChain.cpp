#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <climits>

using namespace std;

void printOptimalParens(vector<int>** index, int i, int j, int* undiscoveredPath, int* path, int* level, string* results){
	if (i == j){
		stringstream ss;
		ss << i;
		results->append("A" + ss.str());
	}
	else{
		int tempLevel = ++(*level);
		results->append("(");
		if (index[i][j].size() - 1 > path[tempLevel]){
			undiscoveredPath[0] = tempLevel;
			undiscoveredPath[1] = path[tempLevel] + 1;
		}
		printOptimalParens(index, i, index[i][j][path[tempLevel]], undiscoveredPath, path, level, results);
		printOptimalParens(index, index[i][j][path[tempLevel]] + 1, j, undiscoveredPath, path, level, results);
		results->append(")");
	}
}

void mcm(const vector<int>& p){
	int numOfArrays = p.size() - 1;
	int** multiplications = new int*[numOfArrays + 1]; //saves the number of multiplicationsto multiply the matrixes
	vector<int>**  index = new vector<int>*[numOfArrays + 1](); // where to do the multiplication first
	for (int i = 0; i <= numOfArrays; i++){
		multiplications[i] = new int[numOfArrays + 1];
		index[i] = new vector<int>[numOfArrays + 1]();
	}

	// just the algorithm from the text book
	for (int i = 1; i <= numOfArrays; i++)
		multiplications[i][i] = 0;
	for (int length = 2; length <= numOfArrays; length++){
		for (int i = 1; i <= numOfArrays - length + 1; i++){
			int j = i + length - 1;
			multiplications[i][j] = INT_MAX;//99999999;

			// do the calculation as usual, but instead of recording one best solution, save the number of multiplications down of each cut for later use
			int* multiplicationRecord = new int[j - i];
			for (int k = i; k <= j - 1; k++){
				int temp = multiplications[i][k] + multiplications[k + 1][j] + p[i - 1] * p[k] * p[j];
				multiplicationRecord[k - i] = temp;
				if (temp < multiplications[i][j])
					multiplications[i][j] = temp;
			}
			// run through the saved data and add those that fits in the solution
			for (int k = i; k <= j - 1; k++){
				if (multiplicationRecord[k - i] == multiplications[i][j])
					index[i][j].push_back(k);
			}
			delete [] multiplicationRecord;
		}
	}

	cout << multiplications[1][numOfArrays] << " scalar multiplications" << endl;

	int undiscoveredPath[2] = {0}; // records the undiscovered route with : {level, new path}
	int numOfOptimalWays = 0, level;
	int* path = new int[numOfArrays]; // records the route of the next walk
	string results = "";
	for (int i = 0; i < numOfArrays; i++)
		path[i] = 0;
	do {
		numOfOptimalWays++;
		level = -1;
		path[undiscoveredPath[0]] = undiscoveredPath[1];
		for (int i = undiscoveredPath[0] + 1; i < numOfArrays; i++)
			path[i] = 0;
		undiscoveredPath[0] = -1;
		printOptimalParens(index, 1, numOfArrays, undiscoveredPath, path, &level, &results);
		results.append("\n");
	} while (undiscoveredPath[0] != -1);
	cout << numOfOptimalWays << " optimal ways to multiply" << endl;
	cout << results << endl;

	delete [] path;
	for (int i = 0; i < numOfArrays; i++){
		delete [] multiplications[i];
		delete [] index[i];
	}
	delete [] multiplications;
	delete [] index;
}

void testing_mcm(const vector<int>& p){
	static int test = 0;
	cout << "Test " << ++test << " ..." << endl;
	mcm(p);
}

int main(){
	testing_mcm({30, 42, 15, 5, 10, 20, 25});
	testing_mcm({3, 3, 3, 3, 3});
	testing_mcm({2, 2, 3, 2, 2, 3, 3, 2});

	return 0;
}
/*
Test 1  ... 
15125 scalar multiplications
1 optimal way to multiply
((A1(A2A3))((A4A5)A6))

Test 2  ...
81 scalar multiplications
5 optimal ways to multiply
(A1(A2(A3A4)))
(A1((A2A3)A4))
((A1A2)(A3A4))
((A1(A2A3))A4)
(((A1A2)A3)A4)

Test 3  ...
66 scalar multiplications
10 optimal ways to multiply
(A1((A2A3)(A4(A5(A6A7)))))
(A1((A2A3)(A4((A5A6)A7))))
(A1(((A2A3)A4)(A5(A6A7))))
(A1(((A2A3)A4)((A5A6)A7)))
((A1(A2A3))(A4(A5(A6A7))))
((A1(A2A3))(A4((A5A6)A7)))
((A1((A2A3)A4))(A5(A6A7)))
((A1((A2A3)A4))((A5A6)A7))
(((A1(A2A3))A4)(A5(A6A7)))
(((A1(A2A3))A4)((A5A6)A7))
*/
