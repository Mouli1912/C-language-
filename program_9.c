#include<stdio.h>

int fr[3];

int main(void){
    int page[12]={2,3,2,1,5,2,4,5,3,2,5,2};
    int i,j,flag1=0,pf=0,frsize=3;

    for(i=0;i<3;i++){
        fr[i]=-1;
    }

    for(j=0;j<12;j++){
        flag1=0;
        for(i=0;i<frsize;i++){
            if(fr[i]==page[j]){
                flag1=1;
                break;
            }
        }
        if(flag1==0){
            pf++;
            for(i=0;i<frsize;i++){
                if(fr[i]==-1){
                    fr[i]=page[j];
                    break;
                }
            }
        }
    }

    printf("Number of page faults: %d\n",pf);
    return 0;
}