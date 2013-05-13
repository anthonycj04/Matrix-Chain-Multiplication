#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

void printOptimalParens(vector<int>** index, int i, int j, vector<string>* results, int resultNum, bool printOut){
	if (i == j){
		stringstream ss;
		ss << i;
		results->at(resultNum).append("A" + ss.str());
	}
	else{
		string origString = results->at(resultNum);
		for (int l = 0; l < index[i][j].size(); l++){
		// for (int l = 0; l < 1; l++){
			if (l == 0){
				results->at(resultNum).append("(");
				printOptimalParens(index, i, index[i][j][l], results, resultNum, false);
				printOptimalParens(index, index[i][j][l] + 1, j, results, resultNum, false);
				results->at(resultNum).append(")");
			}
			else{
				int newResultNum;
				string tempString = origString;
				newResultNum = results->size();
				results->push_back(tempString);
				results->at(newResultNum).append("(");
				printOptimalParens(index, i, index[i][j][l], results, newResultNum, false);
				printOptimalParens(index, index[i][j][l] + 1, j, results, newResultNum, false);
				results->at(newResultNum).append(")");
			}
		}
	}

	if (printOut){
		for (int i = 0; i < results->size(); i++)
			cout << results->at(i) << endl;
	}
}

void mcm(const vector<int>& p){
	int numOfArrays = p.size() - 1;
	int** multiplications = new int*[numOfArrays + 1];
	vector<int>**  index = new vector<int>*[numOfArrays + 1]();
	for (int i = 0; i <= numOfArrays; i++){
		multiplications[i] = new int[numOfArrays + 1];
		index[i] = new vector<int>[numOfArrays + 1]();
	}

	for (int i = 1; i <= numOfArrays; i++)
		multiplications[i][i] = 0;
	for (int length = 2; length <= numOfArrays; length++){
		for (int i = 1; i <= numOfArrays - length + 1; i++){
			int j = i + length - 1;
			multiplications[i][j] = 99999999;

			int* multiplicationRecord = new int[j - i];
			for (int k = i; k <= j - 1; k++){
				int temp = multiplications[i][k] + multiplications[k + 1][j] + p[i - 1] * p[k] * p[j];
				multiplicationRecord[k - i] = temp;
				if (temp < multiplications[i][j]){
					multiplications[i][j] = temp;
					// index[i][j].push_back(k);
				}
			}
			for (int k = i; k <= j - 1; k++){
				if (multiplicationRecord[k - i] == multiplications[i][j])
					index[i][j].push_back(k);
			}
			delete [] multiplicationRecord;
		}
	}

	cout << multiplications[1][numOfArrays] << endl;

	// for (int i = 1; i <= numOfArrays; i++){
	// 	for (int j = i; j <= numOfArrays; j++)
	// 		cout << multiplications[i][j] << ' ';
	// 	cout << endl;
	// }
	// cout << endl;
	for (int i = 1; i <= numOfArrays; i++){
		for (int j = i; j <= numOfArrays; j++){
			for (int k = 0; k < index[i][j].size(); k++)
				cout << index[i][j][k] << ", ";
			cout << "; ";
		}
		cout << endl;
	}

	vector<string>* results = new vector<string>();
	// results->push_back(new string());
	results->push_back("");
	printOptimalParens(index, 1, numOfArrays, results, 0, true);
	delete results;

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
	cout << endl;
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
