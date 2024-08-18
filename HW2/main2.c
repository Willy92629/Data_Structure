#include <stdio.h>
#include <stdlib.h>
#include <String.h>
int lhei,rhei;
struct treeNode{
	struct treeNode *leftPtr;
	int data;
	struct treeNode *rightPtr;
};
typedef struct treeNode TreeNode;
typedef TreeNode *TreeNodePtr;

void post(TreeNodePtr treePtr){
	if(treePtr !=NULL){
		post(treePtr->leftPtr);
		post(treePtr->rightPtr);
		printf("%3d",treePtr->data);
	}
}

TreeNodePtr L(TreeNodePtr treePtr){
	TreeNodePtr temp;
	temp = (treePtr->rightPtr);
	(treePtr->rightPtr) = temp->leftPtr;
	temp->leftPtr = treePtr;
	return temp;
}
TreeNodePtr R(TreeNodePtr treePtr){
	TreeNodePtr temp;
	temp = (treePtr->leftPtr);
	(treePtr->leftPtr) = temp->rightPtr;
	temp->rightPtr = treePtr;
	return temp;
}
TreeNodePtr LR(TreeNodePtr treePtr){
	treePtr->leftPtr = L(treePtr->leftPtr) ;
	return R(treePtr);
}
TreeNodePtr RL(TreeNodePtr treePtr){
	treePtr->rightPtr = R(treePtr->rightPtr) ;
	return L(treePtr);
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
			l = HeightT((*treePtr)->leftPtr);
			r = HeightT((*treePtr)->rightPtr);
			if(l-r >= 2){
				if(((*treePtr)->leftPtr)->data > value){
					*treePtr = R(*treePtr);
				}else{
					*treePtr = LR(*treePtr);
				}
			}
		}else if( value > (*treePtr)->data ){
			insertNode(&((*treePtr)->rightPtr),value);
			l = HeightT((*treePtr)->leftPtr);
			r = HeightT((*treePtr)->rightPtr);
			if(r-l >= 2){
				if(((*treePtr)->rightPtr)->data < value){
					*treePtr = L(*treePtr);
				}else{
					*treePtr = RL(*treePtr);
				}
			}
		}
	}
}

int AllNode(TreeNodePtr treePtr){
	int l, r;
	if(treePtr == NULL){
		return 0;
	}else{
		l = AllNode((treePtr)->leftPtr);
		r = AllNode((treePtr)->rightPtr);
		free(treePtr);
		return  (l+r+1);
	}
}

int HeightT(TreeNodePtr treePtr){
	int l,r;
	if(treePtr == NULL){
		return 0;
	}else{
		l = HeightT((treePtr)->leftPtr);
		r = HeightT((treePtr)->rightPtr);
		return (l > r) ? l+1 : r+1;
	}
}

int main(){
	int height, tre, node , task[1000],AT=1;
	int i,j,k,in,rt;
	char num[10],temp ,ctask[1000]={};
	TreeNodePtr HP[100];
	int ival[100]={0};
	FILE *fp;
	if ((fp = fopen("input2.txt","r"))== NULL){//TestFile ("filename", mode)
        printf("Error when opening file");
        exit(1);
    }
	
	while(fscanf(fp, "%d %d ",&height,&tre) != EOF){
		fgets( ctask, 1000, fp);
		for(i=0;i<100;i++){
			HP[i] = NULL;
			ival[i] = 0;
		}
		memset(num ,0,sizeof(num));
		AT = 1;
		i = 0;
		j = 0;
		while(ctask[i] != '\n'){
			if(ctask[i] == NULL)
				break;	
			if(ctask[i] == ' '||ctask[i] == NULL){
				task[j] = atoi(num);
				memset(num ,0,sizeof(num));
				j++;
			}else if(ctask[i] >= '0' && ctask[i] <= '9'){
				num[strlen(num)] = ctask[i];
			}
			i++;
			in = j;
		}
		task[j] = atoi(num);
		memset(num ,0,sizeof(num));
		in++;
		
		for(j=0;j < in ;j++){
			
			for(i=0;i < AT;i++){
				if(task[j] <= ival[i]){
					insertNode(&HP[i], task[j]);
					break;
				}else if(ival[i] == 0){
					insertNode(&HP[i], task[j]);
					break;
				}
			}
			if(HeightT(HP[i]) > height){
				for(k=AT;k > i;k--){
					HP[k] = HP[k-1];
					ival[k] = ival[k-1];
				}
				HP[i+1] = (HP[i])->rightPtr;
				ival[i] = HP[i]->data;
				rt = HP[i]->data;
				HP[i] = (HP[i])->leftPtr;
				insertNode(&HP[i], rt);
				AT++;
			}
		}
		node = AllNode(HP[tre-1]);
		printf("%d\n",node);
	}
	return 0;
} 
