
// WORST-FIT memory allocation (fixed and portable)
#include <stdio.h>
#include <stdlib.h>

#define MAX 25

int main(void)
{
    int frag[MAX], b[MAX], origB[MAX], f[MAX];
    int i, j, nb, nf;
    int bf[MAX], ff[MAX];

    printf("Memory management scheme: Worst Fit\n");
    printf("Enter the number of blocks: ");
    if (scanf("%d", &nb) != 1 || nb <= 0 || nb > MAX) {
        printf("Invalid number of blocks\n");
        return 1;
    }

    printf("Enter the number of files: ");
    if (scanf("%d", &nf) != 1 || nf <= 0 || nf > MAX) {
        printf("Invalid number of files\n");
        return 1;
    }

    printf("Enter the size of the blocks:\n");
    for (i = 0; i < nb; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &b[i]);
        origB[i] = b[i];
        bf[i] = 0; /* flag: 0 = free, 1 = used */
    }

    printf("Enter the size of the files:\n");
    for (i = 0; i < nf; i++) {
        printf("File %d: ", i + 1);
        scanf("%d", &f[i]);
        ff[i] = -1;
        frag[i] = 0;
    }

    /* Worst-fit allocation: for each file, choose block leaving largest leftover >= 0 */
    for (i = 0; i < nf; i++) {
        int worstIndex = -1;
        int worstRem = -1;
        for (j = 0; j < nb; j++) {
            if (b[j] >= f[i]) {
                int rem = b[j] - f[i];
                if (rem > worstRem) {
                    worstRem = rem;
                    worstIndex = j;
                }
            }
        }
        if (worstIndex != -1) {
            ff[i] = worstIndex;
            frag[i] = worstRem;
            b[worstIndex] = frag[i]; /* remaining size */
            bf[worstIndex] = 1;
        }
    }

    printf("\nFile_no\tFile_size\tBlock_no\tBlock_size\tFragment\n");
    for (i = 0; i < nf; i++) {
        if (ff[i] != -1) {
            printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
                   i + 1, f[i], ff[i] + 1, origB[ff[i]], frag[i]);
        } else {
            printf("%d\t\t%d\t\tNot Allocated\n", i + 1, f[i]);
        }
    }

    return 0;
}

