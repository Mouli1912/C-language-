// Best-fit

#include<stdio.h>
#include<stdlib.h>

#define MAX 25
int main(void){
    int frag[MAX], b[MAX], origB[MAX], f[MAX];
    int i,j nb,nf;
    int bf[MAX], ff[MAX];

    printf("Memoery management scheme: Best Fit \n");

    printf("Enter the number of blocks:");
    if(scanf("%d", &nb) != || nb <=0 || nb>MAX){
        printf("Invalid number of Blocks\n");
        return 1;

    }
printf("Enter the size of the blocks: \n");
for(i=0; i<nb ; i++){
    printf("Block %d:", i + 1);
    scanf("%d", &b[i]);
    origB[i]= b[i];
    bf[i] =0; /*flag:0 = free, 1= used*/

}
printf("Enter the size of the files:\n;")
}