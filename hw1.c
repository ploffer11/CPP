#include <stdio.h>
#include <string.h>

char song[21][50];
char temp[50];
char temp2[50];
int cnt;

int main()
{
    while (1)
    {
        int c;
        printf(" [ 0.���� 1.�߰� 2.���� 3.��� ] ���� ? ");
        scanf("%d\n", &c);

        if (c == 0)
            return 0;

        else if (c == 1)
        {
            printf("�뷡 ����? ");
            fgets(song[cnt++], 50, stdin);
        }

        else if (c == 2)
        {
            printf("ã�� �뷡 ����? ");
            fgets(temp, 50, stdin);
            printf("������ ����? ");
            fgets(temp2, 50, stdin);

            for (int i = 0; i < cnt; i++)
            {
                if (!strcmp(song[i], temp))
                {
                    for (int j = 0; j < strlen(temp2); j++)
                        song[i][j] = temp2[j];
                    break;
                }
            }
        }

        else if (c == 3)
        {
            printf("<< �뷡 ��� >>\n");
            for (int i = 0; i < cnt; i++)
                printf("%s", song[i]);
        }
    }
}