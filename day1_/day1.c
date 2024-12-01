#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_POINTS 1000

void mergeSort(int arr[], int l, int r);

int main(int argc, string argv[])
{
    FILE *fp = fopen(argv[1], "r");
    int count = 0;
    char c;
    int rlist[MAX_POINTS];
    int llist[MAX_POINTS];

    if (fp == NULL)
    {
        return 1;
    }

    while (fscanf(fp, "%d %d", &rlist[count], &llist[count]) == 2)
    {
        printf("%d, %d\n", rlist[count], llist[count]);
        count++;
    }

    fclose(fp);
    mergeSort(rlist, 0, MAX_POINTS - 1);
    mergeSort(llist, 0, MAX_POINTS - 1);

    printf("-----------PART-ONE----------\n");
    int sum = 0;
    for (int i = 0; i < MAX_POINTS; i++)
    {
        sum += abs(rlist[i] - llist[i]);
    }

    printf("answer: %d\n", sum);

    printf("-----------PART-TWO----------\n");
    int sum2 = 0;
    int i1 = 0;
    int i2 = 0;
    while (i1 < MAX_POINTS && i2 < MAX_POINTS)
    {
        if (llist[i1] < rlist[i2])
        {
            i1++;
            continue;
        }
        else if (llist[i1] > rlist[i2])
        {
            i2++;
            continue;
        }
        else
        {
            int value = llist[i1];
            int term1 = 0;
            int term2 = 0;

            while (llist[i1] == value)
            {
                term1++;
                i1++;
            }

            while (rlist[i2] == value)
            {
                term2++;
                i2++;
            }

            sum2 += value * term1 * term2;
        }
    }
    printf("answer: %d\n", sum2);
}

void merge(int arr[], int start, int mid, int end)
{
    int start2 = mid + 1;
    if (start2 <= start)
        return;

    while (start <= mid && start2 <= end)
    {
        if (arr[start] <= arr[start2])
        {
            start++;
        }
        else
        {
            int value = arr[start2];
            int index = start2;
            while (index != start)
            {
                arr[index] = arr[index - 1];
                index--;
            }
            arr[start] = value;
            start++;
            mid++;
            start2++;
        }
    }
}

void mergeSort(int array[], int l, int r)
{
    if (r <= l)
        return;

    int mid = l + (r - l) / 2;
    mergeSort(array, l, mid);
    mergeSort(array, mid + 1, r);

    merge(array, l, mid, r);
}
