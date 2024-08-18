//HW1_4_4110056015
#include<stdio.h>
#include<stdlib.h>
#include<Math.h>
int arpic[100][100] = {0};
short int been[100][100] = {0};
int ArMax = 0;

typedef struct {
	short int row;
	short int col;
	short int dir;
} element;
element stack[10000];

typedef struct {
short int vert;
short int horiz;
} offsets;
offsets move[4];

void inidir(){
	move[0].horiz=0;
	move[0].vert=-1;
	move[1].horiz=1;
	move[1].vert=0;
	move[2].horiz=0;
	move[2].vert=1;
	move[3].horiz=-1;
	move[3].vert=0;
}

int main(){
	int pic, mis = 0, sum = 0, szr = 0,szc = 0;
	int i = 0, j = 0, k = 0, tmp;
	
	FILE *fp;
	if((fp = fopen("input4.txt","r")) == NULL){ //TestFile ("filename", mode)
		printf("Error when opening file");
		exit(1);
	}
	fscanf(fp," %d",&pic);
	inidir();
	
	for(i = 1;i <= pic; i++){
		fscanf(fp,"%d %d %d ",&szr,&szc,&mis);
		for(j=0;j<szr;j++){
			for(k=0;k<szc;k++){
				fscanf(fp," %d",&arpic[j][k]);
				been[j][k]=0;
			}
		}
		sum = Mount(szr,szc,mis);
		printf("第%d張圖，山的數量 = %d，最大山面積 = %d\n",i,sum,ArMax);	
		sum = 0;
	}
	
	fclose(fp);
	return(0);
}

int Mount(int maxrow, int maxcol, int mis){
	int i, j, sum = 0, max = 0, tmp;
	for(i = 0; i < maxrow ; i++){
		for(j = 0; j < maxcol; j++){
			if(been[i][j] == 1)
				continue;
			stack[0].row = i;
			stack[0].col = j;
			if(max < (tmp = Area(0,maxrow,maxcol,mis))){
				max = tmp;
			}
			sum++;
		}
	}
	ArMax = max;
	return(sum);
}

int Area(int top,int maxrow,int maxcol,int mis){
	int i, j = top, areas = 0;
	int row = stack[j].row;
	int col = stack[j].col;
	
	for(i = 0; i < 4; i++){	
		if(row+move[i].vert<0||row+move[i].vert>=maxrow||col+move[i].horiz<0||col+move[i].horiz>=maxcol)
			continue;
		if(been[row+move[i].vert][col+move[i].horiz]==1)
			continue;
		if(abs(arpic[row][col] - arpic[row+move[i].vert][col+move[i].horiz]) <= mis){
			been[row][col] = 1;
			stack[j+1].row = row+move[i].vert;
			stack[j+1].col = col+move[i].horiz;
			areas += Area(j+1,maxrow,maxcol,mis);
		}
	}
	been[row][col] = 1;
	areas++;
	return (areas);
}
