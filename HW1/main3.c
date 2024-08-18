//HW1_3_4110056015
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 2147483647 
int armap[15][15] = {0};
typedef struct {
	short int row;
	short int col;
	short int dir;
} element;
element stack[230];

typedef struct {
short int vert;
short int horiz;
} offsets;
offsets move[8];

void inidir(){
	move[0].horiz=0;
	move[0].vert=-1;
	move[1].horiz=1;
	move[1].vert=-1;
	move[2].horiz=1;
	move[2].vert=0;
	move[3].horiz=1;
	move[3].vert=1;
	move[4].horiz=0;
	move[4].vert=1;
	move[5].horiz=-1;
	move[5].vert=1;
	move[6].horiz=-1;
	move[6].vert=0;
	move[7].horiz=-1;
	move[7].vert=-1;
}

int main(){
	int map, sol = 0; 
	int szr = 0,szc = 0; //size_row size_col
	int i = 0, j = 0, k = 0;
	char num[15]={""};
	
	FILE *fp;
	if((fp = fopen("input3.txt","r")) == NULL){ //TestFile ("filename", mode)
		printf("Error when opening file");
		exit(1);
	}
	
	fscanf(fp," %d",&map);//map amount
	inidir();//initial direction
	
	for(i = 1; i <= map; i++){ 
		fscanf(fp,"%d %d \n",&szr,&szc); //Scan map size
		for(j = 0; j < szr; j++){
			for(k = 0; k < szc; k++){
				fscanf(fp,"%s",&num);
				if(!strcmp(num,"e")){
					armap[j][k] = MAX;
				}else if(!strcmp(num,"s")){
					armap[j][k] = -1;
					stack[0].row = j;
					stack[0].col = k;
				}else {
					armap[j][k] = atoi(num);
				}
			}
		}
		sol = path(0,szr,szc);//all solutions in map
		
		printf("第%d張圖的可走路線共:%d種\n",i,sol);
		sol = 0;
	}
	
	fclose(fp);
	return(0);
}

int path(int top,int maxrow,int maxcol){
	int i,j = top,paths = 0;
	int row = stack[j].row;
	int col = stack[j].col;
	
	if(armap[row][col] == MAX){
		return (1);
	}
	
	for(i = 0; i < 8; i++){	
		if(row+move[i].vert<0||row+move[i].vert>=maxrow||col+move[i].horiz<0||col+move[i].horiz>=maxcol){
			continue;
		}
		if(armap[row][col] < armap[row+move[i].vert][col+move[i].horiz]){
			stack[j+1].row=row+move[i].vert;
			stack[j+1].col=col+move[i].horiz;
			paths += path(j+1,maxrow,maxcol); 
		}
	}
	return (paths);
}
