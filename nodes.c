#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int nVal;
  struct Node *pNext;
} SNode;

int LL_sorted_add(SNode **ppList,int n);
int LL_add(SNode **ppList,int n);
int LL_del(SNode **ppList,int n);
int LL_Print(SNode *pList);
int LL_Destructor(SNode **ppList);
int LL_sort(SNode **ppList);
int LL_sorted_add(SNode **ppList,int n){
  SNode *pSent, *pCur;
  pSent=pCur=*ppList;
  while((pCur)&&(pCur->nVal < n)){
    pSent=pCur;
    pCur=pCur->pNext;
  }
  if (pSent==pCur){
    *ppList=(SNode*)malloc(sizeof(SNode)); 
    (*ppList)->nVal=n;
    (*ppList)->pNext=pCur;
  } else{
  pSent->pNext=(SNode*)malloc(sizeof(SNode)); 
  (pSent->pNext)->nVal=n;
  (pSent->pNext)->pNext=pCur;
  }
  return 0;
}


int LL_RecursiveDestructor(SNode **ppList){
  if(*ppList){
    LL_RecursiveDestructor(&((*ppList)->pNext));
    printf("removing [%d], ",(*ppList)->nVal); 
    free(*ppList);
    *ppList=NULL;
  }
  printf("\b\b\n"); 
  return 0;
}

int LL_Destructor(SNode **ppList){
  while(*ppList){
    SNode *pTemp=(*ppList)->pNext;
    printf("removing [%d], ",(*ppList)->nVal); 
    free(*ppList);
    *ppList=pTemp;
  }
  printf("\b\b\n"); 
  return 0;
}

int LL_del(SNode **ppList,int n){
  SNode *pSent, *pCur;
  pSent=pCur=*ppList;
  while((pCur)&&(pCur->nVal!=n)){
    pSent=pCur;
    pCur=pCur->pNext;
    if (pCur==NULL) break; 
  }
  if (pCur){
    if (pCur==*ppList) *ppList=pCur->pNext;
    else pSent->pNext=pCur->pNext;
    free(pCur);
    return 0;
  } else return 1;
}

int LL_add(SNode **ppList,int n){
  SNode *pTemp = *ppList; 
  *ppList=(SNode *) malloc(sizeof(SNode));
  (*ppList)->pNext=pTemp;
  (*ppList)->nVal=n;
  return 0;
}

int LL_Print(SNode *pList){
  if (pList==NULL) {
    printf("pList-/\n");
    return 1;
  }
  printf("pList->[%d]->",pList->nVal);
  while(pList->pNext){
    pList=pList->pNext;
    printf("[%d]->",pList->nVal);
  }
  printf("\b/\n");
  return 0;
}

int LL_RPrint(SNode *pList){
  if (pList){
    printf("[%d]->",pList->nVal);
    LL_RPrint(pList->pNext);
  }
  printf("\n");
  return 0;
}

int LL_RBPrint(SNode *pList){
  if (pList){
    LL_RBPrint(pList->pNext);
    printf("[%d]->",pList->nVal);
  }
  printf("\n");
  return 0;
}

int LL_sort(SNode **ppList){
	SNode *j=*ppList,*i;int temp=0;
	for(j;j!=NULL;j=j->pNext){
		for(i=j->pNext;i!=NULL;i=i->pNext){
			if(j->nVal > i->nVal){
				temp=j->nVal;
				j->nVal=i->nVal;
				i->nVal=temp;
			}	
		}
	}
	return 1;
}

int main(){
  SNode *pList=NULL;
  int n;
  char cAction;
  LL_add(&pList,  3);LL_add(&pList, 32);
  LL_add(&pList, 11);LL_add(&pList, 33);
  LL_add(&pList, 10);LL_add(&pList,  2);
  LL_add(&pList, 40);LL_add(&pList, 23);
	LL_Print(pList);
	LL_sort(&pList);
	LL_Print(pList);
/*
  do{
    printf("(a)dd, (S)ort an array, (s)orted_add, (d)elete, (D)estruct, (R)ecursivelyDestruct, (q)uit, (p)rint recursively, (P)rint backwards : ");scanf(" %c",&cAction);
    if (cAction=='a'){
      printf("Enter a number to add to the list: ");scanf(" %d",&n);
      LL_add(&pList, n);
      if (pList==NULL) printf("pList = NULL!!\n");
      LL_Print(pList);
    }
    if (cAction=='s'){
      printf("Sorted adding of a number to the list: ");scanf(" %d",&n);
      LL_sorted_add(&pList, n);
      if (pList==NULL) printf("pList = NULL!!\n");
      LL_Print(pList);
    } else if (cAction=='d'){
      printf("Enter a number to remove from the list:");scanf(" %d",&n);
      if(LL_del(&pList, n)) fprintf(stderr,"Error: %d was not in the list\n",n);
      LL_Print(pList);
    } else if (cAction=='R'){
      LL_RecursiveDestructor(&pList);
    } else if (cAction=='D'){
      LL_Destructor(&pList);
    } else if (cAction=='S'){
		  LL_sort(&pList);
    } else if (cAction=='p'){
      LL_RPrint(pList);
    } else if (cAction=='P'){
      LL_RBPrint(pList);
    }
  }while(cAction!='q');*/

  return 0;
}



