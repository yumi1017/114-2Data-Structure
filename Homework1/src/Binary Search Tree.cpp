//MinHeap.cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <iomanip>
using namespace std;

// 節點
struct TreeNode {
    int key;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int k) : key(k), left(nullptr), right(nullptr) {}
};

class BST {
private:
    TreeNode* root;

    // 插入
    TreeNode* Insert(TreeNode* node, int key) {
        if (node == nullptr)
            return new TreeNode(key);

        if (key < node->key)
            node->left = Insert(node->left, key);
        else if (key > node->key)
            node->right = Insert(node->right, key);

        return node;
    }

    // 計算高度
    int Height(TreeNode* node) const {
        if (node == nullptr)
            return 0;
        return 1 + max(Height(node->left), Height(node->right));
    }

public:
    BST() : root(nullptr) {}

    void Insert(int key) {
        root = Insert(root, key);
    }

    int Height() const {
        return Height(root);
    }
};

int main() {
    vector<int> testN = { 100, 500, 1000, 2000, 5000, 10000 };

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 10000000);

    cout << fixed << setprecision(4);
    cout << "n\tHeight\tlog2(n)\t比例" << endl;

    for (int n : testN) {
        BST tree;
        set<int> used; // 避免重複

        // 插入 n 個隨機數
        while ((int)used.size() < n) {
            int x = dist(gen);
            if (used.insert(x).second)
                tree.Insert(x);
        }

        int h = tree.Height();
        double logValue = log2((double)n);
        double ratio = h / logValue;

        cout << n << "\t" << h << "\t" << logValue << "\t" << ratio << endl;
    }

    return 0;
}