# 41141205
Homework Sorting Project

## 解題說明
本次作業要求實作並比較多種排序法的效能，包含 Insertion Sort、Quick Sort、Iterative Merge Sort 與 Heap Sort。
透過不同資料量的測試，觀察各排序法在不同情況下的執行時間，並分析其時間複雜度。

本作業中的 Quick Sort 依照要求使用 median-of-three method 選擇 pivot；Merge Sort 則使用 Iterative Merge Sort 的方式實作。

## 解題策略
### 1.分別實作四種排序法：
- Insertion Sort
- Quick Sort, median-of-three
- Iterative Merge Sort
- Heap Sort
### 2.使用相同的測試資料，分別執行四種排序法。
### 3.比較不同排序法在不同資料量下的執行結果與效率。
### 4.分析各排序法的 Best Case、Average Case 與 Worst Case 時間複雜度。
### 5.根據實驗結果，觀察哪一種排序法在不同資料量下較適合使用。

## 程式實作
以下為主要程式碼：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <psapi.h>

using namespace std;

// =====================================================
// 測試結果結構
// =====================================================
struct TestResult
{
    string caseName;
    string sortName;
    double timeMs;
    size_t memoryBefore;
    size_t memoryAfter;
    size_t estimatedExtraMemory;
};

// =====================================================
// 取得目前程式記憶體使用量，單位 KB
// =====================================================
size_t getMemoryKB()
{
    PROCESS_MEMORY_COUNTERS pmc;

    GetProcessMemoryInfo(
        GetCurrentProcess(),
        &pmc,
        sizeof(pmc)
    );

    return pmc.WorkingSetSize / 1024;
}

// =====================================================
// 檢查排序是否成功
// =====================================================
bool isSorted(const vector<int>& data)
{
    for (int i = 1; i < (int)data.size(); i++)
    {
        if (data[i - 1] > data[i])
            return false;
    }
    return true;
}

// =====================================================
// Insertion Sort
// =====================================================
void insertionSort(vector<int>& data)
{
    for (int i = 1; i < (int)data.size(); i++)
    {
        int key = data[i];
        int j = i - 1;

        while (j >= 0 && data[j] > key)
        {
            data[j + 1] = data[j];
            j--;
        }

        data[j + 1] = key;
    }
}

// =====================================================
// Quick Sort：median-of-three
// =====================================================
int medianOfThree(vector<int>& data, int left, int right)
{
    int mid = (left + right) / 2;

    if (data[mid] < data[left])
        swap(data[mid], data[left]);

    if (data[right] < data[left])
        swap(data[right], data[left]);

    if (data[right] < data[mid])
        swap(data[right], data[mid]);

    swap(data[mid], data[right - 1]);

    return data[right - 1];
}

void quickSortRecursive(vector<int>& data, int left, int right)
{
    if (left + 10 <= right)
    {
        int pivot = medianOfThree(data, left, right);

        int i = left;
        int j = right - 1;

        while (true)
        {
            while (data[++i] < pivot) {}
            while (data[--j] > pivot) {}

            if (i < j)
                swap(data[i], data[j]);
            else
                break;
        }

        swap(data[i], data[right - 1]);

        quickSortRecursive(data, left, i - 1);
        quickSortRecursive(data, i + 1, right);
    }
    else
    {
        for (int p = left + 1; p <= right; p++)
        {
            int temp = data[p];
            int j = p;

            while (j > left && temp < data[j - 1])
            {
                data[j] = data[j - 1];
                j--;
            }

            data[j] = temp;
        }
    }
}

void quickSort(vector<int>& data)
{
    if (!data.empty())
        quickSortRecursive(data, 0, (int)data.size() - 1);
}

// =====================================================
// Merge Sort
// =====================================================
void mergeData(vector<int>& data, vector<int>& temp, int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right)
    {
        if (data[i] <= data[j])
            temp[k++] = data[i++];
        else
            temp[k++] = data[j++];
    }

    while (i <= mid)
        temp[k++] = data[i++];

    while (j <= right)
        temp[k++] = data[j++];

    for (int p = left; p <= right; p++)
        data[p] = temp[p];
}

void mergeSortRecursive(vector<int>& data, vector<int>& temp, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;

        mergeSortRecursive(data, temp, left, mid);
        mergeSortRecursive(data, temp, mid + 1, right);

        mergeData(data, temp, left, mid, right);
    }
}

void mergeSort(vector<int>& data)
{
    vector<int> temp(data.size());

    if (!data.empty())
        mergeSortRecursive(data, temp, 0, (int)data.size() - 1);
}

// =====================================================
// Heap Sort
// =====================================================
void heapify(vector<int>& data, int n, int root)
{
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < n && data[left] > data[largest])
        largest = left;

    if (right < n && data[right] > data[largest])
        largest = right;

    if (largest != root)
    {
        swap(data[root], data[largest]);
        heapify(data, n, largest);
    }
}

void heapSort(vector<int>& data)
{
    int n = (int)data.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(data, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        swap(data[0], data[i]);
        heapify(data, i, 0);
    }
}

// =====================================================
// Composite Sort
// 小資料用 Insertion Sort，大資料用 Quick Sort
// =====================================================
void compositeSortRecursive(vector<int>& data, int left, int right)
{
    const int THRESHOLD = 20;

    if (right - left + 1 <= THRESHOLD)
    {
        for (int i = left + 1; i <= right; i++)
        {
            int key = data[i];
            int j = i - 1;

            while (j >= left && data[j] > key)
            {
                data[j + 1] = data[j];
                j--;
            }

            data[j + 1] = key;
        }
        return;
    }

    int pivot = data[(left + right) / 2];
    int i = left;
    int j = right;

    while (i <= j)
    {
        while (data[i] < pivot)
            i++;

        while (data[j] > pivot)
            j--;

        if (i <= j)
        {
            swap(data[i], data[j]);
            i++;
            j--;
        }
    }

    if (left < j)
        compositeSortRecursive(data, left, j);

    if (i < right)
        compositeSortRecursive(data, i, right);
}

void compositeSort(vector<int>& data)
{
    if (!data.empty())
        compositeSortRecursive(data, 0, (int)data.size() - 1);
}

// =====================================================
// 測試排序：回傳測試結果，不直接輸出
// =====================================================
template <class SortFunction>
TestResult testSort(
    string caseName,
    string sortName,
    vector<int> data,
    SortFunction sortFunc,
    size_t estimatedExtraMemoryKB
)
{
    size_t memoryBefore = getMemoryKB();

    auto start = chrono::high_resolution_clock::now();

    sortFunc(data);

    auto end = chrono::high_resolution_clock::now();

    size_t memoryAfter = getMemoryKB();

    chrono::duration<double, milli> elapsed = end - start;

    if (!isSorted(data))
    {
        cout << sortName << " 在 " << caseName << " 排序失敗！" << endl;
    }

    TestResult result;
    result.caseName = caseName;
    result.sortName = sortName;
    result.timeMs = elapsed.count();
    result.memoryBefore = memoryBefore;
    result.memoryAfter = memoryAfter;
    result.estimatedExtraMemory = estimatedExtraMemoryKB;

    return result;
}

// =====================================================
// 輸出表格
// =====================================================
void printTable(const vector<TestResult>& results)
{
    cout << fixed << setprecision(2);

    cout << left
         << setw(22) << "Sort Method"
         << setw(15) << "Case"
         << setw(15) << "Time(ms)"
         << setw(22) << "Memory Before(KB)"
         << setw(22) << "Memory After(KB)"
         << setw(28) << "Extra Memory(KB)"
         << endl;

    cout << string(124, '-') << endl;

    for (const auto& r : results)
    {
        cout << left
             << setw(22) << r.sortName
             << setw(15) << r.caseName
             << setw(15) << r.timeMs
             << setw(22) << r.memoryBefore
             << setw(22) << r.memoryAfter
             << setw(28) << r.estimatedExtraMemory
             << endl;
    }
}

// =====================================================
// 產生 Best Case：由小到大
// =====================================================
vector<int> generateBestData(int n)
{
    vector<int> data;

    for (int i = 1; i <= n; i++)
        data.push_back(i);

    return data;
}

// =====================================================
// 產生 Average Case：亂數
// =====================================================
vector<int> generateAverageData(int n)
{
    vector<int> data;

    for (int i = 0; i < n; i++)
        data.push_back(rand());

    return data;
}

// =====================================================
// 產生 Worst Case：由大到小
// =====================================================
vector<int> generateWorstData(int n)
{
    vector<int> data;

    for (int i = n; i >= 1; i--)
        data.push_back(i);

    return data;
}

// =====================================================
// main 主程式
// =====================================================
int main()
{
    srand((unsigned)time(NULL));

    int n;

    cout << "請輸入資料筆數 n: ";
    cin >> n;

    vector<int> bestData = generateBestData(n);
    vector<int> averageData = generateAverageData(n);
    vector<int> worstData = generateWorstData(n);

    size_t zeroExtraMemory = 0;
    size_t mergeExtraMemory = n * sizeof(int) / 1024;

    vector<TestResult> results;

    cout << endl;
    cout << "======================================" << endl;
    cout << "Homework Sorting Project" << endl;
    cout << "資料筆數 N = " << n << endl;
    cout << "======================================" << endl;
    cout << endl;

    // =====================================================
    // Best Case
    // =====================================================
    results.push_back(testSort("Best Case", "Insertion Sort", bestData, insertionSort, zeroExtraMemory));
    results.push_back(testSort("Best Case", "Quick Sort", bestData, quickSort, zeroExtraMemory));
    results.push_back(testSort("Best Case", "Merge Sort", bestData, mergeSort, mergeExtraMemory));
    results.push_back(testSort("Best Case", "Heap Sort", bestData, heapSort, zeroExtraMemory));
    results.push_back(testSort("Best Case", "Composite Sort", bestData, compositeSort, zeroExtraMemory));

    // =====================================================
    // Average Case
    // =====================================================
    results.push_back(testSort("Average Case", "Insertion Sort", averageData, insertionSort, zeroExtraMemory));
    results.push_back(testSort("Average Case", "Quick Sort", averageData, quickSort, zeroExtraMemory));
    results.push_back(testSort("Average Case", "Merge Sort", averageData, mergeSort, mergeExtraMemory));
    results.push_back(testSort("Average Case", "Heap Sort", averageData, heapSort, zeroExtraMemory));
    results.push_back(testSort("Average Case", "Composite Sort", averageData, compositeSort, zeroExtraMemory));

    // =====================================================
    // Worst Case
    // =====================================================
    results.push_back(testSort("Worst Case", "Insertion Sort", worstData, insertionSort, zeroExtraMemory));
    results.push_back(testSort("Worst Case", "Quick Sort", worstData, quickSort, zeroExtraMemory));
    results.push_back(testSort("Worst Case", "Merge Sort", worstData, mergeSort, mergeExtraMemory));
    results.push_back(testSort("Worst Case", "Heap Sort", worstData, heapSort, zeroExtraMemory));
    results.push_back(testSort("Worst Case", "Composite Sort", worstData, compositeSort, zeroExtraMemory));

    printTable(results);

    return 0;
}
```

<img width="1134" height="469" alt="image" src="https://github.com/user-attachments/assets/d61f8207-30c4-4365-8dc5-2517e1a0f4bf" />

## 結論
本次 Homework Sorting Project 主要實作並比較 Insertion Sort、Quick Sort、Iterative Merge Sort 與 Heap Sort 四種排序法。透過實際撰寫程式與測試不同資料狀態，可以更清楚看出每種排序法在效率上的差異。

Insertion Sort 的程式邏輯最簡單，當資料量較小或資料已經接近排序完成時，執行效率不錯；但如果資料量變大，或資料呈現反向排序，因為需要大量比較與搬移，時間複雜度會變成 O(n^2)，執行時間會明顯增加。

Quick Sort 在平均情況下效率很好，本次作業依照要求使用 median-of-three method 選擇 pivot，能降低選到太大或太小 pivot 的機率，使排序過程更穩定。不過 Quick Sort 在最壞情況下仍可能退化成 O(n^2)，所以 pivot 的選擇方式會影響實際執行效率。

Iterative Merge Sort 的優點是 Best Case、Average Case 與 Worst Case 都能維持 O(n log n)，因此在不同資料狀態下表現都相對穩定。不過它需要額外的暫存陣列，所以空間複雜度為 O(n)。

Heap Sort 同樣在三種情況下都能維持 O(n log n)，而且是原地排序，額外空間需求較少。相較於 Merge Sort，Heap Sort 的空間使用較低，但程式邏輯與 heap 調整過程較複雜。

綜合比較後，可以發現沒有一種排序法在所有情況下都一定是最好的。小資料量或接近排序完成的資料可以考慮使用 Insertion Sort；若重視平均效率，可以使用 Quick Sort；若希望在各種情況下都有穩定表現，則 Merge Sort 與 Heap Sort 會比較適合。透過這次作業，我了解到演算法不能只看理論時間複雜度，也需要搭配實際測試結果、資料狀態與記憶體使用量來判斷哪一種排序法較適合。

## 申論及開發報告
### 選擇不同排序法的原因

在本次作業中，選擇 Insertion Sort、Quick Sort、Iterative Merge Sort 與 Heap Sort 進行比較，是因為這幾種排序法具有不同的演算法特性。

Insertion Sort 的實作方式簡單，適合用來觀察 O(n^2) 排序法在資料量增加時的變化。當資料已經接近排序完成時，Insertion Sort 的表現會比較好，但若資料是反向排序，則需要大量比較與搬移。

Quick Sort 是常見且效率高的排序法，平均時間複雜度為 O(n log n)。本次作業使用 median-of-three method，是為了降低 pivot 選擇不佳的機率，使 Quick Sort 的執行效率更穩定。

Iterative Merge Sort 使用由小到大的合併方式完成排序，避免遞迴呼叫。它的時間複雜度在各種情況下都是 O(n log n)，因此效能表現較穩定。

Heap Sort 則是利用 Max Heap 的特性進行排序。它的優點是在最壞情況下仍然能維持 O(n log n)，而且不需要額外的大量空間。


# 以下為各別實作sort的內容
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

### 效能分析
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

### 效能分析
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

### 效能分析
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

### 效能分析
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

### 效能分析
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

### 效能分析
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
