#include "myQueue.h"

extern SQD* Front;
extern SQD* Rear;

SQD* create_Q(){
	SQD* N;

	N=(SQD*)malloc(sizeof(SQD));
	N->data = 0;
	N->link1 = NULL;
	N->link2 = NULL;

	return N;
}

void enque(int data){
	SQD* N;
	N=create_Q();
	N->data=data;
	if(Front->link1==NULL && Rear->link1==NULL){
		Front->link1 = N;
		Rear->link1 = N;	
	}
	else{
		SQD* P;
		P=Rear->link1;
		P->link1=N;
		Rear->link1=N;
	} 	
}

int deque(){
	int data = -1;

	if(!isempty_Q()){
		SQD* P;
		P=Front->link1;
		data = P->data;

		Front->link1=P->link1;
		if(isempty_Q()){
			Rear->link1=NULL;			
		}
		free(P);
	}
	
	return data;
}

int isempty_Q(){
	return (Front->link1 == NULL)?1:0;
}

