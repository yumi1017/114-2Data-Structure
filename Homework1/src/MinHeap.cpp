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