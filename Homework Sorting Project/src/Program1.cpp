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
