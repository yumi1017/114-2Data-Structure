#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

class Graph
{
private:
    int n;
    vector<vector<int>> adj;

    int num;
    int* dfn;
    int* low;

    stack<pair<int, int>> s;

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

    virtual void Biconnected()
    {
        num = 1;              // num is an int data member of Graph
        dfn = new int[n];     // dfn is declared as int* in Graph
        low = new int[n];     // low is declared as int* in Graph

        fill(dfn, dfn + n, 0);
        fill(low, low + n, 0);

        Biconnected(0, -1); // start at vertex 0

        delete[] dfn;
        delete[] low;
    }

    virtual void Biconnected(const int u, const int v)
    {
        // Compute dfn and low, and output the edges of G by their biconnected
        // components. v is the parent (if any) of u in the resulting spanning tree.
        // s is an initially empty stack declared as a data member of Graph.
        dfn[u] = low[u] = num++;

        for (int w : adj[u]) // actual code uses an iterator
        {
            if ((u != v) && (dfn[w] < dfn[u]))
            {
                s.push({ u, w });
            }

            if (dfn[w] == 0)
            {
                // w is an unvisited vertex
                Biconnected(w, u);
                low[u] = min(low[u], low[w]);

                if (low[w] >= dfn[u])
                {
                    cout << "New Biconnected Component: " << endl;

                    pair<int, int> edge;

                    do
                    {
                        // delete an edge from the stack s;
                        edge = s.top();
                        s.pop();

                        // let this edge be (x, y);
                        int x = edge.first;
                        int y = edge.second;

                        cout << x << ", " << y << endl;

                    } while (!(edge.first == u && edge.second == w));
                }
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
    Graph g(7);

    g.InsertEdge(0, 1);
    g.InsertEdge(1, 2);
    g.InsertEdge(2, 0);

    g.InsertEdge(1, 3);

    g.InsertEdge(3, 4);
    g.InsertEdge(4, 5);
    g.InsertEdge(5, 3);

    g.InsertEdge(5, 6);

    g.Biconnected();

    return 0;
}