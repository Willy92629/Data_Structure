#include<stdio.h>
#include<stdlib.h>
#include<String.h>


void prt(int com[][100]){
	int i,j,k;
	for(i=0; i<100; i++){
		if(com[i][0] == 0)
			break;
		for(j=0; j<100; j++){
			if(com[i][j] != 0){
				printf("%d ",com[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");
}

void decol(int arr[][100], int col){
	int i,j;
	for(i=0;i<100;i++){
		if(arr[i][0] == 0)
			break;
		for(j=col;j<99;j++){
			arr[i][j] = arr[i][j+1];
			if(arr[i][j] == 0)
				break; 
		}
	}
}

void depnt(int arr[][100], int row, int col){
	int i;
	for(i=col;i<100;i++){
		arr[row][i] = arr[row][i+1];
		if(arr[row][i] == 0)
			break;
	}
}

void rotate(int com[][100]){
	int i,j,k,c,arr[100][100]={0};
	for(i=0; i<100; i++){
		for(j=99, k=0; j>=0; j--){
			if(com[j][i] != 0){
				arr[i][k] = com[j][i];
				k++;
			}
		}
	}
	for(i=0; i<100; i++){
		for(j=0; j<100; j++){
			com[i][j] = arr[i][j];
		}
	}
}

int main(){
	int n,D2;
	int i=0,j,k,temp,dr,dc;
	int m[100][100] = {0};
	char com[20],a[10];
	
	FILE *fp;
	if ((fp = fopen("input1.txt","r"))== NULL){//TestFile ("filename", mode)
        printf("Error when opening file");
        exit(1);
    }
	
	while( !feof(fp) ){
		fgets(com, 20, fp);
		if(isdigit(com[0])){
			if(i != 0){
				prt(m);
			}
			n = atoi(com);
			temp = 1;
			for(j=0;j<n;j++){
				for(k=0;k<n;k++){
					m[j][k]=temp;
					temp++;
				}
			}
		}else if(com[0] == 'R'){
			rotate(m);
		}else if(com[0] == 'D'){
			if(isdigit(com[2])){
				j = 2;
				while(1){
					if(isdigit(com[j])){
						a[strlen(a)] = com[j];
					}else{
						dc = atoi(a);
						memset(a ,0,sizeof(a));
						break;
					}
					j++;
				}
				decol( m, dc-1);
			}else{
				j = 4;
				while(1){
					if(com[j] != ' '){
						a[strlen(a)] = com[j];
					}else{
						dr = atoi(a);
						memset(a ,0,sizeof(a));
						j++;
						break;
					}
					j++;
				}
				while(1){
					if(com[j] != ' '){
						a[strlen(a)] = com[j];
					}else{
						dc = atoi(a);
						memset(a ,0,sizeof(a));
						break;
					}
					j++;
				}
				depnt(m, dr-1, dc-1);
			}
		}else if(com[0] == 'I'){
			for(j=0;j<100;j++){
				if(m[j][0] == 0)
					break;
				for(k=1;k<100;k++){
					if(m[j][k] == 0){
						m[j][k]=temp;
						temp++;
						break;
					}
				}
			}
		}
		i++;
	}
	prt(m);
	return 0;
}
