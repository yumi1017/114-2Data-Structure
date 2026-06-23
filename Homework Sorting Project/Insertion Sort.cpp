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