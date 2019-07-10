#include <cstring>
#include <limits.h>

using namespace std;

class DinicsClass{

public:
    int s, t;
    vector<vector<int>> graph;
    vector<vector<int>> rGraph;

    //метод заполнения graph значениями из матрицы и rGraph нулями
    void fill(int N, vector<vector<int>> g)
    {
        graph.resize(N);
        rGraph.resize(N);
        for (int i = 0; i < N; ++i) {
            graph[i].resize(N);
            rGraph[i].resize(N);
            for (int j = 0; j < N; ++j)
            {
                graph[i][j]=g[i][j];
                rGraph[i][j]=0;
            }
        }
    }

    bool BFS(int N, int *q, int *d) {
        int qh=0, qt=0;
        q[qt++] = s;
        memset (d, -1, N * sizeof d[0]);
        d[s] = 0;
        while (qh < qt) {
            int v = q[qh++];
            for (int to=0; to<N; ++to)
                if (d[to] == -1 && rGraph[v][to] < graph[v][to]) {
                    q[qt++] = to;
                    d[to] = d[v] + 1;
                }
        }
        return d[t] != -1;
    }

    int DFS(int N, int v, int flow, int *d, int *ptr) {
        if (!flow)  return 0;
        if (v == t)  return flow;
        for (int & to=ptr[v]; to<N; ++to) {
            if (d[to] != d[v] + 1)  continue;
            int pushed = DFS(N, to, min(flow, graph[v][to] - rGraph[v][to]), d, ptr);
            if (pushed) {
                rGraph[v][to] += pushed;
                rGraph[to][v] -= pushed;
                return pushed;
            }
        }
        return 0;
    }

    int Dinic(vector<vector<int>> g,int N, int ss, int tt)
    {
        //d - слои вершины
        //ptr - точка остановки для вершины v

        int d[N], ptr[N], q[N];
        s=ss;
        t=tt;
        fill(N, g);
        int flow = 0;
        while (BFS(N, q, d))
        {
            memset (ptr, 0, N * sizeof ptr[0]);
            while (int pushed = DFS(N, s, INT_MAX, d, ptr))
                flow += pushed;
        }
        return flow;
    }
};