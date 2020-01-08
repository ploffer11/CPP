#include <stdio.h>
#include <random>
#include <vector>
#include <utility>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <map>
using namespace std;
typedef pair<double, double> pdd;
typedef pair<int, int> pii;
// uniform - normal, normal - normal
#define X_RANGE_START 0.0
#define X_RANGE_END 100.0

#define X_MEAN 50
#define X_STDDEV 10

#define NOISE_MEAN 0
#define NOISE_STDDEV 10

#define NUMBER 1000
#define BIGNUMBER 10000

#define PRIMARY_COEFFICIENT 3
#define CONSTANT 5

#define IS_X_NORMAL_DIST false

random_device random;
mt19937 gen(random());
uniform_real_distribution<> X_uni(X_RANGE_START, X_RANGE_END);
normal_distribution<> X_normal(X_MEAN, X_STDDEV);
normal_distribution<> NOISE(NOISE_MEAN, NOISE_STDDEV);

pdd experiment(bool is_x_normal_dist)
{
    return make_pair((is_x_normal_dist) ? X_normal(gen) : X_uni(gen), NOISE(gen));
}
char filename[100];

void sol(bool is_x_normal_dist)
{
    vector<pdd> v, vv;
    for (int i = 0; i < NUMBER; i++)
        v.push_back(experiment(is_x_normal_dist));
    for (int i = 0; i < BIGNUMBER; i++)
        vv.push_back(experiment(is_x_normal_dist));
    sort(v.begin(), v.end());
    sort(vv.begin(), vv.end());
    for (int i = 0; i < vv.size(); i++)
    {
        auto it = vv[i];
        double x = it.first, noise = it.second;
        printf("%.9lf,\"=$F$1*A%d+$G$1+%.9lf\",\"=$F$2*A%d+$G$2\"", x, i + 2, noise, i + 2);
        if (i < v.size())
        {
            auto jt = v[i];
            double sx = jt.first, snoise = jt.second;
            printf(",%.9lf,\"=$F$1*D%d+$G$1+%.9lf\"", sx, i + 2, snoise);
        }
        printf("\n");
    }
}
int main()
{
    sprintf(filename, "%d-%d-%d-%d.csv", NUMBER, IS_X_NORMAL_DIST ? 1 : 0, NOISE_STDDEV, time(NULL));
    freopen(filename, "w", stdout);
    printf("X,Y,Y_HAT,TRAIN_X,TRAIN_Y,%d,%d,=SUMXMY2(B:B,C:C)/%d\n", PRIMARY_COEFFICIENT, CONSTANT, BIGNUMBER);
    sol(IS_X_NORMAL_DIST);
}