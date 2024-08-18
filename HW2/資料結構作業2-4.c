#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Size 201

/* 背包問題 */

int max(int a,int b){
	return (a > b) ? a : b;
}

int main(){
	clock_t start,end;
	start = clock();
	FILE *fp;
	fp = fopen("./input4(10000).txt","r");
	FILE *fp2;
	fp2 =fopen("./測資2-4(10000).txt","w+");
	int arr[Size] = {0};
	int sample;
	int i,j,k,l,m;
	int cake,friend,waste;          //蛋糕的單位，幾位朋友，切一刀浪費多少單位
	int stomach;
	fscanf(fp,"%d",&sample);        //幾筆測資 
	for(i=0;i<sample;i++){
		fscanf(fp,"%d %d %d",&cake,&friend,&waste);
		for(j=0;j<friend;j++){
			fscanf(fp,"%d",&stomach);            //存朋友食量的值
			arr[j] = stomach;
		}
		
		int v[cake + 1 + waste];      //存答案的值，dp
		
		for(k=0; k < cake + 1 + waste; k++){         //把沒用過的陣列先初始化
			v[k] = 0;
		}
		
		for(l=0;l<friend;l++){
			for(m = cake + waste; m >= arr[l] + waste; m--){           //更新最大值 
				v[m] = max(v[m], v[m - arr[l] - waste] + arr[l]);
			}
		}
		//printf("%d\n",v[cake + waste]);        //沒print少兩秒左右
		fprintf(fp2,"%d\n",v[cake + waste]);
		//memset(arr,0,250);
	}
	end = clock();
	double dtime = end - start;
	printf("time = %f s(秒)",dtime/1000);        //毫秒換秒 
}
