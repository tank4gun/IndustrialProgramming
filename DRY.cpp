#include <iostream>
#include <set>

using namespace std;

void fill_set(int size, set<int> &set_to_fill) {
    int input_val;
    for(int i = 0; i < size; i++) {
        cin >> input_val;
        set_to_fill.insert(input_val);
    }
}

void print_set(set<int> &set_to_print) {
    set<int>::iterator it = set_to_print.begin();
    for(; it != set_to_print.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

int main()
{
    set<int> A;
    set<int> B;
    int n, m, d, count = 0;
    cin >> n >> m;
    int mass1[n];
    fill_set(n, A);
    fill_set(m, B);
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
    print_set(A);
    cout << m - count << endl;
    print_set(B);
    return 0;
}

