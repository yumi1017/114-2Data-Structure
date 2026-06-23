#include <iostream>
using namespace std;

template <class T>
int ListMerge(T* a, int* link, const int start1, const int start2)
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

    int* a = new int[n + 1];
    int* link = new int[n + 1];

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