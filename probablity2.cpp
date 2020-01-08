#include <stdio.h>
#include <random>
#include <vector>
#include <utility>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <map>
using namespace std;

#define X_MEAN 50
#define X_STDDEV 10

#define NUMBER 100
#define BIGNUMBER 10000

random_device random;
mt19937 gen(random());

normal_distribution<> X_normal(X_MEAN, X_STDDEV);

double experiment()
{
    return X_normal(gen);
}
char filename[100];

void sol(int x)
{
    for (int i = 0; i < NUMBER; i++)
        printf("%.15lf,", experiment());
    printf("=AVERAGE(A%d:CV%d),=VAR.S(A%d:CV%d)\n", x + 3, x + 3, x + 3, x + 3);
}
int main()
{
    sprintf(filename, "%d-%d-%d.csv", NUMBER, BIGNUMBER, time(NULL));
    freopen(filename, "w", stdout);
    printf("모평균,모분산,시행횟수,표본평균의평균,표본분산의평균\n");
    printf("%d,=%d*%d,%d,=AVERAGE(CW:CW),=AVERAGE(CX:CX)\n", X_MEAN, X_STDDEV, X_STDDEV, BIGNUMBER);
    for (int i = 0; i < BIGNUMBER; i++)
        sol(i);
}