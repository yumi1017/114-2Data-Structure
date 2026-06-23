//inorder.cpp
#include <iostream>
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

    void Inorder();
    void Inorder(TreeNode<T>* currentNode);
};

template<class T>
void Tree<T>::Inorder()
{
    Inorder(root);
}

template<class T>
void Tree<T>::Inorder(TreeNode<T>* currentNode)
{
    if (currentNode) {
        Inorder(currentNode->leftChild);
        Visit(currentNode);
        Inorder(currentNode->rightChild);
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

    cout << "Inorder traversal: ";
    tree.Inorder();

    return 0;
}