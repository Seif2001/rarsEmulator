#include <iostream>
using namespace std;

int sum(int n)
{
    if (n == 0 || n == 1)
    {
        return n;
    }
    else
    {
        return n + (sum(n - 1));
    }
}
int main()
{
    int s = 2, t = 3, temp = 0;
    temp = s;
    s = t;
    t = temp;
    cout << sum(5);
    return 0;
}