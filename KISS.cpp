#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main()
{
    int n, m, sum = 0, sum1 = 0, tek1 = 0, tek2 = 0, e = 0, w = 0;
    char c;
    string s, f;
    getline(cin, s);
    f = s[0];
    for(int j = 1; j < s.size(); j++)
        {
            if (s[j] == ' ')
            {
                n = atoi(f.c_str());
                f = "";
            }
            else
            f += s[j];
        }
    m = atoi(f.c_str());
    vector< vector<int> > v1;
    vector<int> v2;

    int d;
    for(int i = 0; i < n; i++)
    {
        getline(cin, s);
        f = s[0];
        for(int j = 1; j < s.size(); j++)
        {
            if (s[j] == ' ')
            {
                d = atoi(f.c_str());
                v2.push_back(d);
                f = "";
            }
            else
            f += s[j];
        }
        d = atoi(f.c_str());
        v2.push_back(d);
        v1.push_back(v2);
        v2.clear();
    }
    for(int i = 0; i < n; i++)
    {
        sum = max(sum, sum1);
        sum1 = v1[i][0];
        tek1 = i;
        tek2 = 0;
        for(int j = 0; j < m; j++)
        {
            if (sum1 < v1[i][j])
            {
                sum1 = v1[i][j];
                tek1 = i;
                tek2 = j;
            }
        }
        if (sum1 > sum)
        {
            e = tek1;
            w = tek2;
            sum = sum1;
        }

    }
    cout << sum << endl;
    cout << e << ' ' << w;
    return 0;
}

