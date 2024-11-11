#include "myStack.h"

extern SQD* Top;

SQD* create_S(){
	SQD* N;

	N=(SQD*)malloc(sizeof(SQD));
	N->data = 0;
	N->link1 = NULL;
	N->link2 = NULL;

	return N;
}

void push(int data){
	SQD* N;

	N=create_S();
	N->data=data;
	N->link1=Top->link1;
	Top->link1=N; 
}

int pop(){
	int data = -1;

	if(!isempty_S()){
		SQD* P;
		P=Top->link1;
		data=P->data; 		
		Top->link1=P->link1;
		free(P);
	}

	return data;
}

int isempty_S(){
	return (Top->link1 == NULL)?1:0;
}
