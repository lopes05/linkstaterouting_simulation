#include <bits/stdc++.h>
#define MAX 10
#define MAX_VAL INT_MAX

using namespace std;

void printMenu(){
    cout << "\n\n######################################################" << endl;
    cout << " Link state routing simulation " << endl;
    cout << " (1) - Input network topology" << endl;
    cout << " (2) - Show results" << endl;
    cout << " (3) - Exit " << endl;
    cout << "######################################################" << endl << endl;
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
    }
    else{
        cout << "Unable to open file" << endl;
        exit(1);
    }
    return routerMatrix;
}

void printMatrix(vector<vector<int>> routerMatrix){
    for(int i = 0; i < routerMatrix.size(); i++){
        for(int j = 0; j < routerMatrix[i].size(); j++){
            cout << routerMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

int minDistance(vector<int> dist, bool sptSet[]){
   int min = INT_MAX, min_index;
  
   for (int v = 0; v < dist.size(); v++)
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;
  
   return min_index;
}

void printPath(vector<int> parent, int end){
	if (parent[end]==-1){
        return;
	}
    printPath(parent, parent[end]);
 
    printf("%d ", end);
}

void printSolution(vector<int> dist, vector<int> parent, int src){
    printf("Vertex\t  Distance\tPath");
    for(int i = 0; i < src; i++){
    	if(dist[i] != MAX_VAL){
        	printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src);
        	printPath(parent, i);
        }
        else{
        	printf("\n(No connection between this routers)\n" );
        }
    }

    for(int i = src + 1; i < dist.size(); i++){
        if(dist[i] != MAX_VAL){
        	printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src);
        	printPath(parent, i);
        }
        else{
        	printf("\n(No connection between this routers)\n");
        }
    }
}

void dijkstra(vector<vector<int>> routerMatrix, int src){
    const int len = routerMatrix.size();
    vector<int> dist(len);
  
    bool visited[len];
    vector<int> parent(len);

    for (int i = 0; i < len; i++){
        dist[i] = MAX_VAL;
        visited[i] = false;
        parent[0] = -1;
    }
  	parent[src] = -1;
    dist[src] = 0;

	for (int i = 0; i < len-1; i++){
	    int u = minDistance(dist, visited);
	    visited[u] = true;
		    for (int v = 0; v < len; v++){
			    if (!visited[v] && routerMatrix[u][v] && dist[u] != INT_MAX 
	          && dist[u]+routerMatrix[u][v] < dist[v] && routerMatrix[u][v] != -1){
			   	parent[v] = u;
	        	dist[v] = dist[u] + routerMatrix[u][v];
			}
		}
	}
  
    printSolution(dist, parent, src);

}

void getUserChoice(){
    int inputValue, start;
    vector<vector<int>> network;
    bool fileloaded = false;
    while(true){
        printMenu();
        cin >> inputValue;
        switch(inputValue){
            case 1: {
                cout << "Insert filename with a matrix(NxN): ";
                string fn;
                cin >> fn;
                vector<vector<int>> buildNetwork(string filename);
                void printMatrix(vector<vector<int>> routerMatrix);
                cout << endl;
                network = buildNetwork(fn);
                printMatrix(network);
                fileloaded = true;
                break;
            }
            case 2: {
            	if(fileloaded){
                	cout << "Insert initial node (0~" << network.size() - 1 << "): ";
                	cin >> start;
                	cout << endl;
                	dijkstra(network, start);
            	}
            	else{
            		cout << "Please enter a file first" << endl;
            	}
                break;
            }
            case 3:
                exit(0);
                break;
            default:
                cout << "Insert a valid option" << endl;
        }
    }
}

int main(){
    getUserChoice();
    return 0;
}
