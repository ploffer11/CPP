#include <stdio.h>
#include <string.h>

int time_to_string(char arr[], int max, int hour, int minute, int second)
{
    if (!(0 <= hour && hour <= 23))
        return -1;

    if (!(0 <= minute && minute <= 59))
        return -1;

    if (!(0 <= second && second <= 59))
        return -1;

    arr[0] = '0' + hour / 10;
    arr[1] = '0' + hour % 10;
    arr[2] = ':';
    arr[3] = '0' + minute / 10;
    arr[4] = '0' + minute % 10;
    arr[5] = ':';
    arr[6] = '0' + second / 10;
    arr[7] = '0' + second % 10;
    arr[8] = '\0';

    return 8;
}

int main()
{
    char s[10] = {0};
    int a, b, c;

    printf("½Ã ºÐ ÃÊ? ");
    scanf("%d %d %d", &a, &b, &c);

    time_to_string(s, 10, a, b, c);
    printf("%s", s);
}