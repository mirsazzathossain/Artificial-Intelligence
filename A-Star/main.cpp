#include<bits/stdc++.h>

using namespace std;

vector<vector<pair<int, int>>>adjList;
vector<int>heuristic;
vector<char>dictionary;

void aStar(int source, int destination){
    string path = "";
    path += to_string(source);
    int cost = heuristic[source];

    map<int, string>frontier;
    frontier.insert(make_pair(cost, path));

    while(true){
        map<int, string>::iterator itr;
        itr = frontier.begin();
        cost = itr->first;
        path = itr->second;
        int index = path.length();

        int u = (int)path[index-1]-48;
        frontier.erase(itr);
        cost -= heuristic[u];
        

        if(u == destination){
            for(int i=0; i<path.length(); i++){
                int j = (int)path[i] - 48;
                cout<<dictionary[j];
            }
            cout<<" is the best path costing: "<<cost<<endl;
            break;
        }

        for(int i=0; i<adjList[u].size(); i++){
            int v = adjList[u][i].first;
            int newCost = cost + adjList[u][i].second + heuristic[v];
            frontier.insert(make_pair(newCost, path+to_string(v)));
        }

    }

}

int main(){

    fstream fin("input.txt");

    int vertices, edges;
    fin>>vertices>>edges;
    adjList.resize(vertices);

    int u, v, w;
    for(int i=0; i<edges; i++){
        fin>>u>>v>>w;
        adjList[u].push_back(make_pair(v, w));
    }

    dictionary.resize(vertices);

    for(int i=0; i<vertices; i++){
        fin>>dictionary[i];
    }

    heuristic.resize(vertices);

    for(int i=0; i<vertices; i++){
        fin>>heuristic[i];
        //cout<<heuristic[i]<<endl;
    }

    int source, destination;
    fin>>source>>destination;

    aStar(source, destination);




/*
    //Print Adjacency List
    for(int i=0; i<adjList.size(); i++){
        cout<<i<<" -> ";
        for(int j=0; j<adjList[i].size(); j++){
            cout<<adjList[i][j].first<<","<<adjList[i][j].second<<" ";
        }
        cout<<endl;
    }
*/
    return 0;
}