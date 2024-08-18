#include<stdio.h>
#include<stdlib.h>
#include <String.h>
int su[20];
struct treeNode{
	struct treeNode *leftPtr;
	int data;
	struct treeNode *rightPtr;
};
typedef struct treeNode TreeNode;
typedef TreeNode *TreeNodePtr;

void findsum(TreeNodePtr treePtr, int last, int now){
	int i;
	if(treePtr !=NULL){
		su[now] = treePtr->data;
		findsum(treePtr->leftPtr , last - treePtr->data,now+1);
		if((treePtr->leftPtr != NULL) || (treePtr->rightPtr != NULL)){	
			findsum(treePtr->rightPtr , last - treePtr->data,now+1);
		}
	}else{
		if(last == 0){
			for(i=0;i<now;i++){
				printf("%d ",su[i]);
			}
			printf("\n");
		}
	}
}

void post(TreeNodePtr treePtr,int sum){
	if(treePtr !=NULL){
		post(treePtr->leftPtr,sum);
		findsum(treePtr->leftPtr , sum,0);
		post(treePtr->rightPtr,sum);
		findsum(treePtr->rightPtr , sum,0);
	}
}

void insertNode(TreeNodePtr *treePtr, int value){
	int l,r;
	if(*treePtr == NULL){
		*treePtr = malloc(sizeof(TreeNode));
		if(*treePtr != NULL){
			(*treePtr)->data = value;
			(*treePtr)->leftPtr = NULL;
			(*treePtr)->rightPtr = NULL;
		}
	}else{
		if( value < (*treePtr)->data ){
			insertNode(&((*treePtr)->leftPtr),value);
		}else if( value > (*treePtr)->data ){
			insertNode(&((*treePtr)->rightPtr),value);
		}
	}
}

int main(){
	int sum,i,j,k,temp;
	char c[1000]={},num[11];
	TreeNodePtr Tr;
	
	FILE *fp;
	if ((fp = fopen("input2.txt","r"))== NULL){//TestFile ("filename", mode)
        printf("Error when opening file");
        exit(1);
    }
    
    while(fscanf(fp, "%d ",&sum) != EOF){
		fgets( c, 1000, fp);
		Tr = NULL;
		memset(num ,0,sizeof(num));
		i = 0;
		j = 0;
		while(c[i] != '\n'){
			if(c[i] == '\0')
				break;	
			if(c[i] == ' '||c[i] == '\0'){
				temp = atoi(num);
				insertNode(&Tr, temp);
				memset(num ,0,sizeof(num));
				j++;
			}else if(c[i] >= '0' && c[i] <= '9'){
				num[strlen(num)] = c[i];
			}
			i++;
		}
		temp = atoi(num);
		insertNode(&Tr, temp);
		memset(num ,0,sizeof(num));
		
		findsum(Tr,sum,0);	
    	post(Tr,sum);
    	
    	printf("\n");
    }
	fclose(fp);
    return 0;
}
