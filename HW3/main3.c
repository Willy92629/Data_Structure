#include<stdio.h>
#include<stdlib.h>
#include <String.h>


void delN(int N[], int deg, int hi, int del,int max, int rpl){
	int i,j;
	if(del<max){
		for(i=del*deg+1,j=rpl*deg+1;i>del*deg+1-deg;i--,j--){
			delN(N,deg,hi,i,max,j);
			if(j>max)
				N[i] = 0;
			else
				N[i] = j;
			
		}
	}
}
int main(){
	int deg, hi, del,max=0;
	int i,j,k;
	int node[1000];
	
	FILE *fp;
	if ((fp = fopen("input3.txt","r"))== NULL){//TestFile ("filename", mode)
        printf("Error when opening file");
        exit(1);
    }
	
	while((fscanf(fp," %d %d %d",&deg,&hi,&del)) != EOF){
		max=0;
		for(i=0;i<hi;i++){
			max = deg*max+1;
		}
		for(i=1;i<=max;i++){
			node[i]=i;
		}
		node[del] = deg*del-((deg+1)/2)+((del-1)%deg)>max ? 0 : deg*del-((deg+1)/2)+((del-1)%deg);
		
		delN(node,deg,hi,del,max,node[del]);
		
		k=0;
		j=1;
		for(i=0;i<hi;i++){	
			k = deg*k+1;
			for(;j<= k;j++){
				if(node[j] != 0)
					printf("%d ",node[j]);
			}
			printf("\n");
		}
		printf("\n");
	}
	fclose(fp);
	return 0;
}
