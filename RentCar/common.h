#ifndef __COMMON__
#define __COMMON__
#include <stdio.h>

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
}CAR;

typedef struct customer{
	char phone[13];
	char name[10];
	int age;
	int history;
	int score;
}CUST;

typedef struct rent{
	char number[20];
	char phone[13];
	char start[20];
	char end[20];
	int use_mileage;
	char destination[30];
}RENT;

#endif
