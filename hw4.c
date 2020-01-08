#include <stdio.h>
#include <string.h>

char s1[50], s2[50];
int main()
{
    int cnt = 0;
    int flag = 0;
    while (1)
    {
        printf("word? ");
        scanf("%s", s1);

        if (strlen(s1) <= 2)
        {
            printf("too short, try again\n");
            continue;
        }

        if (!flag)
        {
            strcpy(s2, s1);
            flag = 1;
            cnt++;
            continue;
        }

        if (s2[strlen(s2) - 1] != s1[0])
        {
            printf("WRONG WORD!! YOU FAILED!!!\n count: %d", cnt);
            return 0;
        }

        strcpy(s2, s1);
        cnt++;
    }
}