#include <stdio.h>

int main(void)
{
    int n, tq, i, time = 0, completed = 0;
    int bt[20], rem[20], wt[20], tat[20];
    float avg_wt = 0.0f, avg_tat = 0.0f;

    printf("Enter the number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 20)
    {
        printf("Invalid number of processes.\n");
        return 1;
    }

    printf("Enter the burst time of each process:\n");
    for (i = 0; i < n; i++)
    {
        printf("Process %d: ", i + 1);
        if (scanf("%d", &bt[i]) != 1 || bt[i] < 0)
        {
            printf("Invalid burst time.\n");
            return 1;
        }
        rem[i] = bt[i];
        wt[i] = 0;
        tat[i] = 0;
    }

    printf("Enter time quantum: ");
    if (scanf("%d", &tq) != 1 || tq <= 0)
    {
        printf("Invalid time quantum.\n");
        return 1;
    }

    while (completed < n)
    {
        int flag = 0;

        for (i = 0; i < n; i++)
        {
            if (rem[i] > 0)
            {
                flag = 1;

                if (rem[i] > tq)
                {
                    time += tq;
                    rem[i] -= tq;
                }
                else
                {
                    time += rem[i];
                    tat[i] = time;
                    rem[i] = 0;
                    completed++;
                }
            }
        }

        if (!flag)
            break;
    }

    for (i = 0; i < n; i++)
    {
        wt[i] = tat[i] - bt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", avg_wt / n);
    printf("Average Turnaround Time = %.2f\n", avg_tat / n);

    return 0;
}
