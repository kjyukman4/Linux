#ifndef __CAR__
#define __CAR__
#include "DBfunction.h"
#include <stdio_ext.h>

void Car_Main();
int car_menu();
void Car_Insert();
void Car_Delete(MYSQL* , char* );
void Car_Update(MYSQL* , char* );
void Car_Select(MYSQL* , char* );

#endif

