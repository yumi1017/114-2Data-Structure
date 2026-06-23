#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graph
{
private:
    int n;
    vector<vector<int>> adj;

    int num;
    int* dfn;
    int* low;

public:
    Graph(int vertices)
    {
        n = vertices;
        adj.resize(n);
        dfn = nullptr;
        low = nullptr;
        num = 1;
    }

    void InsertEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    virtual void DfnLow(const int x) // begin DFS at vertex x
    {
        num = 1;              // num is an int data member of Graph
        dfn = new int[n];     // dfn is declared as int* in Graph
        low = new int[n];     // low is declared as int* in Graph

        fill(dfn, dfn + n, 0);
        fill(low, low + n, 0);

        DfnLow(x, -1); // start at vertex x

        cout << "vertex\t";
        for (int i = 0; i < n; i++)
            cout << i << "\t";
        cout << endl;

        cout << "dfn\t";
        for (int i = 0; i < n; i++)
            cout << dfn[i] << "\t";
        cout << endl;

        cout << "low\t";
        for (int i = 0; i < n; i++)
            cout << low[i] << "\t";
        cout << endl;

        delete[] dfn;
        delete[] low;
    }

    void DfnLow(const int u, const int v)
    {
        // Compute dfn and low while performing a depth first search beginning at vertex u.
        // v is the parent (if any) of u in the resulting spanning tree.
        dfn[u] = low[u] = num++;

        for (int w : adj[u]) // actual code uses an iterator
        {
            if (dfn[w] == 0)
            {
                // w is an unvisited vertex
                DfnLow(w, u);
                low[u] = min(low[u], low[w]);
            }
            else if (w != v)
            {
                low[u] = min(low[u], dfn[w]); // back edge
            }
        }
    }
};

int main()
{
    Graph g(6);

    g.InsertEdge(0, 1);
    g.InsertEdge(1, 2);
    g.InsertEdge(2, 0);
    g.InsertEdge(1, 3);
    g.InsertEdge(3, 4);
    g.InsertEdge(4, 5);
    g.InsertEdge(5, 3);

    g.DfnLow(0);

    return 0;
}