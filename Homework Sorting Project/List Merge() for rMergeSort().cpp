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