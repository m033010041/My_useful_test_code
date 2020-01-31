#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int a[64];

void swap(int* array, int x, int y)
{
    int tmp = array[x];
    array[x] = array[y];
    array[y] = tmp;
}


void QuickSort(int* array, int left, int right)
{
    if(left<right)
    {
        int i= left-1, j=right+1;
        int mid = array[(left+right)/2];

        while(true)
        {
            while(array[++i] < mid);
            while(array[--j] > mid);

            if(i>=j)
                break;

            swap(array, i, j);
        }

        QuickSort(array, left, i-1);
        QuickSort(array, j+1, right);
    }
}


int main(int argc, char* argv[])
{
    int i=0;
    cout << "Please input data to sort" << endl;

    while(cin >> a[i])
    {
        if(a[i] != 0)
            i++;
        else
            break;
    }
    cout << "You set " << i << " items." << endl;

    cout << "Original data:" << endl;
    for(int index=0; index<i; index++)
        cout << a[index] << " ";
    cout << endl;
    QuickSort(a, 1, i-1);

    cout << "Sorted data:" << endl;
    for(int index=0; index<i; index++)
        cout << a[index] << " ";
    cout << endl;


    return 0;
}
