#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Size 201

/* �I�]���D */

int max(int a,int b){
	return (a > b) ? a : b;
}

int main(){
	clock_t start,end;
	start = clock();
	FILE *fp;
	fp = fopen("./input4(10000).txt","r");
	FILE *fp2;
	fp2 =fopen("./����2-4(10000).txt","w+");
	int arr[Size] = {0};
	int sample;
	int i,j,k,l,m;
	int cake,friend,waste;          //�J�|�����A�X��B�͡A���@�M���O�h�ֳ��
	int stomach;
	fscanf(fp,"%d",&sample);        //�X������ 
	for(i=0;i<sample;i++){
		fscanf(fp,"%d %d %d",&cake,&friend,&waste);
		for(j=0;j<friend;j++){
			fscanf(fp,"%d",&stomach);            //�s�B�ͭ��q����
			arr[j] = stomach;
		}
		
		int v[cake + 1 + waste];      //�s���ת��ȡAdp
		
		for(k=0; k < cake + 1 + waste; k++){         //��S�ιL���}�C����l��
			v[k] = 0;
		}
		
		for(l=0;l<friend;l++){
			for(m = cake + waste; m >= arr[l] + waste; m--){           //��s�̤j�� 
				v[m] = max(v[m], v[m - arr[l] - waste] + arr[l]);
			}
		}
		//printf("%d\n",v[cake + waste]);        //�Sprint�֨���k
		fprintf(fp2,"%d\n",v[cake + waste]);
		//memset(arr,0,250);
	}
	end = clock();
	double dtime = end - start;
	printf("time = %f s(��)",dtime/1000);        //�@���� 
}
