#ifndef __DBFUNCTION__
#define __DBFUNCTION__
#include "common.h"
#include <mysql.h>
#include <string.h>

MYSQL* DB_connect();
int DB_Insert(void* ,int );
int DB_Modify(int ,char* ,char*);
int DB_Delete(int , char*);
void DB_Select(char* ,char*);
int DB_Rows_Num(char* ,char*);
void print_error(MYSQL* ,char* ); 
void DB_Get_Value(char* ,char* ,char* ,char*);
#endif
