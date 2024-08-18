#include<stdio.h> 
#include<stdlib.h>
#include<String.h>

int main(){
	int t,m,n;
	int i,j,k;;
	int wo[1000][200]={0};
	
	FILE *fp;
	if ((fp = fopen("input4.txt","r"))== NULL){//TestFile ("filename", mode)
        printf("Error when opening file");
        exit(1);
    }
	fscanf(fp," %d",&t);
	while(t>0){
		fscanf(fp," %d %d",&m,&n);
		for(i=0;i<m;i++){
			for(j=0;j<n;j++){
				fscanf(fp," %d",&wo[m][n]);
			}
		}
		
		
		
		
		
		
		
		
		
		
		memset(wo,0,sizeof(wo));
		t--;
	}
	return 0;
}
