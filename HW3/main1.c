#include<stdio.h>
#include<stdlib.h>

int main(){
	int in[100][2] = {0} ,out[100][100];
	int i,j,k,gp,last,list;
	char ch;
	
	FILE *fp;
	if ((fp = fopen("input1.txt","r"))== NULL){//TestFile ("filename", mode)
        printf("Error when opening file");
        exit(1);
    }
    
	while(fscanf(fp,"%c",&ch) != EOF){
		i = 0;j = 0;
		if(ch == '['){
			do{
				fscanf(fp,"[%d,%d]",&in[i][0],&in[i][1]);
				i++;
				fscanf(fp,"%c",&ch);
			}while(ch == ',');
			gp = i;
		}else{
			continue;
		}
		for(i=0;i < gp;i++){
			if(in[i][0] == -1){
				out[j][0] = in[i][0];
				out[j][1] = in[i][1];
				j++;
			}
			list = j;
		}
		
		for(i=0, last=1;i < list;i++){
			last = 1;
			for(j = 0;j < gp;j++){
				for(k = 0;k < gp;k++){
					if(in[k][0] == out [i][last]){
						out[i][++last] = in[k][1];
 					}
	 				if(out[i][last]==-1)
	 					break;
				}
			}
		}
		for(i=0, k=1;i < list;i++){
			while(out[i][k] != -1 && out[i][k] != 0 ){
				printf("%d ",out[i][k]);
				k++;
			}
			printf("\n");
			k = 1;
		}
		printf("\n");
	}
	fclose(fp);
	return 0;
}
