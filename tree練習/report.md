# 41141205

## inorder
左子樹 → 根節點 → 右子樹
```cpp
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
```

### input
<img width="113" height="133" alt="image" src="https://github.com/user-attachments/assets/e354a688-6877-4128-85fd-c874005b84ef" />

### output
```text
Inorder traversal: 4 2 5 1 3 
```

## preorder
根節點 → 左子樹 → 右子樹
```cpp
//preorder.cpp
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

    void Preorder();
    void Preorder(TreeNode<T>* currentNode);
};

template<class T>
void Tree<T>::Preorder()
{
    Preorder(root);
}

template<class T>
void Tree<T>::Preorder(TreeNode<T>* currentNode)
{
    if (currentNode) {
        Visit(currentNode);
        Preorder(currentNode->leftChild);
        Preorder(currentNode->rightChild);
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

    cout << "Preorder traversal: ";
    tree.Preorder();

    return 0;
}
```

### input
<img width="113" height="133" alt="image" src="https://github.com/user-attachments/assets/e354a688-6877-4128-85fd-c874005b84ef" />

### output
```text
Preorder traversal: 1 2 4 5 3 
```

## postorder
左子樹 → 右子樹 → 根節點
```cpp
//postorder.cpp
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

    void Postorder();
    void Postorder(TreeNode<T>* currentNode);
};

template<class T>
void Tree<T>::Postorder()
{
    Postorder(root);
}

template<class T>
void Tree<T>::Postorder(TreeNode<T>* currentNode)
{
    if (currentNode) {
        Postorder(currentNode->leftChild);
        Postorder(currentNode->rightChild);
        Visit(currentNode);
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

    cout << "Postorder traversal: ";
    tree.Postorder();

    return 0;
}
```

### input
<img width="113" height="133" alt="image" src="https://github.com/user-attachments/assets/e354a688-6877-4128-85fd-c874005b84ef" />

### output
```text
Postorder traversal: 4 5 2 3 1 
```

## levelorder
從上到下、從左到右
```cpp
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
```

### input
<img width="113" height="133" alt="image" src="https://github.com/user-attachments/assets/e354a688-6877-4128-85fd-c874005b84ef" />

### output
```text
Levelorder traversal: 1 2 3 4 5 
```
