# Homework Sorting Project

## Insertion Sort
```cpp
#include <iostream>
using namespace std;

template <class T>
void Insert(const T& e, T* a, int i)
{// Insert e into the ordered sequence a[1:i] such that the
 // resulting sequence a[1:i+1] is also ordered.
 // The array a must have space allocated for at least i + 2 elements.
    a[0] = e;
    while (e < a[i])
    {
        a[i + 1] = a[i];
        i--;
    }
    a[i + 1] = e;
}

template <class T>
void InsertionSort(T* a, int n)
{
    for (int i = 1; i < n; i++)
    {
        T e = a[i + 1];
        Insert(e, a, i);
    }
}

int main()
{
    int n;

    cout << "請輸入資料筆數: ";
    cin >> n;

    int* a = new int[n + 1];

    cout << "請輸入 " << n << " 個數字: ";
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }

    InsertionSort(a, n);

    cout << "排序後結果: ";
    for (int i = 1; i <= n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;

    delete[] a;

    return 0;
}
```

### input
```text
請輸入資料筆數: 5
請輸入 5 個數字: 5 2 4 1 3
```

### output
```text
排序後結果: 1 2 3 4 5
```

### 時間複雜度
> Best Case
```text
O(n)
```
> Average Case
```text
O(n²)
```
> Worst Case
```text
O(n²)
```

## Quick Sort
```text
median-of-three
從 a[left], a[mid], a[right] 三個值裡面選中間大小的值當 pivot。
```

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
void MedianOfThree(T *a, const int left, const int right)
{
    int mid = (left + right) / 2;

    if (a[mid] < a[left])
        swap(a[mid], a[left]);

    if (a[right] < a[left])
        swap(a[right], a[left]);

    if (a[right] < a[mid])
        swap(a[right], a[mid]);

    // 將 median 放到 right - 1 的位置，作為 pivot
    swap(a[mid], a[right - 1]);
}

template <class T>
void QuickSort(T *a, const int left, const int right)
{// Sort a[left:right] into nondecreasing order.
 // Use median-of-three method to choose pivot.

    if (left + 1 >= right)
    {
        if (a[right] < a[left])
            swap(a[left], a[right]);
        return;
    }

    MedianOfThree(a, left, right);

    T pivot = a[right - 1];

    int i = left;
    int j = right - 1;

    while (true)
    {
        while (a[++i] < pivot);
        while (a[--j] > pivot);

        if (i < j)
            swap(a[i], a[j]);
        else
            break;
    }

    // 將 pivot 放回正確位置
    swap(a[i], a[right - 1]);

    QuickSort(a, left, i - 1);
    QuickSort(a, i + 1, right);
}

int main()
{
    int n;

    cout << "請輸入資料筆數: ";
    cin >> n;

    int *a = new int[n + 1];

    cout << "請輸入 " << n << " 個數字: ";
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }

    QuickSort(a, 1, n);

    cout << "排序後結果: ";
    for (int i = 1; i <= n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;

    delete[] a;

    return 0;
}
```

### input
```text
請輸入資料筆數: 10
請輸入 10 個數字: 4 2 3 5 1 6 10 11 9 7
```
### output
```text
排序後結果: 1 2 3 4 5 6 7 9 10 11
```

### 時間複雜度
> Best Case
```text
O(n log n)
```
> Average Case
```text
O(n log n)
```
> Worst Case
```text
O(n²)
```

## Iterative Merge Sort
```text
Program 7.7：Merge()
負責合併兩段已排序好的資料
+
Program 7.8：MergePass()
負責一整輪合併，每次合併長度為 s 的子串列
+
Program 7.9：MergeSort()
真正的 Iterative Merge Sort 主排序函式
```

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
void Merge(T* initList, T* mergedList, const int l, const int m, const int n)
{// initList[l:m] and initList[m + 1:n] are sorted lists. They are merged to obtain
 // the sorted list mergedList[l:n].

    int i1 = l;
    int iResult = l;
    int i2 = m + 1;

    for (; // i1, i2, and iResult are list positions
        i1 <= m && i2 <= n; // neither input list is exhausted
        iResult++)
        if (initList[i1] <= initList[i2])
        {
            mergedList[iResult] = initList[i1];
            i1++;
        }
        else
        {
            mergedList[iResult] = initList[i2];
            i2++;
        }

    // copy remaining records, if any, of first list
    copy(initList + i1, initList + m + 1, mergedList + iResult);

    // copy remaining records, if any, of second list
    copy(initList + i2, initList + n + 1, mergedList + iResult);
}

template <class T>
void MergePass(T* initList, T* resultList, const int n, const int s)
{// Adjacent pairs of sublists of size s are merged from
 // initList to resultList. n is the number of records in initList.

    int i;

    for (i = 1; // i is first position in first of the sublists being merged
        i <= n - 2 * s + 1; // enough elements for two sublists of length s?
        i += 2 * s)
        Merge(initList, resultList, i, i + s - 1, i + 2 * s - 1);

    // merge remaining list of size < 2 * s
    if ((i + s - 1) < n)
        Merge(initList, resultList, i, i + s - 1, n);
    else
        copy(initList + i, initList + n + 1, resultList + i);
}

template <class T>
void MergeSort(T* a, const int n)
{// Sort a[1:n] into nondecreasing order.
    T* tempList = new T[n + 1];

    // l is the length of the sublist currently being merged
    for (int l = 1; l < n; l *= 2)
    {
        MergePass(a, tempList, n, l);
        l *= 2;
        MergePass(tempList, a, n, l); // interchange role of a and tempList
    }

    delete[] tempList;
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

    MergeSort(a, n);

    cout << "排序後結果: ";
    for (int i = 1; i <= n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;

    delete[] a;

    return 0;
}
```

### input
```text
請輸入資料筆數 n: 8
請輸入 8 個數字: 8 3 5 1 7 2 6 4
```

### output
```text
排序後結果: 1 2 3 4 5 6 7 8
```

### 時間複雜度
> Best Case
```text
O(n log n)
```
> Average Case
```text
O(n log n)
```
> Worst Case
```text
O(n log n)
```

## Recursive Merge Sort
```cpp
#include <iostream>
using namespace std;

template <class T>
int ListMerge(T *a, int *link, const int start1, const int start2)
{
    int i = start1;
    int j = start2;
    int first = 0;
    int last = 0;

    while (i != 0 && j != 0)
    {
        int selected;

        if (a[i] <= a[j])
        {
            selected = i;
            i = link[i];
        }
        else
        {
            selected = j;
            j = link[j];
        }

        if (first == 0)
            first = selected;
        else
            link[last] = selected;

        last = selected;
    }

    if (i != 0)
    {
        if (first == 0)
            first = i;
        else
            link[last] = i;
    }
    else
    {
        if (first == 0)
            first = j;
        else
            link[last] = j;
    }

    return first;
}

template <class T>
int rMergeSort(T* a, int* link, const int left, const int right)
{// a[left:right] is to be sorted. link[i] is initially 0 for all i.
 // rMergeSort returns the index of the first element in the sorted chain.
    if (left >= right) return left;
    int mid = (left + right) / 2;
    return ListMerge(a, link,
        rMergeSort(a, link, left, mid),       // sort left half
        rMergeSort(a, link, mid + 1, right)); // sort right half
}

int main()
{
    int n;

    cout << "請輸入資料筆數 n: ";
    cin >> n;

    int *a = new int[n + 1];
    int *link = new int[n + 1];

    cout << "請輸入 " << n << " 個數字: ";
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        link[i] = 0;
    }

    int first = rMergeSort(a, link, 1, n);

    cout << "排序後結果: ";
    for (int i = first; i != 0; i = link[i])
    {
        cout << a[i] << " ";
    }
    cout << endl;

    cout << "排序後的 link 陣列: " << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << "link[" << i << "] = " << link[i] << endl;
    }

    delete[] a;
    delete[] link;

    return 0;
}
```

### input
```text
請輸入資料筆數 n: 5
請輸入 5 個數字: 5 2 4 1 3
```

### output
```text
排序後結果: 1 2 3 4 5
排序後的 link 陣列:
link[1] = 0
link[2] = 5
link[3] = 1
link[4] = 2
link[5] = 3
```

### 時間複雜度
> Best Case
```text
O(n log n)
```
> Average Case
```text
O(n log n)
```
> Worst Case
```text
O(n log n)
```

## List Merge() for rMergeSort()
```cpp
#include <iostream>
using namespace std;

template <class T>
int ListMerge(T* a, int* link, const int start1, const int start2)
{// The sorted chains beginning at start1 and start2, respectively, are merged.
 // link[0] is used as a temporary header. Return start of merged chain.
    int iResult = 0; // last record of result chain

    int i1 = start1;
    int i2 = start2;

    for (; i1 && i2; )
        if (a[i1] <= a[i2]) {
            link[iResult] = i1;
            iResult = i1; 
            i1 = link[i1];
        }
        else {
            link[iResult] = i2;
            iResult = i2; 
            i2 = link[i2];
        }

    // attach remaining records to result chain
    if (i1 == 0) 
        link[iResult] = i2;
    else 
        link[iResult] = i1;

    return link[0];
}

template <class T>
int rMergeSort(T* a, int* link, const int left, const int right)
{// a[left:right] is to be sorted. link[i] is initially 0 for all i.
 // rMergeSort returns the index of the first element in the sorted chain.
    if (left >= right) return left;
    int mid = (left + right) / 2;
    return ListMerge(a, link,
        rMergeSort(a, link, left, mid),       // sort left half
        rMergeSort(a, link, mid + 1, right)); // sort right half
}

int main()
{
    int n;

    cout << "請輸入資料筆數 n: ";
    cin >> n;

    int* a = new int[n + 1];
    int* link = new int[n + 1];

    cout << "請輸入 " << n << " 個數字: ";
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        link[i] = 0;
    }

    link[0] = 0;

    int first = rMergeSort(a, link, 1, n);

    cout << "排序後結果: ";
    for (int i = first; i != 0; i = link[i])
    {
        cout << a[i] << " ";
    }
    cout << endl;

    cout << "排序後的 link 陣列:" << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << "link[" << i << "] = " << link[i] << endl;
    }

    delete[] a;
    delete[] link;

    return 0;
}
```

### input
```text
請輸入資料筆數 n: 5
請輸入 5 個數字: 5 2 4 1 3
```

### output
```text
排序後結果: 1 2 3 4 5
排序後的 link 陣列:
link[1] = 0
link[2] = 5
link[3] = 1
link[4] = 2
link[5] = 3
```

### 時間複雜度
> Best Case
```text
O(n)
```
> Average Case
```text
O(n)
```
> Worst Case
```text
O(n)
```

## Heap Sort
```text
Heap() + Adjust()
```

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
void Adjust(T *a, const int root, const int n)
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
void HeapSort(T *a, const int n)
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

    int *a = new int[n + 1];

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
```

### input
```text
請輸入資料筆數 n: 8
請輸入 8 個數字: 8 3 5 1 7 2 6 4
```

### output
```text
排序後結果: 1 2 3 4 5 6 7 8
```

### 時間複雜度
> Best Case
```text
O(n log n)
```
> Average Case
```text
O(n log n)
```
> Worst Case
```text
O(n log n)
```

## 時間複雜度總表
| Sorting Method | Best Case | Average Case | Worst Case |
|---|---|---|---|
| Insertion Sort | O(n) | O(n^2) | O(n^2) |
| Quick Sort, median-of-three | O(n log n) | O(n log n) | O(n^2) |
| Iterative Merge Sort | O(n log n) | O(n log n) | O(n log n) |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) |
