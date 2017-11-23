#include <bits/stdc++.h>
#define MAX 10

using namespace std;

void printMenu(){
	cout << "\n\n######################################################" << endl;
	cout << " Link state routing simulation " << endl;
	cout << " (1) - Input network topology" << endl;
	cout << " (2) - Build connection table" << endl;
	cout << " (3) - Show the shortesst path to destination router " << endl;
	cout << " (4) - Exit " << endl;
	cout << "######################################################" << endl << endl;
}

void getUserChoice(){
	int inputValue;
	
	while(true){
		printMenu();
		cin >> inputValue;
		switch(inputValue){
			case 1: {
				cout << "Insert filename: ";
				string fn;
				cin >> fn;
				vector<vector<int>> buildNetwork(string filename);
				void printMatrix(vector<vector<int>> routerMatrix);
				cout << endl;
				vector<vector<int>> network = buildNetwork(fn);
				printMatrix(network);
				break;
			}
			case 2: {
				break;
			}
			case 3:
				break;
			case 4:
				exit(0);
				break;
			default:
				cout << "Insert a valid option" << endl;
		}
	}
}

int matrixSet = 0;
//int routerMatrix[10][10];

vector<vector<int>> buildNetwork(string filename){
	ifstream file(filename);
	vector<vector<int>> routerMatrix;
	if(file.is_open()){
		string line;
		int i = 0;
		while(getline(file, line)){
			istringstream iss(line);
			vector<string> tokens{
				istream_iterator<string>{iss},
				istream_iterator<string>{}
			};

			vector<int> col;
			int j = 0;
			for(auto n : tokens){
				col.push_back(stoi(n));
				j++;
			}
			routerMatrix.push_back(col);
			i++;
		}
		void setDistances(vector<vector<int>> routerMatrix);
		setDistances(routerMatrix);
	}
	else{
		cout << "Unable to open file" << endl;
		exit(1);
	}
	return routerMatrix;
}

map<int, map<int, int>> distances;
vector<int> nodes;

void setDistances(vector<vector<int>> routerMatrix){
	for(int i = 0; i < routerMatrix.size(); i++){
		map<int, int> tmp;
		// to na duvida se é ate routerMatrix[i].size(), n
		// sei se o cara so resolve NxN, la ta sem o i.
		for(int j = 0; j < routerMatrix[i].size(); j++){
			if(i != j and routerMatrix[i][j] != - 1){
				tmp[j+1] = routerMatrix[i][j];
			}
		}
		distances[i+1] = tmp;
		nodes.push_back(i+1);
	}
}

void printMatrix(vector<vector<int>> routerMatrix){
	for(int i = 0; i < routerMatrix.size(); i++){
		for(int j = 0; j < routerMatrix[i].size(); j++){
			cout << routerMatrix[i][j] << " ";
		}
		cout << endl;
	}
}



int main(){
	getUserChoice();

	return 0;
}
