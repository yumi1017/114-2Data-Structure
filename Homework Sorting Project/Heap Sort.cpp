#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
void Adjust(T* a, const int root, const int n)
{// Adjust binary tree with root root to satisfy heap property. The left and right
 // subtrees of root already satisfy the heap property. No node index is > n.
    T e = a[root];

    // find proper place for e
    int j;

    for (j = 2 * root; j <= n; j *= 2) {
        if (j < n && a[j] < a[j + 1]) j++; // j is max child of its parent
        if (e >= a[j]) break;              // e may be inserted as parent of j
        a[j / 2] = a[j];                   // move jth record up the tree
    }

    a[j / 2] = e;
}

template <class T>
void HeapSort(T* a, const int n)
{// Sort a[1:n] into nondecreasing order.

    int i;

    for (i = n / 2; i >= 1; i--) // heapify
        Adjust(a, i, n);

    for (i = n - 1; i >= 1; i--) // sort
    {
        swap(a[1], a[i + 1]);       // swap first and last of current heap
        Adjust(a, 1, i);            // heapify
    }
}

int main()
{
    int n;

    cout << "請輸入資料筆數 n: ";
    cin >> n;

    int* a = new int[n + 1];

    cout << "請輸入 " << n << " 個數字: ";
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }

    HeapSort(a, n);

    cout << "排序後結果: ";
    for (int i = 1; i <= n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;

    delete[] a;

    return 0;
}