#include <iostream>
using namespace std;

void cleararr(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = 0;
    }
}
int main()
{
    int arr[3] = {3, 2, 4};
    cleararr(arr, 3);
}
