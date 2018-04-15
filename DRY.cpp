#include <iostream>
#include <set>

using namespace std;

int main()
{
    set<int> A;
    set<int> B;
    int n, m, d, count = 0;
    cin >> n >> m;
    int mass1[n];
    for (int i = 0; i < n; i++)
    {
        cin >> d;
        A.insert(d);
    }
    for (int i = 0; i < m; i++)
    {
        cin >> d;
        B.insert(d);
    }
    set<int>::iterator it = A.begin();
    for (; it != A.end(); it++)
    {
        if (B.count((*it)) == 1)
        {
            count++;
            mass1[count - 1] = *it;

        }
    }
    cout << count << endl;
    for (int i = 0; i < count; i++)
    {
        cout << mass1[i] << ' ';
    }
    cout << endl;
    cout << n - count << endl;
    for (int i = 0; i < count; i++)
    {
        A.erase(mass1[i]);
        B.erase(mass1[i]);
    }
    set<int>::iterator yt = A.begin();
    for(; yt != A.end(); yt++)
    {
        cout << *yt << ' ';
    }
    cout << endl;
    cout << m - count << endl;
    set<int>::iterator zt = B.begin();
    for(; zt != B.end(); zt++)
    {
        cout << *zt << ' ';
    }
    return 0;
}

