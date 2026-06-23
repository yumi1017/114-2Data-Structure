//levelorder.cpp
#include <iostream>
#include <queue>
using namespace std;

template<class T>
class TreeNode {
public:
    T data;
    TreeNode<T>* leftChild;
    TreeNode<T>* rightChild;

    TreeNode(T value) {
        data = value;
        leftChild = nullptr;
        rightChild = nullptr;
    }
};

template<class T>
class Tree {
private:
    TreeNode<T>* root;

public:
    Tree() {
        root = nullptr;
    }

    void SetRoot(TreeNode<T>* node) {
        root = node;
    }

    void Visit(TreeNode<T>* node) {
        cout << node->data << " ";
    }

    void Levelorder();
};

template<class T>
void Tree<T>::Levelorder()
{
    if (!root) return;

    queue<TreeNode<T>*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode<T>* currentNode = q.front();
        q.pop();

        Visit(currentNode);

        if (currentNode->leftChild)
            q.push(currentNode->leftChild);

        if (currentNode->rightChild)
            q.push(currentNode->rightChild);
    }
}

int main()
{
    Tree<int> tree;

    TreeNode<int>* A = new TreeNode<int>(1);
    TreeNode<int>* B = new TreeNode<int>(2);
    TreeNode<int>* C = new TreeNode<int>(3);
    TreeNode<int>* D = new TreeNode<int>(4);
    TreeNode<int>* E = new TreeNode<int>(5);

    A->leftChild = B;
    A->rightChild = C;
    B->leftChild = D;
    B->rightChild = E;

    tree.SetRoot(A);

    cout << "Levelorder traversal: ";
    tree.Levelorder();

    return 0;
}