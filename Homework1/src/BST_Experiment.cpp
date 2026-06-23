//BST_Experiment.cpp
#include <iostream>
using namespace std;

// 節點結構
struct TreeNode {
    int key;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int k) : key(k), left(nullptr), right(nullptr) {}
};

class BST {
private:
    TreeNode* root;

    // 插入節點
    TreeNode* Insert(TreeNode* node, int key) {
        if (node == nullptr)
            return new TreeNode(key);

        if (key < node->key)
            node->left = Insert(node->left, key);
        else if (key > node->key)
            node->right = Insert(node->right, key);

        return node;
    }

    // 找最小值（右子樹用）
    TreeNode* FindMin(TreeNode* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    // 刪除節點
    TreeNode* DeleteNode(TreeNode* node, int key) {
        if (node == nullptr)
            return nullptr;

        // 往左找
        if (key < node->key) {
            node->left = DeleteNode(node->left, key);
        }
        // 往右找
        else if (key > node->key) {
            node->right = DeleteNode(node->right, key);
        }
        // 找到要刪的節點
        else {
            // Case 1：葉節點
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            // Case 2：只有右子樹
            else if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            // Case 2：只有左子樹
            else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            // Case 3：有兩個子節點
            else {
                TreeNode* successor = FindMin(node->right); // 找右子樹最小
                node->key = successor->key; // 取代
                node->right = DeleteNode(node->right, successor->key);
            }
        }

        return node;
    }

    // 中序走訪（排序輸出）
    void Inorder(TreeNode* node) {
        if (node == nullptr) return;
        Inorder(node->left);
        cout << node->key << " ";
        Inorder(node->right);
    }

public:
    BST() : root(nullptr) {}

    void Insert(int key) {
        root = Insert(root, key);
    }

    void Delete(int key) {
        root = DeleteNode(root, key);
    }

    void Print() {
        Inorder(root);
        cout << endl;
    }
};

// 測試
int main() {
    BST tree;

    tree.Insert(50);
    tree.Insert(30);
    tree.Insert(70);
    tree.Insert(20);
    tree.Insert(40);

    cout << "原BST：";
    tree.Print();

    tree.Delete(30);

    cout << "刪除30後：";
    tree.Print();

    return 0;
}