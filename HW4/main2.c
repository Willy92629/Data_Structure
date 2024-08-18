#include <stdio.h> 
#include <stdlib.h>
#include <String.h>

int main(){
	int lst[100][100]={0} ,follow[100],been[100];
	int r,t,i,j,k,temp,max[2];
	char com[50],a[10];
	
	FILE *fp;
	if ((fp = fopen("input2.txt","r"))== NULL){//TestFile ("filename", mode)
        printf("Error when opening file");
        exit(1);
    }
	
	while( !feof(fp) ){
		fscanf(fp,"%d\n",&t);
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
					lst[0][atoi(a)]++;
					lst[temp][0]++;
					memset(a ,0,sizeof(a));
					i++;
					if(com[j] == ']')
						break;
				}
				j++;
			}
		}
		/*
		for(i=0;i<20;i++){
			for(j=0;j<20;j++){
				printf("%d ",lst[i][j]);
			}
			printf("\n");
		}
		*/
		//been 1/been 2/head 3/inque
		for(i=1;i<100;i++){
			temp = 0;
			if(lst[0][i] != 0 || lst[i][0] != 0){
				for(j=1;j<100;j++){
					if(lst[i][j]==1){
						temp++;
					}
				}
				if(temp == 0){
					been[i] = 2;
				}
			}
		}
		
		while(1){
			for(i=1;i<100;i++){
				if(been[i] == 3){
					for(j=1;j<100;j++){
						if(lst[i][j] == 1 && been[j] != 1){
							temp = 1;
							for(k=1;k<100;k++){
								if(follow[k] == j)
									break;
							}
							if(k==100){
								follow[r] = j;
								r++;
								been[j] = 1;
								for(k=1;k<100;k++){
									if(lst[k][j]==1 && been[k]==0)
										been[k] = 3;
								}
							}
						} 
					}
					for(k=1;k<100;k++){
						if(lst[k][i]==1 && been[k]==0)
							been[k] = 3;
					}
					been[i] = 1;
					follow[r] = i;
					r++;
					temp = 20;
					break;
				}
			}
			if(temp == 20){
				temp = 0;
				continue;
			}
			
			for(i=1;i<100;i++){
				if(been[i] == 2){
					been[i] = 1;
					follow[r] = i;
					r++;
					for(k=1;k<100;k++){
						if(lst[k][i]== 1 && been[k] == 0)
							been[k] = 3;
					}
					break;
				}
			}
			
			temp=0;
			for(i=1;i<100;i++){
				if(been[i] == 3 || been[i] == 2){
					temp++;
				}
			}
			if(temp == 0)
				break;	
		}
		
		/*
		for(i=1;i<100;i++){
			for(j=1;j<100;j++){
				if(lst[i][j] == 1){
					temp = 1;
					for(k=1;k<100;k++){
						if(follow[k] == j)
							break;
					}
					if(k==100){
						follow[r] = j;
						r++;
					}
					
				}
			}
			if(temp == 1){
				follow[r] = i;
				temp = 0;
				r++;
			}
		}
		*/
		for(i = 0;i < r;i++){
			printf("%d ",follow[i]);
		}
		printf("\n");
		r = 0;
		memset(lst ,0,sizeof(lst));
		memset(been ,0,sizeof(been));
		memset(follow ,0,sizeof(follow));
	}
	return 0;
}
