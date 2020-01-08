#include <stdio.h>
#include <string.h>

char s[50];
int main()
{
    while (1)
    {
        printf("전화번호 (.입력 시 종료)? ");
        scanf("%s", s);

        if (s[0] == '.' && strlen(s) == 1)
            return 0;

        if (strlen(s) != 11)
        {
            printf("잘못 입력했습니다. 01012345678 형식으로 입력하세요.\n");
            continue;
        }

        if (!(s[0] == '0' && s[1] == '1' && s[2] == '0'))
        {
            printf("잘못 입력했습니다. 01012345678 형식으로 입력하세요.\n");
            continue;
        }

        int flag = 1;
        for (int i = 3; i < 11; i++)
        {
            if (!('0' <= s[i] && s[i] <= '9'))
            {
                printf("잘못 입력했습니다. 01012345678 형식으로 입력하세요.\n");
                flag = 0;
                break;
            }
        }

        if (flag)
        {
            printf("%s는 유효한 전화번호 입니다.\n", s);
        }
    }
}