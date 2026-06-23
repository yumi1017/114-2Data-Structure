#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
void MedianOfThree(T* a, const int left, const int right)
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
void QuickSort(T* a, const int left, const int right)
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

    int* a = new int[n + 1];

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
