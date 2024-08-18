#include <stdio.h> 
#include <stdlib.h>
#include <String.h>
struct graphNode{
	struct graphNode *chd[100];
	struct graphNode *prt[100];
	int deg;
	int numP;
	int data;
};
typedef struct graphNode GraphNode;
typedef GraphNode *GraphNodePtr;

void pre(GraphNodePtr graphPtr){
	int i;
	if(graphPtr !=NULL){
		printf("%3d",graphPtr->data);
		for (i=0;i<graphPtr->deg;i++){
			pre(graphPtr->chd[i]);
		}
	}
}

int Loop(int e, GraphNodePtr graphPtr){
	int num=0,i;
	for(i=0;i<graphPtr->deg;i++){
		if(ToB(e,graphPtr->chd[i])>0){
			num++;
		}
	}
	
	if(num>=2){
		return 1;
	}
	return 0;
}
int ToB(int e, GraphNodePtr graphPtr){
	int i;
	if(graphPtr != NULL){
		if(graphPtr->data == e){
			return 1;
		}
		for(i=0;i<graphPtr->deg;i++){
			return ToB(e,graphPtr->chd[i]);
		}
	}else{
		return 0;
	}
}
int savepath(int e,GraphNodePtr start,int array[]){
	int i,flag=0;
	if (start==NULL){
		return;
	}
	else if (start->data==e){
		return 1;
	}
	else{
		for (i=0;i<start->deg;i++){
			if (savepath(e,start->chd[i],array)==1)
			flag=1;
		}
		if (flag==1){
			for(i=1;i<=array[0];i++){
				if(array[i]==start->data){
					return 1;
				}
			}
			array[++array[0]]=start->data;
			return 1;
		}
		return 0;
	}
}

int main(){
	int lst[100][100]={0} ,follow[100],array[100], LF[100]={0}, LE[100]={0};//LF = Loop First LE= Loop End
	int r,t,i,j,k,l,m,n,temp,max[2];
	char com[50],a[10];
	GraphNodePtr L[100];
	
	FILE *fp;
	if ((fp = fopen("input3.txt","r"))== NULL){//TestFile ("filename", mode)
        printf("Error when opening file");
        exit(1);
    }
	
	while( !feof(fp) ){
		fscanf(fp,"%d\n",&t);
		for(i=0;i<100;i++){
			L[i] = malloc(sizeof(GraphNode));
			L[i]->data = i;
			L[i]->deg = 0;
			L[i]->numP = 0;
			for(j=0;j<100;j++){
				L[i]->chd[j] = NULL;
				L[i]->prt[j] = NULL;
			}
		}
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
		
		for(i=1;i<100;i++){
			for(j=1;j<100;j++){
				if(lst[i][j]==1){
					L[i]->prt[L[i]->numP] = L[j];
					L[i]->numP++;
					L[j]->chd[L[j]->deg] = L[i];
					L[j]->deg++;
					if(L[j]->deg >= 2){
						LF[(++LF[0])] = j;
					}
					if(L[i]->numP >= 2){
						LE[(++LE[0])] = i;
					}
				}
			}
		}
		//preorder
		follow[0] = 0;
		for(i=0;i<100;i++){
			if(lst[i][0]==0&&lst[0][i]!=0){
				follow[++follow [0]] = i;
			}
		}
		
		for(i=1;i<=LF[0];i++){
			for(j=1;j<=LE[0];j++){
				if(Loop(LE[j], L[LF[i]])==1){
					savepath(LE[j],L[LF[i]],array);
					temp = 0;
					for(k = 1;k <= array[0];k++){
						temp += array[k];
						for(n=1;n<=follow[0];n++){
							if(follow[n] == array[k]){
								r=n;
								break;
							}
						}
					}
					follow[n] = temp;
					for(k = 1;k <= array[0];k++){
						for(l = 0;l <L[array[k]]->deg;l++){
							r=0;
							for(n=1;n<=array[0];n++){
								if(L[array[k]]->chd[l]->data == n){
									r=1;
									break;
								}
							}
							for(n=0;n<L[temp]->deg;n++){
								if(L[temp]->chd[n]->data == L[array[k]]->chd[l]->data){
									r=1;
									break;
								}
							}
							if(r==1){
								continue;
							}
							L[temp]->chd[L[temp]->deg++] = L[array[k]]->chd[l];
							for(m=0;m<L[L[array[k]]->chd[l]->data]->numP;m++){
								if(L[L[array[k]]->chd[l]->data]->prt[m]->data == array[k]){
									L[L[array[k]]->chd[l]->data]->prt[m] = L[temp];
									break;
								}
							}
						}
						for(l = 0;l <L[array[k]]->numP;l++){
							r=0;
							for(n=1;n<=array[0];n++){
								if(L[array[k]]->prt[l]->data == n){
									r=1;
									break;
								}
							}
							for(n=0;n<L[temp]->numP;n++){
								if(L[temp]->prt[n]->data == L[array[k]]->prt[l]->data){
									r=1;
									break;
								}
							}
							if(r==1){
								continue;
							}
							L[temp]->prt[L[temp]->numP] = L[array[k]]->prt[l];
							L[temp]->numP++;
							for(m=0;m<L[L[array[k]]->prt[l]->data]->deg;m++){
								if(L[L[array[k]]->prt[l]->data]->chd[m]->data == array[k]){
									L[L[array[k]]->prt[l]->data]->chd[m] = L[temp];
									break;
								}
							}
						}
					}
					
					memset(array ,0,sizeof(array));
				}
			}
		}
		//preorder
		for(i=1;i<=follow[0];i++){
			pre(L[follow[i]]);
			printf(" 123456 ");
		}
		/*
		for(i = 1;i <= array[0];i++){
			printf("%d ",array[i]);
		}
		printf("\n");*/
		r = 0;
		memset(lst ,0,sizeof(lst));
		memset(array ,0,sizeof(array));
		memset(follow ,0,sizeof(follow));
	}
	return 0;
}
