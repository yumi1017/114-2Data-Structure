# Homework1

## MinHeap 最小堆積
```cpp
//MinHeap.cpp
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

// MinPQ 抽象類別（最小優先佇列）
template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}                  // 解構子
    virtual bool IsEmpty() const = 0;    // 判斷是否為空
    virtual const T& Top() const = 0;    // 取得最小值（root）
    virtual void Push(const T&) = 0;     // 插入元素
    virtual void Pop() = 0;              // 刪除最小值
};

// MinHeap 實作（使用 Binary Heap）
template <class T>
class MinHeap : public MinPQ<T> {
private:
    vector<T> heap; // 使用陣列（vector）儲存 heap

    // 向上調整（維持 MinHeap 性質）
    void HeapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2; // 找父節點

            // 若子節點比父節點小 → 交換
            if (heap[index] < heap[parent]) {
                swap(heap[index], heap[parent]);
                index = parent; // 繼續往上檢查
            }
            else {
                break;
            }
        }
    }

    // 向下調整（維持 MinHeap 性質）
    void HeapifyDown(int index) {
        int n = heap.size();

        while (true) {
            int left = 2 * index + 1;   // 左子節點
            int right = 2 * index + 2;  // 右子節點
            int smallest = index;

            // 找最小的節點
            if (left < n && heap[left] < heap[smallest])
                smallest = left;

            if (right < n && heap[right] < heap[smallest])
                smallest = right;

            // 如果最小的不是自己 → 交換
            if (smallest != index) {
                swap(heap[index], heap[smallest]);
                index = smallest;
            }
            else {
                break;
            }
        }
    }

public:
    // 判斷是否為空
    bool IsEmpty() const override {
        return heap.empty();
    }

    // 取得最小值（root）
    const T& Top() const override {
        if (IsEmpty())
            throw runtime_error("Heap 是空的！");
        return heap[0];
    }

    // 插入元素
    void Push(const T& x) override {
        heap.push_back(x);                // 放到最後
        HeapifyUp(heap.size() - 1);       // 向上調整
    }

    // 刪除最小值
    void Pop() override {
        if (IsEmpty())
            throw runtime_error("Heap 是空的！");

        heap[0] = heap.back();  // 最後一個補到 root
        heap.pop_back();        // 刪掉最後一個

        if (!heap.empty())
            HeapifyDown(0);     // 向下調整
    }

    // 顯示 heap
    void PrintHeap() const {
        for (const auto& x : heap)
            cout << x << " ";
        cout << endl;
    }
};

// 測試
int main() {
    MinHeap<int> h;

    h.Push(40);
    h.Push(10);
    h.Push(30);
    h.Push(5);
    h.Push(20);

    cout << "Heap內容：";
    h.PrintHeap();

    cout << "最小值 = " << h.Top() << endl;

    h.Pop();

    cout << "刪除後最小值 = " << h.Top() << endl;

    return 0;
}
```

### output:
```text
Heap內容：5 10 30 40 20 
最小值 = 5
刪除後最小值 = 10
```

### 時間複雜度
```text
IsEmpty()-> 判斷是否為空 -> O(1)
Top() -> 取得最小值 -> O(1)
Push() -> 插入元素 -> O(log n)
Pop() -> 刪除最小值 -> O(log n)
PrintHeap() -> 印出所有元素 -> O(n)

整體時間複雜度 -> O(log n)
```

### 空間複雜度
```text
vector<T> heap -> 儲存 heap 中的 n 個元素 -> O(n)
HeapifyUp() -> 使用迴圈向上調整，沒有額外陣列 -> O(1)
HeapifyDown() -> 使用迴圈向下調整，沒有額外陣列 -> O(1)
IsEmpty() -> 只判斷 heap 是否為空 -> O(1)
Top() -> 只回傳 heap[0] -> O(1)
Push() -> 新增一個元素到 vector -> O(1) 額外空間
Pop() -> 刪除 root 並重新調整 -> O(1) 額外空間
PrintHeap() -> 只逐一輸出元素，沒有額外儲存 -> O(1) 額外空間

整體空間複雜度 -> O(n)
```

## Binary Search Tree Deletion

```cpp
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
```
### input:
```text
50, 30, 70, 20, 40
```
形成的 BST:
<img width="110" height="137" alt="image" src="https://github.com/user-attachments/assets/e0503940-b5e4-4dfb-9bf1-b89a5bbc0e7f" />

### output:
```text
原BST：20 30 40 50 70 
刪除30後：20 40 50 70 
```

### 時間複雜度
```text
Insert() -> 平均 O(log n)，最壞 O(n)
Delete() -> 平均 O(log n)，最壞 O(n)
Print() -> O(n)

整體主要操作時間複雜度 -> 平均 O(log n)，最壞 O(n)
```

### 空間複雜度
```text
BST 儲存 n 個節點 -> O(n)
遞迴呼叫堆疊 -> 平均 O(log n)，最壞 O(n)

整體空間複雜度 -> O(n)
```

## Binary Search Tree
儲存隨機產生的不重複整數，並計算不同 n 值下 BST 的高度

```cpp
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
```

### output:
這段程式碼因為使用 **隨機數插入 BST**，所以每次執行的 Height 和 比例 可能都會不一樣。
```text
n       Height  log2(n)  比例
100     13      6.6439   1.9567
500     20      8.9658   2.2307
1000    22      9.9658   2.2076
2000    26      10.9658  2.3708
5000    28      12.2877  2.2787
10000   33      13.2877  2.4835
```

### 時間複雜度
```text
IsEmpty() -> 判斷是否為空 -> O(1)
Top() -> 取得最小值 -> O(1)
Push() -> 插入元素 -> O(log n)
Pop() -> 刪除最小值 -> O(log n)
PrintHeap() -> 印出所有元素 -> O(n)

整體時間複雜度 -> O(log n)
```

### 空間複雜度
```text
vector<T> heap -> 儲存 heap 中的 n 個元素 -> O(n)
HeapifyUp() -> 使用迴圈向上調整，沒有額外陣列 -> O(1)
HeapifyDown() -> 使用迴圈向下調整，沒有額外陣列 -> O(1)
IsEmpty() -> 只判斷 heap 是否為空 -> O(1)
Top() -> 只回傳 heap[0] -> O(1)
Push() -> 新增一個元素到 vector -> O(1) 額外空間
Pop() -> 刪除 root 並重新調整 -> O(1) 額外空間
PrintHeap() -> 只逐一輸出元素，沒有額外儲存 -> O(1) 額外空間

整體空間複雜度 -> O(n)
```
