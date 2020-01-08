#include <stdio.h>
#include <stdlib.h>

int swap(int *a, int *b)
{
    int temp = *b;
    *b = *a;
    *a = temp;
}

void quick_sort(int *arr, int start, int end)
{
    if (start >= end)
        return;

    int pivot = arr[end];
    int i = start, j = end - 1;

    while (i <= j)
    {
        for (; j >= i && pivot < arr[j]; j--)
            continue;
        for (; i <= j && pivot >= arr[i]; i++)
            continue;
        if (i > j)
            break;
        swap(&arr[i], &arr[j]);
    }

    swap(&arr[i], &arr[end]);
    quick_sort(arr, start, i - 1);
    quick_sort(arr, i + 1, end);
}

void merge(int *arr, int start, int mid, int end)
{
    int *newarr = (int *)malloc(sizeof(int) * (end - start + 1));

    int cnt = 0, i = start, j = mid + 1;

    while (i <= mid && j <= end)
    {
        if (arr[i] < arr[j])
            newarr[cnt++] = arr[i++];
        else
            newarr[cnt++] = arr[j++];
    }

    while (i <= mid)
        newarr[cnt++] = arr[i++];

    while (j <= end)
        newarr[cnt++] = arr[j++];

    for (int i = start, j = 0; i <= end; i++, j++)
        arr[i] = newarr[j];
}

void merge_sort(int *arr, int size, int start, int end)
{
    if (start == end)
        return;

    int mid = (start + end) / 2;
    merge_sort(arr, size, start, mid);
    merge_sort(arr, size, mid + 1, end);
    merge(arr, start, mid, end);
}

int main()
{
    int n;

    int *arr = (int *)malloc(sizeof(int) * 10);

    for (int i = 0; i < 10; i++)
        arr[i] = 11 - i;

    merge_sort(arr, 10, 0, 9);
    //quick_sort(arr, 0, 9);

    for (int i = 0; i < 10; i++)
        printf("%d ", arr[i]);
}