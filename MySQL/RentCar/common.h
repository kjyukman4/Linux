#ifndef __COMMON__
#define __COMMON__
#include <stdio.h>
#include <stdlib.h>

typedef struct car{
	char number[20];
	char kind[20];
	char year[20];
	char fuel[20];
	int peopleNum;
	int mileage;
	int fuelamount;
	int fuelefficiency;
	int state;
	int price;
}CAR;

typedef struct customer{
	char ID[20];
	char phone[14];
	char name[10];
	int age;
	int history;
	int score;
}CUST;

typedef struct rent{
	char ID[20];
	char number[20];
	char phone[14];
	char start[30];
	char end[30];
	int use_mileage;
	char destination[30];
	int price;
}RENT;

#endif
