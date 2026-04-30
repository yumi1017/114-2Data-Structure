# Homework 2 Graph

## The Graph Abstract Data Type
- Basic Graph Class Structure
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;
struct Edge{
int u,v;
};

class Graph{
private:
    int n;
    int num;
    vector<int>*adj;
public:
    Graph(int nodes):n(nodes){
        adj=new vector<int>[n];
    }

    ~Graph(){
        delete[] adj;
    }

    void addEdge(int u,int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
```

- showMatrix()
```cpp
    void showMatrix(){
        vector<int>::iterator it;
        for(int k=0;k<n;k++){
            cout<<k<<" ";
        }
        cout<<endl;
        for(int i=0;i<n;++i){
            it=adj[i].begin();
            for(int j=0;j<n;j++){
                if(*it==){
                    cout<<"1 ";
                    ++it;
                }
                else{
                    cout<<"0 ";
                }
            }
            cout<<endl;
        }
    }
```

- showArraylist()
```cpp
    void showArraylist(){
        vector<int>::iterator it;
        for(int i=0;i<n;++i){
            cout<<i<<" : ";
            for(it=adj[i].begin();it<adj[i].end();++it)
            cout<<*it<<" ";
            cout<<endl;
        }
    }
};
```

- main()
```cpp
int main(){
        Graph g(10);

        g.addEdge(0,1);
        g.addEdge(1,2);
        g.addEdge(1,3);
        g.addEdge(2,4);
        g.addEdge(4,3);
        g.addEdge(3,5);
        g.addEdge(5,6);
        g.addEdge(5,7);
        g.addEdge(6,7);
        g.addEdge(7,8);
        g.addEdge(7,9);

        g.showArraylist();
        g.showMatrix();

        return 0;
    }
```

> output
```text
0 : 1
1 : 0 2 3
2 : 1 4
3 : 1 4 5
4 : 2 3
5 : 3 6 7
6 : 5 7
7 : 5 6 8 9
8 : 7
9 : 7
0 1 2 3 4 5 6 7 8 9
0 1 0 0 0 0 0 0 0 0
1 0 1 1 0 0 0 0 0 0
0 1 0 0 1 0 0 0 0 0
0 1 0 0 1 1 0 0 0 0
0 0 1 1 0 0 0 0 0 0
0 0 0 1 0 0 1 1 0 0
0 0 0 0 0 1 0 1 0 0
0 0 0 0 0 1 1 0 1 1
0 0 0 0 0 0 0 1 0 0
```

## ADT 6.1: Abstract data type Graph
```cpp
class Graph
{// objects: A nonempty set of vertices and a set of undirected edges,
 // where each edge is a pair of vertices.
public:
    virtual ~Graph() {}
        // virtual destructor

    bool IsEmpty() const {return n == 0;};
        // return true iff graph has no vertices

    int NumberOfVertices() const {return n;};
        // return number of vertices in the graph

    int NumberOfEdges() const {return e;};
        // return number of edges in the graph

    virtual int Degree(int u) const = 0;
        // return number of edges incident to vertex u

    virtual bool ExistsEdge(int u, int v) const = 0;
        // return true iff graph has the edge (u, v)

    virtual void InsertVertex(int v) = 0;
        // insert vertex v into graph; v has no incident edges

    virtual void InsertEdge(int u, int v) = 0;
        // insert edge (u, v) into graph

    virtual void DeleteVertex(int v) = 0;
        // delete v and all edges incident to it

    virtual void DeleteEdge(int u, int v) = 0;
        // delete edge (u, v) from the graph

private:
    int n;
        // number of vertices

    int e;
        // number of edges
};
```

## Depth-first search (DFS)
- DFS:Depth-first search，深度優先搜尋
-- 從起點開始，先往一條路一直走下去，走到不能走時，再回頭找其他還沒拜訪過的點。
```cpp
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
```
```text
DFS result: 0 1 3 2 4 5
```

### 空間複雜度
adjacency list -> O(V + E)
visited 陣列 -> O(V)
DFS 遞迴堆疊 -> 最差 O(V)

### 時間複雜度
-> O(V + E)

## Breadth-first search (BFS)
- BFS:Breadth-first search，廣度優先搜尋
-- 從起點開始，先拜訪距離最近的節點，再一層一層往外拜訪。
```cpp
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
```
```text
BFS result: 0 1 2 3 4 5 =thread-exited,id="4",group-id="i1"
```

### 空間複雜度
adjacency list -> O(V + E)
visited 陣列 -> O(V)
queue -> 最差 O(V)

### 時間複雜度
-> O(V + E)

## Program 6.3：Determining connected components
- Connected Components:連通分量
-- 在一個無向圖中，彼此可以互相到達的一群 vertex，就形成一個 connected component。
```cpp
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
```
```text
Component: 0 1 2
Component: 3 4
Component: 5 6
```

### 空間複雜度
adjacency list -> O(V + E)
visited 陣列 -> O(V)
DFS 遞迴堆疊 -> 最差 O(V)

### 時間複雜度
-> O(V + E)

## Program 6.4：Computing dfn and low
- 用 DFS 來計算兩個重要陣列
```cpp
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
```
```text
vertex	0	1	2	3	4	5
 dfn	1	2	3	4	5	6
 low	1	1	1	4	4	4
```

### 空間複雜度
adjacency list -> O(V + E)
dfn 陣列 -> O(V)
low 陣列 -> O(V)
DFS 遞迴堆疊 -> 最差 O(V)

### 時間複雜度
-> O(V + E)

## Program 6.5：Outputting biconnected components when n > 1
- 用來輸出 Biconnected Components，雙連通分量
```cpp
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
                s.push({u, w});
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
```
```text
New Biconnected Component:
6, 5
5, 6
New Biconnected Component:
5, 3
5, 4
4, 5
4, 3
3, 4
New Biconnected Component:
3, 1
1, 3
New Biconnected Component:
2, 0
2, 1
1, 2
1, 0
0, 1
```

### 空間複雜度
adjacency list -> O(V + E)
dfn 陣列 -> O(V)
low 陣列 -> O(V)
stack 儲存邊 -> 最差 O(E)
DFS 遞迴堆疊 -> 最差 O(V)

### 時間複雜度
-> O(V + E)
