//HW1_2_4110056015 
#include<stdio.h>
#include<stdlib.h>
#include<String.h>
#include<Math.h>

typedef struct{
	int data;
	int seq;
	int locate;
}Task;

int main(){
	FILE *fp;
	
	int tmp,i = 0,j = 0, k = 0 , c = 0;
	int sum[10000] = {0}, tsum = 0, que, len, seq = 1 , locate = 0, last = 0;
	char temp,num[15]={""};
	Task task[100000],ttmp; 
	
	
	if ((fp = fopen("input2.txt","r"))== NULL){//TestFile ("filename", mode)
        printf("Error when opening file");
        exit(1);
    }
	
	fscanf(fp," %d %d ",&que,&len);
	
	printf("Current work	turn around time\n");
	
	while(fscanf(fp,"%c",&temp) != EOF){
		if(temp == '\n'){
			//sort 由data小到大排;
			for(j = last; j < i-1; j++){
				for(k = last; k < i-j+last-1; k++){
					if(task[k].data > task[k+1].data){
						ttmp.data = task[k].data;
						ttmp.locate = task[k].locate;
						ttmp.seq = task[k].seq;
						task[k].data = task[k+1].data;
						task[k].locate = task[k+1].locate;
						task[k].seq = task[k+1].seq;
						task[k+1].data = ttmp.data;
						task[k+1].locate = ttmp.locate;
						task[k+1].seq = ttmp.seq;
					}
				}
			}
			//queuing分堆排locate;
			for(c = 0; c < que ; c++){
				for(j = last + c*(ceil((i-last)/(float)que)); j < last + (c+1)*(ceil((i-last)/(float)que))-1; j++){
					for(k = last + c*(ceil((i-last)/(float)que)) ; k < 2*last + (2*c+1)*(ceil((i-last)/(float)que))-j-1; k++){
						if(k>=i-1){
							break;
						}
						
						if(task[k].locate > task[k+1].locate){
							ttmp.data = task[k].data;
							ttmp.locate = task[k].locate;
							ttmp.seq = task[k].seq;
							task[k].data = task[k+1].data;
							task[k].locate = task[k+1].locate;
							task[k].seq = task[k+1].seq;
							task[k+1].data = ttmp.data;
							task[k+1].locate = ttmp.locate;
							task[k+1].seq = ttmp.seq;
						}
					}
				}
			} 
			//calc
			for(j = last; j < last+len; j++){
				if(j >= i){
					break;
				}
				for(k = 1;k <= seq; k++){
					sum[k]+=task[j].data;
				}
				//print
				printf("%d		%d\n",task[j].data,sum[task[j].seq]);
				tsum += sum[task[j].seq];
			}
			seq++;
			last += len;
		}else if(temp >= '0' && temp <= '9'){
			num[strlen(num)]=temp; 
		}else if(temp == ' '){
			task[i].data = atoi(num);
			task[i].seq = seq;
			task[i].locate = locate;
			memset(num ,0,sizeof(num));
			i++;
			locate++;
		}
	}
	printf("Avg turn around time: %.2f",(float)tsum/i);
	
	fclose(fp);
	return(0);
}
