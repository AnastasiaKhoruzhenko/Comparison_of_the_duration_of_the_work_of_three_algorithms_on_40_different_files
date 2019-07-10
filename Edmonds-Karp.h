#include <iostream>
#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

class EdmondsKarpClass{
public:

//возвращает true, если есть путь из переданного истока в переданный сток
bool BFS(vector<vector<int>> &rGraph, int N, int s, int t, int *parent)
{
    //для пометки посещенных вершин
    bool visited[N];
    memset(visited, 0, sizeof(visited));

    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v=0; v<N; v++)
        {
            if (!visited[v] && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return (visited[t]);
}

int EdmondsKarp(vector<vector<int>> graph, int N, int s, int t)
{
    int u, v;

    vector<vector<int>> rGraph(N, vector <int> (N) );

    for (u = 0; u < N; u++)
        for (v = 0; v < N; v++)
            rGraph[u][v] = graph[u][v];

    int parent[N];
    int max_flow = 0;

    while (BFS(rGraph, N, s, t, parent))
    {
        int path_flow = INT32_MAX;
        //пока не достигну истока, возвращаюсь по родителям
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}
};
