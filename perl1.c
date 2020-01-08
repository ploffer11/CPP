#include <stdio.h>

double score;
char str[100];
int main()
{
    printf("이름? ");
    scanf("%s", str);

    printf("학점? ");
    scanf("%lf", &score);

    printf("%s의 학점은 %lf입니다.", str, score);
}