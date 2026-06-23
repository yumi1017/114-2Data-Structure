#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graph
{
private:
    int n;
    vector<vector<int>> adj;
    bool* visited;

public:
    Graph(int vertices)
    {
        n = vertices;
        adj.resize(n);
        visited = nullptr;
    }

    void InsertEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void DFS(const int v)
    {
        visited[v] = true;
        cout << v << " ";

        for (int w : adj[v])
        {
            if (!visited[w])
                DFS(w);
        }
    }

    void OutputNewComponent()
    {
        cout << endl;
    }

    virtual void Components()
    {
        // Determine the connected components of the graph.
        // visited is assumed to be declared as a bool* data member of Graph
        visited = new bool[n];
        fill(visited, visited + n, false);

        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                cout << "Component: ";
                DFS(i); // find a component
                OutputNewComponent();
            }
        }

        delete[] visited;
    }
};

int main()
{
    Graph g(7);

    g.InsertEdge(0, 1);
    g.InsertEdge(0, 2);
    g.InsertEdge(3, 4);
    g.InsertEdge(5, 6);

    g.Components();

    return 0;
}