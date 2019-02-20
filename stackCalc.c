#include<stdio.h>
#include<stdlib.h>
#include<float.h>

double plus(double x, double y) {return x+y;}
double minus(double x, double y) {return x-y;}
double mult(double x, double y) {return x*y;}
double Div(double x, double y) {return x/y;}
double Mod(double x, double y) {return (int)x%(int)y;}
double error(double x, double y) {
  fprintf(stderr,"ERROR! The only valid operators are + - * / %%\n");
  return 0;
}

double (*f[])()={plus, minus, mult, Div, Mod, error}; //Array of pointers on functions

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
//int d_CLifo(SLifo *p);

int main(){
  SLifo myCalcStack;
	int n; 
  double d=0;
  char szString[100], *p;

  int aF[256]; // array of functions
  for (int i=0;i<256;aF[i++]=5);
  aF['+']=0; aF['-']=1; aF['*']=2; aF['/']=3; aF['%']=4;


  printf("Enter a stack size: ");scanf("%d",&n);
  if (CLifo(&myCalcStack,n)){
    fprintf(stderr,"Error creating the stack\n");
    return 1;
  }
  
  printf("Push numbers or operators (end with q)\n");
  while (1){
    scanf("%s",szString);
    d=strtod(szString, &p); printf("%c\n",*p);
    if (p!=szString){ // if szString is a number, p points to the rest
      CLifo_push(&myCalcStack, d);printf("%lf\n",myCalcStack.pValueStack[myCalcStack.iTop]);}// of the string (=after the number)
    else {          // it is not a string, but an operator, or 'q'
      if (szString[0]=='q') break; // Stop!
      CLifo_push(&myCalcStack, // push the calculation on the stack
                (*f[aF[szString[0]]])(CLifo_pop(&myCalcStack),
                                      CLifo_pop(&myCalcStack)));

		printf("The Top now is %lf \n",myCalcStack.pValueStack[myCalcStack.iTop]);
    }
  }

//  d_CLifo(&myCalcStack);

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
		p->pValueStack[++p->iTop]=n;//p->pValueStack[++p->iTop]=n;
		return 1;	
	}//end else
}
//----------------------------------------------------------------------------------------------
double CLifo_pop(SLifo *p){
	if(CLifo_isEmpty(p))	return DBL_MAX;
	else{ 
	//	if (p->nSize-p->iTop>=3) p->nSize-=3;
		return p->pValueStack[p->iTop--];
	}
}
//----------------------------------------------------------------------------------------------
int CLifo_print(SLifo *p){
	if(CLifo_isEmpty(p))	{printf("Stack is EMPTY!!! \n"); return 0;}
	for(int i=0;i<=p->iTop;i++) printf("%lf\t",p->pValueStack[i]);
}
//----------------------------------------------------------------------------------------------
/*int d_CLifo(SLifo *p){
	free(p->pValueStack);
	free(p);
	return 0;
}*/



