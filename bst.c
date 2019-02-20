/*************************************/
/*******BINARY SEARCH TREE************/
/*************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define COUNT 8
#define DIGITS 1

typedef struct Node{   
int val;
struct Node *left, *right;
}BSNode;

BSNode *constructTree(int n);
BSNode *add(BSNode *pTree, int n);
void treePrinter(BSNode *pTree){printf("%d \t", pTree->val);}
void treeTraverseA(BSNode *pTree);
void treeTraverseD(BSNode *pTree);
int treeNodeNumber(BSNode *pTree, int *d);
int treeDepth(BSNode *pTree, int d);
void treePrintLevel(BSNode *pTree, int level);
void treePrintLevels(BSNode *root, int *d);
int BSearch(BSNode *pTree, int n);
int treeDepth_1(BSNode *pTree);
int treeDepth(BSNode *pTree, int d);
int getBalance(BSNode *pTree);
BSNode* rightRot(BSNode *pTree);
BSNode* leftRot(BSNode *pTree);
void treePrint(BSNode *pTree, int *d);
void treePrintL(BSNode *pTree, int depth, int level, int cl);
void branches(int depth, int level);
void spaces(int depth, int level, int op);

int main(){
BSNode *BStree=NULL;
int d=0, s;
int x=17;
//Add Nodes
int tab[]={3,4,5,1,2,6,7,8};
for (int i=0;i<8;i++) BStree=add(BStree, tab[i]);
int depth=treeDepth(BStree,d);

//treeTraverseA(BStree);
//printf("\n");

printf("%d\n",treeDepth(BStree->right,d));
treePrint(BStree,&depth);
//getBalance(BStree);

BStree=leftRot(BStree);
treePrint(BStree,&depth);
//getBalance(BStree);

BStree=rightRot(BStree);
treePrint(BStree,&depth);
//getBalance(BStree);



/*treeTraverseD(BStree);
printf("\n");
int numb=0;
printf("%d\n",treeNodeNumber(BStree,&numb));

printf("Search for a value into the tree:\n");
printf("Give us the value :\t"); scanf("%d",&s);
printf("------> Searching \n");
if(BSearch(BStree, s)) printf("FOUND ..%d\n",BSearch(BStree,s));
else printf("This value %d DON'T exist in the tree.\n",s);
*/
return 0;
}
//-----------------------------------------------------------------------
BSNode *constructTree(int n){
	BSNode *pTree=(BSNode *)malloc(sizeof(BSNode));
	pTree->left=NULL;  pTree->val=n;  pTree->right=NULL;
	return pTree;
}
//-----------------------------------------------------------------------
BSNode *add(BSNode *pTree,int n){
	if(pTree==NULL) pTree=constructTree(n);
	if(pTree->val>n) pTree->left=add(pTree->left,n);
	else if(pTree->val<n) pTree->right=add(pTree->right,n);
	return pTree;
}//-----------------------------------------------------------------------
void treeTraverseA(BSNode *pTree){
	if(pTree!=NULL){
		treeTraverseA(pTree->right);
		printf("%d\t",pTree->val);
		treeTraverseA(pTree->left);
	}//end if
}
//-----------------------------------------------------------------------
void treeTraverseD(BSNode *pTree){
	if(pTree!=NULL){
		treeTraverseD(pTree->left);
		printf("%d\t",pTree->val);
		treeTraverseD(pTree->right);	
	}//end if
}
//-----------------------------------------------------------------------
int treeNodeNumber(BSNode *pTree, int *d){
		if(pTree!=NULL){
	treeNodeNumber(pTree->left,d);
		*d++;
	treeNodeNumber(pTree->right,d);
	}
	return *d;
}
//-----------------------------------------------------------------------
int BSearch(BSNode *pTree, int n){
	if(pTree!=NULL){	
		if(n>pTree->val)
			BSearch(pTree->right,n);
		else if(n<pTree->val)
			BSearch(pTree->left,n);
		else if (n==pTree->val)
			return n;	
	}
	else  return 0;
}
//-----------------------------------------------------------------------

int lev=0;
void treePrintLevel(BSNode *pTree, int level){
	if(pTree!=NULL){
		if(level==1)	printf("%5d",pTree->val);
		else if(level>1){
			treePrintLevel(pTree->left,level-1);
			treePrintLevel(pTree->right,level-1);
		}
	}
}

//-----------------------------------------------------------------------

void treePrintLevels(BSNode *root, int *d){
	for(int i=0;i<*d+1;i++){
		treePrintLevel(root,i);
		printf("\n");
	}	
}
//-----------------------------------------------------------------------
int x=0;
int treeDepth(BSNode *pTree, int d){
	if(pTree!=NULL){
		d++;
		treeDepth(pTree->left,d);
		treeDepth(pTree->right,d);
		if(d>=x) x=d;
	}
	return x;
	}

//-----------------------------------------------------------------------

int treeDepth_1(BSNode *pTree){
	if(pTree!=NULL){ 
		int left=treeDepth_1(pTree->left);
		int right=treeDepth_1(pTree->right);

		if(left>right)	{
			//printf("The left is incremented, Now left = %d\n",left+1);	
			return left+1;		
		}
		else{
			//printf("The right is incremented, Now right = %d\n",right+1);	
			return right+1;			
		}			
	}
}
//-----------------------------------------------------------------------

int getBalance(BSNode *pTree){
	int i=treeDepth_1(pTree->left)-treeDepth_1(pTree->right);
	if(i<=1 && i>=-1){
		printf("%d  AVL balanced\n",i);
		return 1;
	}
	else{
		printf("Not AVL balanced\n");
		return i;
	}
}

BSNode* rightRot(BSNode *pTree){
	BSNode *pTemp;
	pTemp=(pTree);	
	(pTree)=pTree->left;
	pTemp->left=pTree->right;
	pTree->right=pTemp;
	return (pTree);
}
	
BSNode* leftRot(BSNode *pTree){
	BSNode *pTemp;
	pTemp=(pTree);	
	(pTree)=pTree->right;
	pTemp->right=pTree->left;
	pTree->left=pTemp;
	return (pTree);
}

//PRINTING A TREE EVEN IF NOT BALANCED

//----------------------------------------------------------------------
void spaces(int depth, int level, int op){
     if(op==0) { //printf("d=%d,l=%d \n",depth,level);//spaces before we start printing numbers
     for(int i=0;i<(DIGITS)*(pow(2,depth-level)-1); i++) printf(" ");}
else if(op==1) { //printf("d=%d,l=%d \n",depth,level);//spaces between numbers
if(depth == level) {for(int i=0;i<(DIGITS)*(pow(2,depth-level)); i++) printf(" ");}
else {for(int i=0;i<2*(DIGITS)*(pow(2,depth-level)-1)+DIGITS; i++) printf(" ");}}
else if(op==2) { //spaces for case of between branches
for(int i=0;i<(DIGITS)*(pow(2,depth-level)-1); i++) printf(" ");}
}
//----------------------------------------------------------------------
void branches(int depth, int level){
if (depth != level){
spaces(depth,level-1,0);
for (int i=0;i<pow(2,level);i++)
if (i%2==0) {printf("/"); spaces(depth,level,2);}
else {printf("\\"); spaces(depth,level,2);}
}}
//----------------------------------------------------------------------
void treePrintL(BSNode *pTree, int depth, int level, int cl){ //printing with spaces between numbers
if (pTree!=NULL){
if (level==1) {printf("%d",pTree->val); spaces(depth,cl,1);}
else if (level>1){
treePrintL(pTree->left, depth, level-1, cl);
treePrintL(pTree->right, depth, level-1, cl);
}}
else {//printing an empty space for numbers !
if (level==1) {printf("00"); spaces(depth,cl,1);}
}
}
//---------------------------------------------------------------------
void treePrint(BSNode *pTree, int *d){
for (int i=1;i<=*d;i++) {
spaces(*d,i,0);
treePrintL(pTree, *d, i, i); printf("\n");
//branches(*d,i);printf("\n");
}}

