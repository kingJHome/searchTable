#include <stdio.h>
#include "sstable.h"

void visitBiTree(BiTree *t);

int main(int argc,char *argv[]){
	BiTree *bt;
	NodeWithWeight rt = {NULL,0};

	CreateWeightList(&rt);
	CreateSOSTree(&bt, rt);
	visitBiTree(bt);
	printf("\n");
	
	return 0;
}

void visitBiTree(BiTree *t){
	if( t ){
		printf("%-5d", t->elem->data);
		visitBiTree(t->lchild);
		visitBiTree(t->rchild);
	}
}
