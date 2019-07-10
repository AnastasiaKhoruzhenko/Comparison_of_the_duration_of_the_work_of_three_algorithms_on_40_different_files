#include <iostream>
#include <iostream>
#include <cstring>
#include <queue>
#include <limits.h>
#include <stack>

using namespace std;

class FordFulkersonClass{
public:
    bool DFS(vector<vector<int>> &rGraph, int N, int * parent, int x, int t)
    {
        vector<bool> visited(N, false);
        stack<int> myStack;

        parent[x] = -1;
        myStack.push(x);

        while (!myStack.empty())
        {
            int u = myStack.top();
            myStack.pop();

            for (int i = N-1; i >= 0 ; i--) {
                if (!visited[i] && rGraph[u][i] > 0)
                {
                    myStack.push(i);
                    parent[i] = u;
                    visited[i] = true;
                }
            }
        }

        return visited[t];

    }

    int FordFulkerson(vector<vector<int>> graph, int N, int s, int t){

        vector <vector<int>> rGraph(N, vector <int> (N) );
        int parent[N];

        for(int i = 0; i < N; ++i)
            for(int j = 0; j < N; ++j)
                rGraph[i][j]=graph[i][j];

        int max_flow = 0;

        while(DFS(rGraph, N, parent, s, t)){
            int path_flow = INT_MAX;

            for(int v = t; v != s; v = parent[v]){
                int u = parent[v];
                path_flow = min(path_flow, rGraph[u][v]);
            }

            for(int v = t; v != s; v = parent[v]){
                int u = parent[v];
                rGraph[u][v] -= path_flow;
                rGraph[v][u] += path_flow;
            }

            max_flow += path_flow;
        }

        return max_flow;
    }

};