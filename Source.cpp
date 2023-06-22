#include <iostream>
#include <future>
#include <thread>
#include <chrono>
using namespace std;


void merge(int low, int mid, int high, vector<int>& num)
{
    vector<int> copy(num.size());
    int h, i, j, k;
    h = low;
    i = low;
    j = mid + 1;

    while ((h <= mid) && (j <= high))
    {
        if (num[h] <= num[j])
        {
            copy[i] = num[h];
            h++;
        }
        else
        {
            copy[i] = num[j];
            j++;
        }
        i++;
    }
    if (h > mid)
    {
        for (k = j; k <= high; k++)
        {
            copy[i] = num[k];
            i++;
        }
    }
    else
    {
        for (k = h; k <= mid; k++)
        {
            copy[i] = num[k];
            i++;
        }
    }
    for (k = low; k <= high; k++)
        swap(num[k], copy[k]);
}


void merge_sort(int low, int high, vector<int>& num)
{
    int mid;
    if (low < high)
    {
        mid = low + (high - low) / 2;
        auto future1 = std::async(std::launch::deferred, [&]()
            {
                merge_sort(low, mid, num);
            });
        auto future2 = std::async(std::launch::deferred, [&]()
            {
                merge_sort(mid + 1, high, num);
            });

        future1.get();
        future2.get();
        merge(low, mid, high, num);
    }
}