#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

struct Edge {
    int u, v;
};

class Graph {
private:
    int n;
    int num;
    vector<int>* adj;

public:
    Graph(int nodes) : n(nodes) {
        adj = new vector<int>[n];
    }

    ~Graph() {
        delete[] adj;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void showMatrix() {
        for (int k = 0; k < n; k++) {
            cout << k << " ";
        }
        cout << endl;

        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n; j++) {
                if (find(adj[i].begin(), adj[i].end(), j) != adj[i].end()) {
                    cout << "1 ";
                }
                else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }

    void showArraylist() {
        vector<int>::iterator it;

        for (int i = 0; i < n; ++i) {
            cout << i << " : ";

            for (it = adj[i].begin(); it < adj[i].end(); ++it) {
                cout << *it << " ";
            }

            cout << endl;
        }
    }
};

int main() {
    Graph g(10);

    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(4, 3);
    g.addEdge(3, 5);
    g.addEdge(5, 6);
    g.addEdge(5, 7);
    g.addEdge(6, 7);
    g.addEdge(7, 8);
    g.addEdge(7, 9);

    cout << "Adjacency List:" << endl;
    g.showArraylist();

    cout << endl;

    cout << "Adjacency Matrix:" << endl;
    g.showMatrix();

    return 0;
}