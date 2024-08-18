#include <stdio.h>
#include <stdlib.h>
#include <String.h>
int times;
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
void Rotate(TreeNodePtr *treePtr){
	int l, r;
	if(*treePtr == NULL){
	}else{
		Rotate(&((*treePtr)->leftPtr));
		Rotate(&((*treePtr)->rightPtr));
		l = HeightT((*treePtr)->leftPtr);
		r = HeightT((*treePtr)->rightPtr);
		if( l >= r ){
			if(l-r >= 2){
				if((r == 0 && ((*treePtr)->leftPtr)->leftPtr != NULL) || HeightT(((*treePtr)->leftPtr)->leftPtr) > 1){
					*treePtr = R(*treePtr);
					times++;
				}else{
					//printf("i");
					*treePtr = LR(*treePtr);
					times++;
				}
			}
		}else{
			if(r-l >= 2){
				if((l == 0 && ((*treePtr)->rightPtr)->rightPtr != NULL) || HeightT(((*treePtr)->rightPtr)->rightPtr) > 1){
					*treePtr = L(*treePtr);
					times++;
				}else{
					*treePtr = RL(*treePtr);
					times++;
				}
			}
		}
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
		if( value <= (*treePtr)->data ){
			insertNode(&((*treePtr)->leftPtr),value);
		}else if( value > (*treePtr)->data ){
			insertNode(&((*treePtr)->rightPtr),value);
		}
	}
}
TreeNodePtr clone(TreeNodePtr treePtr){
    if(treePtr == NULL){
		return NULL;
	}
    TreeNodePtr temp = malloc(sizeof(TreeNode));	
    if(temp != NULL){
		temp->data = treePtr->data;
 		temp->leftPtr = clone(treePtr->leftPtr);
    	temp->rightPtr = clone(treePtr->rightPtr);
	}
	return temp;
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
int PH(TreeNodePtr treePtr,int max){
	int now = 1,TR=0;
	if(max==0){
		return 0;
	}
	if(HeightT(treePtr)==max){
		if(HeightT(treePtr->leftPtr)==max-1){
			printf("%d ",treePtr->data);
			PH(treePtr->leftPtr,max-1);
			if(max == 2){
				treePtr->leftPtr = NULL;
				printf("\n");
			}
		}else if(HeightT(treePtr->rightPtr)==max-1){
			printf("%d ",treePtr->data);
			PH(treePtr->rightPtr,max-1);
			if(max == 2){
				treePtr->rightPtr = NULL;
				printf("\n");
			}
		}
	}
	return 0;
}
int main(){
	int height, tre, node , task[1000];
	int i,j,in,time = 0,rt;
	char num[10],temp ,ctask[1000]={};
	TreeNodePtr T,A;
	int ival[100]={0};
	FILE *fp;
	if ((fp = fopen("input3.txt","r"))== NULL){//TestFile ("filename", mode)
        printf("Error when opening file");
        exit(1);
    }
	while(time<1){
		fgets( ctask, 1000, fp);
		T = NULL;
		A = NULL;
		memset(num ,0,sizeof(num));
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
			times = 0;
			A = clone(T);
			insertNode(&T, task[j]);
			insertNode(&A, task[j]);
			Rotate(&A);
			rt = times;
			node = HeightT(A);
			printf("%d %d\n",task[j],rt);
			if(j == in-1){
				while(HeightT(A) == node){
					PH(A,node);
				}
			}
			AllNode(A);
			
		}
		
		
		//node = AllNode(T);
		//printf(" %d\n",node);
		time++;
	}
	return 0;
} 
