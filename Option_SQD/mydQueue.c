#include "mydQueue.h"

extern SQD* dFront;
extern SQD* dRear;

SQD* create_D(){
	SQD* N;

	N=(SQD*)malloc(sizeof(SQD));
	N->data = 0;
	N->link1 = NULL;
	N->link2 = NULL;

	return N;
}

void enque_D(int data,int course){
	SQD* N;
	N=create_D();
	N->data=data;

	if(isempty_D()){
		dFront->link1=N;
		dRear->link1=N;
	}
	else{
		SQD* P;
		if(course == 1){
			P=dFront->link1;
			P->link1=N;
			N->link2=P;
			dFront->link1=N;
		}
		else if(course == 2){
			P=dRear->link1;
			P->link2=N;
			N->link1=P;
			dRear->link1=N;
		}
	}
}

int deque_D(int course){
	int data = -1;

	if(!isempty_D()){
		SQD* P;
		if(course == 1){
			P=dFront->link1;
			data = P->data;
			dFront->link1=P->link2;
		}
		else if(course == 2){
			P=dRear->link1;
			data = P->data;
			dRear->link1=P->link1;
		}
		if(dFront->link1 == NULL || dRear->link1 == NULL){
			dFront->link1 = NULL;
			dRear->link1 = NULL;
		}
		free(P);
	}

	return data;
}

int isempty_D(){
	return (dFront->link1 == NULL)?1:0;
}

