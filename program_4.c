#include <stdio.h>

int main(void)
{
    int p[20], bt[20], pri[20], wt[20], tat[20], i, k, n, temp;
    float wtavg = 0.0f, tatavg = 0.0f;

    printf("Enter the number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 20)
    {
        printf("Invalid number of processes\n");
        return 1;
    }

    for (i = 0; i < n; i++)
    {
        p[i] = i + 1;
        printf("Enter the Burst Time and Priority for process %d: ", p[i]);
        scanf("%d %d", &bt[i], &pri[i]);
    }

    for (i = 0; i < n - 1; i++)
    {
        for (k = i + 1; k < n; k++)
        {
            if (pri[i] < pri[k])
            {
                temp = p[i];
                p[i] = p[k];
                p[k] = temp;

                temp = bt[i];
                bt[i] = bt[k];
                bt[k] = temp;

                temp = pri[i];
                pri[i] = pri[k];
                pri[k] = temp;
            }
        }
    }

    wt[0] = 0;
    for (i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    for (i = 0; i < n; i++)
    {
        tat[i] = wt[i] + bt[i];
        wtavg += wt[i];
        tatavg += tat[i];
    }

    printf("\nProcess\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i], pri[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", wtavg / n);
    printf("Average Turnaround Time = %.2f\n", tatavg / n);

    return 0;
}
