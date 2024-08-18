#include <stdio.h>
#include <stdlib.h>

void S(int a[], int N){
	int i,j,temp;
	for(i=1;i<N;i++){
		for(j=0;j<(N-i);j++){
			if(a[j]>a[j+1])
			{
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp; 
			}
		}
	}
}

int pSum(int arr[], int target, int last, int min, int time){
	int i,temp,sum=0;
	//printf("%dm",sum);
	if(time==0){
		if(target == 0){
			return 1;
		}else if(target > 0){
			return -1;
		}else
			return 0;
	}else if(last==min){
		return -1;
	}else{
		//printf("%dm",sum);
		for(i = last-1;i >= min;i--){ 
		
			temp = pSum(arr,target-arr[i],i,min,time-1);
			if(temp !=-1){
				sum += temp;
			}else{ 
				break;
			} 
			if(sum > 0){
				break;
			}
		}
		return sum;
	}
}
int main(){
	FILE *fp;
	if ((fp = fopen("input4(10000).txt","r"))== NULL){//TestFile ("filename", mode)
        printf("Error when opening file");
        exit(1);
    }
    FILE *fr;
	if ((fr = fopen("output4.txt","w"))== NULL){//TestFile ("filename", mode)
        printf("Error when opening file");
        exit(1);
    }
    int t,m,n,c,max,sum, sumSq[200];
    int fnd[200];
    int i,j,k,l,imin;
    fscanf(fp,"%d",&t);
    
	for(i = 0;i < t;i++){
		max = 0;
		sum = 0;
    	fscanf(fp,"%d %d %d",&m,&n,&c);
    	for(j=0;j<n;j++){
    		fscanf(fp," %d",&fnd[j]);
		}				
		
		S(fnd,n);
		
		if(n==1){
			max = fnd[0];
		}else{
			for(j=1;j<=n;j++){
				sum += fnd[n-j];
				sumSq[j-1] = sum;
				if(sum == m-c*(j-1)){
					max = sum;
					break;
				}else if(sum > m-c*(j-1)){
					//printf("u%d ",j);
					sum -= fnd[n-j];
					for(k=n-j;k>=0;k--){
						imin = k;
						if(fnd[k] <= (m-c*(j-1)-sum)){
							sum+=fnd[k];
							
							max = sum;
							break;
						}
					}
					//找比sum 大 比 (m-c*(j-1)切刀小的可能性 
					for(k=m-c*(j-1);k>sum;k--){
						
						l = pSum(fnd, k, n, imin, j);
						//printf("%dm%dm ",k,imin);
						//printf(" %dlp ",l);
						if(l > 0){
							max = k;
							break;
						}
					} 
					
					imin = 1;
					while(1){
						if(max < (m-c*(j+imin-1))){
							for(k=m-c*(j+imin-1);k > max;k--){
								//printf(" %dlp ",l);
								l = pSum(fnd, k, n, 0, j+imin);
								
								if(l > 0){
									max = k;
									break;
								}
							} 
						}else{
							break;
						}
						imin++;
					}
					
					break;
				
				}else if (m-c*(j-1) - sum <= c){
					//printf("n%d ",j);
					max = sum;
					break;
				}else if(j==n && sum <= m-c*(j-1)){
					max = sum;
					break;
				}
				for(k=0;k < j+imin ;k++){
					if (sumSq[k] > max){
						max = sumSq[k];
					}
				}
			} 
		}
		
		fprintf(fr,"%d\n",max);
	}
	
	return 0;
} 
