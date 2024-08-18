#include <stdio.h> 
#include <stdlib.h>
#include <String.h>

int main(){
	int tar ,lst[100][100]={0} ,follow[100];
	int r,t,i,j,k,temp,max[2];
	char com[50],a[10];
	
	FILE *fp;
	if ((fp = fopen("input1.txt","r"))== NULL){//TestFile ("filename", mode)
        printf("Error when opening file");
        exit(1);
    }
	
	while( !feof(fp) ){
		fscanf(fp,"%d %d\n",&t,&tar);
		for(;t>0;t--){
			j = 0;
			fgets(com, 50, fp);
			while(1){
				if(com[j] != ' '){
					a[strlen(a)] = com[j];
				}else{
					temp = atoi(a);
					memset(a ,0,sizeof(a));
					j++;
					break;
				}
				j++;
			}
			j++;
			while(1){
				if(com[j] != ' ' && com[j] != ']'){
					a[strlen(a)] = com[j];
				}else{
					lst[temp][atoi(a)]++;
					memset(a ,0,sizeof(a));
					i++;
					if(com[j] == ']')
						break;
				}
				j++;
			}
		}
		for(i=0;i<100;i++){
			for(j=0;j<100;j++){
				if(lst[tar][j] == 1 && lst[i][j] == 1){
					for(k=0;k<100;k++){
						if(lst[i][k]==1){
							follow[k]++;
						}
					}
					break;
				}
			}
		}
		follow[tar] = 0;
		for(j=0;j<100;j++){
			if(lst[tar][j] == 1){
				follow[j]=0;
			}
		}
		while(1){
			max[0]=0; 
			for(j=0;j<100;j++){
				if(max[0]<follow[j]){
					max[0] = follow[j];
					max[1] = j;
				}
			}
			if(max[0]==0){
				break;
			}
			printf("%d ",max[1]);
			follow[max[1]] = 0;
		}
		printf("\n");
		memset(lst ,0,sizeof(lst));
		memset(follow ,0,sizeof(follow));
	}
	return 0;
}
