//HW1_1_4110056015  
#include<stdio.h>
#include<stdlib.h>

int main(){
	FILE *fp;
	if ((fp = fopen("input1.txt","r"))== NULL){//TestFile ("filename", mode)
        printf("Error when opening file");
        exit(1);
    }
	
	int tmp,i = 0,sum = 0,tsum = 0,j;
	
	printf("Current work	turn around time\n");
	while(fscanf(fp," %d",&tmp) != EOF){
		sum+=tmp;
		printf("%d		%d\n",tmp,sum);
		tsum += sum;
		i++;
	}
	
	printf("Avg turn around time: %.2f",(float)tsum/i);
	
	fclose(fp);
	return(0);
}
