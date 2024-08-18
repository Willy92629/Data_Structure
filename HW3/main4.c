#include <stdio.h>
#include <stdlib.h>
#include <String.h>
int same(int fld[][50],int j,int k,int deg,int max){
	int i,ta,tb;
	if(fld[j][0] !=0 && fld[k][0] != 0){
		ta = fld[j][1];
		tb = fld[k][1];
		for(i=2;i<=fld[j][0];i++){
			if((ta == fld[j][i]) != (tb == fld[k][i]))
				return 0;
			ta = fld[j][i];
			tb = fld[k][i];
		}
		return 1;
	}
}

int main(){
	int t,deg,hi,num,max;
	int i,j,k,temp;
	int fld[200][50]={0},MS[3]={0};
	
	FILE *fp;
	if((fp = fopen("input4.txt","r")) == NULL){
		printf("Error when opening file");
		exit(1);
	}
	
	fscanf(fp," %d",&t);
	while(t != 0){
		fscanf(fp," %d %d %d",&deg,&hi,&num);
		for(j=0;j<num;j++){
			fscanf(fp," %d",&temp);
			k= (temp+((deg+1)/2)-1)/deg > 0 ? (temp+((deg+1)/2)-1)/deg : 0;
			for(i=1;i<10;i++){
				if(fld[k][i] == 0 ){
					fld[k][i] = temp;
					fld[k][0]++;
					break;
				}
			}
		}
		max=0;
		for(i=0;i<hi;i++){
			max = deg*max+1;
		}
		for(i=max;i>1;i--){
			for(j=1;j<=fld[i][0];j++){
				temp=(fld[i][0])+1;
				for(k=1;k<=fld[fld[i][j]][0];k++){
					if(fld[fld[i][j]][k] != 0){
						fld[i][temp] = fld[fld[i][j]][k];
						temp++;
						fld[i][0]++;
					}
				}
			}
		}
		for(i=max;i>1;i--){
			for(j=1;j<=fld[i][0];j++){
				fld[i][j] = (fld[i][j]+deg-2)/deg;
			}
		}
		
		for(j=2;j<max-1;j++){
			for(k=j+1;k<max;k++){
				if(fld[j][0]==0)
					break;
				if(fld[k][0]==0)
					continue;
				if(fld[j][0]==fld[k][0]){
					if(same(fld, j, k, deg, max)){
						if((fld[j][0]+1)>MS[2]){
							MS[0] = j;
							MS[1] = k;
							MS[2] = fld[j][0]+1;
						}
					}
				}
			}
		}
		printf("%d %d\n",MS[0],MS[1]);
		memset(fld,0,sizeof(fld));
		memset(MS,0,sizeof(MS));
		t--;
	}
	fclose(fp);
	return 0;
}
