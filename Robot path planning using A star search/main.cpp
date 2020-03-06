#include<bits/stdc++.h>

using namespace std;

//Inputs
#define sfi(x) scanf("%d", &x)
#define sfl(x) scanf("%ld", &x)
#define sfd(x) scanf("%lf", &x)
#define sfc(x) scanf("%c", &x)
#define sfs(x) getline(cin, x);
#define in(x) cin>>x;
//Outputs
#define pfi(x) printf("%d", x)
#define pfl(x) printf("%ld", x)
#define pfd(x) printf("%lf", x)
#define pfc(x) printf("%c", x)
#define out(x) cout<<x
#define endl printf("\n")
#define pcase(i) printf("Case %d: ", i)
//Loops
#define loop0(i, n) for(i=0; i<n; i++)
#define loop1(i, n) for(i=1; i<=n; i++)
#define loopab(i, a, b) for(i=a; i<=b; i++)
#define loopr0(i, n) for(i=n-1; i>=0; i--)
#define loopr1(i, n) for(i=n; i>=1; i--)
#define looprab(i, a, b) for(i=b; i>=a; i--)
#define iterate(it, x) for(it=x.begin(); it!=x.end(); it++)
//Fast Input Output
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
//Data Types
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef vector<string> vs;
typedef vector<double> vd;
typedef set<int> si;
typedef set<long long> sll;
typedef set<double> sd;
typedef set<string> ss;
typedef pair<int, int> pii;
typedef map<int, int> mpii;
typedef map<string, int> mpsi;
//Keywords
#define pb push_back
#define ins insert
//Useful Functions
#define sort(x) sort(x.begin(), x.end());
#define sortr(x, a, b) sort(x.begin()+a, x.end()+b+1);
#define sortd(x) sort(x.begin(), x.end(), greater<int>());
#define rev(x) reverse(x.begin(), x.end());
#define revr(x, a, b) reverse(x.begin()+a, x.end()+b+1);
//Constants
const int MOD = 1000000007;
const int MAX = 1000005;
const double PI = acos(-1.0);
//Custom
#define block 0
#define free 1
#define visited 2

//My map to keep trac of block, free, visited and goal cells
int mp[1000][1000];
//Heuristic cost
int heuristic[1000][1000];

//Directional array
int fx[] = {0, 0, -1, 1};
int fy[] = {-1, 1, 0, 0};

//Function to cheack a cell is destination or not
bool isDestination(pii cell, vector<pii>goals){
    int i;
    //Looping through all the goal cells to cheack wheather our cell is one of the goal or not
    loop0(i, goals.size()){
        if(goals[i].first == cell.first && goals[i].second == cell.second){
            return true;
        }
    }
    return false;
}

//Function to print the final path
void printPath(string path){
    for(int i=0; i<path.length(); i++){
        cout<<path[i];
        if(i != (path.length()-1) && path[i] == ')'){
            cout<<" -> ";
        }
    }
}

//A* Algorithm
void astar(int row, int col, pii source, vector<pii>goals){
    //Add source to our path
    string path = "";
    path += '(' + to_string((source.first)+1) + ',' + to_string((source.second)+1) + ')';
    //Add heuristic cost of source
    int cost = heuristic[source.first][source.second];

    //Mark source as visited
    mp[source.first][source.second] = visited;

    //Map is a type of data structure that always sort(minimum first) data
    //according to key value(here cost) whenever we insert new data
    map<int, string>frontier;
    //Insert the cost with path to frontier
    frontier.insert(make_pair(cost, path));

    while(true){
        //Get front element(minimum cost path) from the frontier
        map<int, string>::iterator itr;
        itr = frontier.begin();
        cost = itr->first;
        path = itr->second;
        int index = path.length();

        pii u;
        u.first = ((int)path[index-4]-48)-1;
        u.second = ((int)path[index-2]-48)-1;

        //Remove the front element(minimum cost path) from the frontier
        frontier.erase(itr);

        //Substract previous heuristic value from cost
        cost -= heuristic[u.first][u.second];

        //Cheack if u is one of the destination or not
        if(isDestination(u, goals)){
            printPath(path);
            cout<<" is the best path costing: "<<cost<<"\n";
            break;
        }

        //Exploring adjecent cells of current cell
        int i;
        loop0(i, 4){
            int nx = u.first + fx[i];
            int ny = u.second + fy[i];

            //Cheack if the cell is valid and free
            if(nx >= 0 && nx < row && ny >= 0 && ny < col && mp[nx][ny] == free){
                //Calculate new cost
                int newCost;
                //Move left and right
                if(i == 0 || i == 1){
                    newCost = cost + 1 + heuristic[nx][ny];
                }
                //Move up and down
                else{
                    newCost = cost + 2 + heuristic[nx][ny];
                }

                //Make new path
                string newPath = path + '(' + to_string(nx+1) + ',' + to_string(ny+1) + ')';
                //Insert new path with cost to the frontier
                frontier.insert(make_pair(newCost, newPath));

                //Make this cell as visited cell
                mp[nx][ny] = visited;
            }
        }
    }
}



int main(){
    //fastio;
    //ofstream fout("output.txt");


    //Reading input from "input.txt" file
    fstream fin("input.txt");
    
    //Number of rows and columns of the grid
    int row, col;
    fin>>row>>col;

    //Make all cells free
    int i, j;
    loop0(i, row){
        loop0(j, col){
            mp[i][j] = free;
        }
    }

    //Source cell
    pii source;
    int x, y;
    fin>>x>>y;
    source.first = x-1;
    source.second = y-1;

    //Number of goal cells
    int numGoals;
    fin>>numGoals;

    //Goal cells
    vector<pii>goals;
    pii goalAxis;
    while(numGoals--){
        fin>>x>>y;
        goalAxis.first = x-1;
        goalAxis.second = y-1;

        //Storing goals axises
        goals.pb(goalAxis);
    }

    //Number of blocked cells
    int numBlock;
    fin>>numBlock;

    //Blocked cells
    int blockx, blocky;
    while(numBlock--){
        fin>>blockx>>blocky;

        //Marking blocked cells in my map
        mp[blockx-1][blocky-1] = block;
    }
    
    //Take min Manhattan distance from nearest goal as Heuristic cost
    int k;
    loop0(i, row){
        loop0(j, col){

            int min = 1000000;
            loop0(k, goals.size()){
                int distance = abs(i-goals[k].first) + abs(j-goals[k].second);
                if(distance < min){
                    min = distance;
                }
            }
            heuristic[i][j] = min;
        }
    }

    //Call A* function
    astar(row, col, source, goals);


    return 0;
}