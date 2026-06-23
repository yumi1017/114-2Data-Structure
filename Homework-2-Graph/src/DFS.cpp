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

    virtual void DFS() // Driver負責建立 visited 陣列，並從 vertex 0 開始搜尋
    {
        visited = new bool[n];
        // visited is declared as a bool* data member of Graph
        fill(visited, visited + n, false);
        DFS(0); // start search at vertex 0
        delete[] visited;
    }

    virtual void DFS(const int v) // Workhorse真正負責遞迴拜訪節點
    {
        // Visit all previously unvisited vertices that are reachable from vertex v.
        visited[v] = true;
        cout << v << " ";

        for (int w : adj[v]) // actual code uses an iterator
        {
            if (!visited[w])
                DFS(w);
        }
    }
};

int main()
{
    Graph g(6);

    g.InsertEdge(0, 1);
    g.InsertEdge(0, 2);
    g.InsertEdge(1, 3);
    g.InsertEdge(2, 4);
    g.InsertEdge(4, 5);

    cout << "DFS result: ";
    g.DFS();

    return 0;
}