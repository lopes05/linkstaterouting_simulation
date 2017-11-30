#include <bits/stdc++.h>
#define MAX 10
#define MAX_VAL 32000

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
vector<int> unvisited;
vector<int> previous;
vector<int> visited;
vector<int> interface;

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
        distances[i] = tmp;
        nodes.push_back(i);
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

bool done(){
    for(auto ni: unvisited)
        if(ni)
            return false;

    return true;
}

void djikstra(int start){
    unvisited = vector<int>(nodes.size());
    previous = vector<int>(nodes.size());
    interface = vector<int>(nodes.size());
    visited = vector<int>(nodes.size());

    int current = start, current_dist = 0, next, dist;

    unvisited[current] = current_dist;

    while(true){
        for(auto const& dists: distances[current]){

            next = dists.first;
            dist = dists.second;

            map<int, int>::iterator it2 = distances[current].find(next);

            if(it2 == distances[current].end())
                continue;

            int new_dist = current_dist + dist;

            if(not unvisited[next] or unvisited[next] > new_dist){
                unvisited[next] = new_dist;
                previous[next] = current;

                if(not interface[current])
                    interface[next] = next;
                else
                    interface[next] = interface[current];
            }
        }

        visited[current] = current_dist;

        if(unvisited.empty() or done())
            break;

        unvisited.erase(unvisited.begin() + current);

        current_dist = MAX_VAL;

        for(int i = 0; i < unvisited.size(); i++)
            if(unvisited[i] < current_dist){
                current = i;
                current_dist = unvisited[i];
            }

    }
}

void shortest_path(int start, int end){

    int dest = end, src = start;
    vector<int> path;

    path.push_back(dest);

    while(dest != src){
        path.push_back(previous[dest]);
        dest = previous[dest];
    }

    cout << "The shortes path between " << start << "and " << end << "is: " << endl;
    for(int i = path.size()-1; i >=0; --i)
        cout << path[i] << '\t';

    cout << endl;
}

void getUserChoice(){
    int inputValue, start;

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
                cout << "Insert initial node" << endl;
                cin >> start;
                djikstra(start);
                for(auto key : interface)
                    cout << key << "\t\t" << interface[key] << endl;
                break;
            }
            case 3:
                cout << "Insert final node" << endl;
                int end;
                cin >> end;
                shortest_path(start, end);
                break;
            case 4:
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
