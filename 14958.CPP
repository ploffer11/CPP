#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

using cp = complex<double>;
using func = vector<cp>;
class FastFourierTransform
{
private:
    const double PI = acos(-1);

    void FFT(func &f, cp w)
    {
        int n = f.size();
        if (n == 1)
            return;

        func even(n / 2), odd(n / 2);
        for (int i = 0; i < n; i++)
            (i & 1 ? odd : even)[i / 2] = f[i];

        FFT(even, w * w);
        FFT(odd, w * w);

        cp wp(1, 0);
        for (int i = 0; i < n / 2; i++)
        {
            f[i] = even[i] + wp * odd[i];
            f[i + n / 2] = even[i] - wp * odd[i];
            wp *= w;
        }
    }

public:
    func multiply(func f, func g)
    {
        int sz = f.size() + g.size() - 1;
        int n = 1;
        while (n < f.size() + 1 || n < g.size() + 1)
            n *= 2;
        n *= 2;
        func h(n);
        f.resize(n);
        g.resize(n);

        cp w(cos(2 * PI / n), sin(2 * PI / n));

        FFT(f, w);
        FFT(g, w);

        for (int i = 0; i < n; i++)
            h[i] = f[i] * g[i];

        FFT(h, cp(1, 0) / w);
        for (int i = 0; i < n; i++)
        {
            h[i] /= cp(n, 0);
            h[i] = cp(round(h[i].real()), round(h[i].imag()));
        }

        while (h.size() != sz)
            h.pop_back();

        return h;
    }
};

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    FastFourierTransform FFT;

    func rock, scissors, paper;

    int m, n;
    cin >> m >> n;
    string inp, t;
    cin >> inp >> t;

    for (auto i : inp)
    {
        rock.push_back(i == 'R' ? 1 : 0);
        scissors.push_back(i == 'S' ? 1 : 0);
        paper.push_back(i == 'P' ? 1 : 0);
    }

    func r, s, p;

    reverse(t.begin(), t.end());
    for (auto i : t)
    {
        r.push_back(i == 'P' ? 1 : 0);
        s.push_back(i == 'R' ? 1 : 0);
        p.push_back(i == 'S' ? 1 : 0);
    }

    func h1 = FFT.multiply(rock, r);
    func h2 = FFT.multiply(scissors, s);
    func h3 = FFT.multiply(paper, p);

    int ans = 0;
    for (int i = n - 1; i < h1.size(); i++)
    {
        ans = max(ans, (int)(h1[i] + h2[i] + h3[i]).real());
    }
    cout << ans;
}