/* Program to simulate optimal page replacement */
#include <stdio.h>

int fr[10], n, m;

void display(void);

int main(void)
{
    int i, j, page[20];
    int next_use[10], farthest, index, flag, pf = 0;
    float pr;

    printf("Enter length of the reference string: ");
    scanf("%d", &n);

    printf("Enter the reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &page[i]);

    printf("Enter no of frames: ");
    scanf("%d", &m);

    for (i = 0; i < m; i++)
        fr[i] = -1;

    printf("\nPage frames after each reference:\n");

    for (j = 0; j < n; j++)
    {
        flag = 0;

        for (i = 0; i < m; i++)
        {
            if (fr[i] == page[j])
            {
                flag = 1;
                break;
            }
        }

        if (flag == 1)
        {
            display();
            continue;
        }

        for (i = 0; i < m; i++)
        {
            if (fr[i] == -1)
            {
                fr[i] = page[j];
                pf++;
                display();
                flag = 1;
                break;
            }
        }

        if (flag == 1)
            continue;

        for (i = 0; i < m; i++)
            next_use[i] = -1;

        for (i = 0; i < m; i++)
        {
            for (int k = j + 1; k < n; k++)
            {
                if (fr[i] == page[k])
                {
                    next_use[i] = k;
                    break;
                }
            }
        }

        farthest = 0;
        index = 0;

        for (i = 0; i < m; i++)
        {
            if (next_use[i] == -1)
            {
                index = i;
                break;
            }

            if (next_use[i] > farthest)
            {
                farthest = next_use[i];
                index = i;
            }
        }

        fr[index] = page[j];
        pf++;
        display();
    }

    printf("\nNumber of page faults: %d\n", pf);
    pr = (float)pf / n * 100;
    printf("Page fault rate = %.2f%%\n", pr);

    return 0;
}

void display(void)
{
    int i;

    for (i = 0; i < m; i++)
        printf("%d\t", fr[i]);

    printf("\n");
}
