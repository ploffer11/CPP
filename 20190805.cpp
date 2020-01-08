#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#define int long long
using namespace std;

vector<int> arr1;
vector<int> arr2;

vector<int> make1;
vector<int> make2;

vector<int> bubun1;
vector<int> bubun2;

void go(int idx, int limit, vector<int> &make, int c)
{
    if (idx == limit)
    {
        if (c == 1)
        {
            int sum = 0;
            for (int i = 0; i < make.size(); i++)
            {
                if (make[i] == 1)
                {
                    sum += arr1[i];
                }
            }

            bubun1.push_back(sum);
        }
        if (c == 2)
        {
            int sum = 0;

            for (int i = 0; i < make.size(); i++)
            {
                if (make[i] == 1)
                {
                    sum += arr2[i];
                }
            }
            bubun2.push_back(sum);
        }
        return;
    }

    make[idx] = 0;
    go(idx + 1, limit, make, c);
    make[idx] = 1;
    go(idx + 1, limit, make, c);
}

main()
{
    int n;

    cin >> n;

    int n1, n2;
    n1 = n / 2;
    n2 = n - n1;

    long long s = 0;

    for (int i = 0; i < n1; i++)
    {
        int tmp;
        cin >> tmp;
        arr1.push_back(tmp);
        s += tmp;
    }

    for (int i = n1; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        arr2.push_back(tmp);
        s += tmp;
    }

    if (s % 2 == 1)
    {
        cout << "NO";
        return 0;
    }

    s /= 2;

    for (int i = 0; i < n1; i++)
    {
        make1.push_back(0);
    }
    for (int i = 0; i < n2; i++)
    {
        make2.push_back(0);
    }

    long long ans = 0;

    go(0, n1, make1, 1);
    go(0, n2, make2, 2);

    sort(bubun1.begin(), bubun1.end());
    sort(bubun2.begin(), bubun2.end());
    reverse(bubun2.begin(), bubun2.end());

    int left = 0;
    int right = 0;

    int leftl = bubun1.size();
    int rightl = bubun2.size();

    while (left < leftl && right < rightl)
    {
        if (bubun1[left] + bubun2[right] == s)
        {
            long long c1 = 1;
            long long c2 = 1;
            left++;
            right++;
            while (left < leftl && bubun1[left] == bubun1[left - 1])
            {
                c1++;
                left++;
            }
            while (right < rightl && bubun2[right] == bubun2[right - 1])
            {
                c2++;
                right++;
            }
            ans += c1 * c2;
        }
        else if (bubun1[left] + bubun2[right] < s)
        {
            left++;
        }
        else if (bubun1[left] + bubun2[right] > s)
        {
            right++;
        }
    }

    if (ans)
    {
        cout << "YES";
    }
    else
    {
        cout << "NO";
    }
}
