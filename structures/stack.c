/*********************************/
/**** Intelligent -STACK     *****/
/*********************************/
#include<stdio.h>
#include<stdlib.h>
#include<float.h>
typedef struct Lifo {
  int iTop, nSize;
  double *pValueStack;
} SLifo;

int CLifo(SLifo *p, int s);
int CLifo_isFull(SLifo *p){ return p->iTop==p->nSize-1; }
int CLifo_isEmpty(SLifo *p){ return p->iTop==-1; }
int CLifo_getSize(SLifo *p){ return p->nSize; }
int CLifo_setSize(SLifo *p);
int CLifo_push(SLifo *p, double n);
double CLifo_pop(SLifo *p);
int CLifo_print(SLifo *p);
int d_CLifo(SLifo *p);//Destroy the Stack

int main(){
	SLifo *myStack;
	int s,c;
	double n;
	printf("Give the size of the stack: ");	scanf("%d",&s);
	if(CLifo(myStack, s)!=0) printf("Something is Wrong!");
	do{
		printf("Choice give 1) to push a value 2) pop 3) print all stack 4) quite\n Your choice:   ");
		scanf("%d",&c);
		switch(c){
		case 1: scanf("%lf",&n); CLifo_push(myStack,n); break;
		case 2: printf("%lf  ",CLifo_pop(myStack)); break;
		case 3: CLifo_print(myStack); break;
		case 4: return 1; break;
		}	
	}while(c !=4);
//	printf("%d\n",CLifo(myStack, s));
	return 0;
}

//----------------------------------------------------------------------------------------------
int CLifo(SLifo *p, int s){
	p->iTop=-1;
	p->nSize=s;	
	p->pValueStack=(double *)malloc(sizeof(double));
	return 0;
}
//----------------------------------------------------------------------------------------------
int CLifo_push(SLifo *p, double n){
	if (CLifo_isFull(p)) return -1;
	else{
		p->iTop++;
		p->pValueStack[p->iTop]=n;//p->pValueStack[++p->iTop]=n;
		return 1;	
	}//end else
}
//----------------------------------------------------------------------------------------------
double CLifo_pop(SLifo *p){
	if(CLifo_isEmpty(p))	return DBL_MAX;
	else{ 
		if (p->nSize-p->iTop>=3) p->nSize-=3;
		return p->pValueStack[p->iTop--];
	}
}
//----------------------------------------------------------------------------------------------
int CLifo_print(SLifo *p){
	if(CLifo_isEmpty(p))	{printf("Stack is EMPTY!!! \n"); return 0;}
	for(int i=0;i<=p->iTop;i++) printf("%lf\t",p->pValueStack[i]);
}
//----------------------------------------------------------------------------------------------
int d_CLifo(SLifo *p){
	free(p->pValueStack);
	free(p);
	return 0;
}










