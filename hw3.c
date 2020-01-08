#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(0));

    printf("엔터 키를 누를 때마다 사용 팁을보여줍니다.\n");
    while (getchar() != EOF)
    {
        int rnd = rand() % 2;

        if (rnd)
        {
            printf("Live Photo의 스틸 이미지를 변경할 수 있습니다\n");
        }
        else
        {
            printf("스크린 타임에서 iPhone의 하루 사용 시간을 알 수 있습니다\n");
        }
    }
}