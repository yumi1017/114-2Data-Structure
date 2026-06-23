#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
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

    virtual void BFS(int v)
    {
        // A breadth first search of the graph is carried out beginning at vertex v.
        // visited[i] is set to true when v is visited. The function uses a queue.
        visited = new bool[n];
        fill(visited, visited + n, false);
        visited[v] = true;

        queue<int> q;
        q.push(v);

        while (!q.empty())
        {
            v = q.front();
            q.pop();

            cout << v << " ";

            for (int w : adj[v]) // actual code uses an iterator
            {
                if (!visited[w])
                {
                    q.push(w);
                    visited[w] = true;
                }
            }
        } // end of while loop

        delete[] visited;
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

    cout << "BFS result: ";
    g.BFS(0);

    return 0;
}