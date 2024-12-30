#include "DBfunction.h"

/*-------------------------------------------------
 MYSQL* DB_connect(): DB연결정보 반환 
-------------------------------------------------*/
MYSQL* DB_connect(){
	MYSQL* conn;

	// 연결 핸들러 초기화	
	conn = mysql_init(NULL);

	if(conn == NULL){
		print_error(conn,"mysql_init() 실패\n");
		return NULL;
	}

	if(mysql_real_connect(conn,"localhost","myuser","mySecret","myDB",3306,NULL,0)==NULL){
		print_error(conn,"mysql_real_connect() 실패\n");
		mysql_close(conn);
		return NULL;
	}
	return conn;
}

/*-------------------------------------------------
 int DB_Insert(void* 구조체,int 상태값):
 Car,Customer,Rent 테이블 삽입
 -return 0: 성공 -return 1: 실패
-------------------------------------------------*/
int DB_Insert(void* vp, int state){
	MYSQL* conn;
	int res = 0;
	char query[200];
	char age[4],history[4],peopleNum[2],mileage[10],fuelamount[10],fuelefficiency[10],use_mileage[30];

	conn = DB_connect();
	if(conn != NULL){ 	
		getchar();
		switch(state){
			case 0:
				CAR CAR_DATA;
				CAR_DATA = *(CAR*)vp;

				strcpy(query,"INSERT INTO Car (number, kind, year, fuel, peopleNum, mileage, fuelamount, fuelefficiency, state) VALUES ('");

				strcat(query,CAR_DATA.number);
				strcat(query,"','");

				strcat(query,CAR_DATA.kind);
				strcat(query,"','");
	
				strcat(query,CAR_DATA.year);
				strcat(query,"','");
	
				strcat(query,CAR_DATA.fuel);
				strcat(query,"','");

				sprintf(peopleNum,"%d",CAR_DATA.peopleNum);
				strcat(query,peopleNum);
				strcat(query,"','");

				sprintf(mileage,"%d",CAR_DATA.mileage);
				strcat(query,mileage);
				strcat(query,"','");

				sprintf(fuelamount,"%d",CAR_DATA.fuelamount);
				strcat(query,fuelamount);
				strcat(query,"','");

				sprintf(fuelefficiency,"%d",CAR_DATA.fuelefficiency);
				strcat(query,fuelefficiency);
				strcat(query,"','0');");
				break;
			case 1:
				CUST CUST_DATA;
				CUST_DATA = *(CUST*)vp;

				strcpy(query,"INSERT INTO Customer (phone, name, age, history, score) VALUES ('");

				strcat(query,CUST_DATA.phone);
				strcat(query,"','");

				strcat(query,CUST_DATA.name);
				strcat(query,"','");
				
				sprintf(age,"%d",CUST_DATA.age);
				strcat(query,age);
				strcat(query,"','");

				sprintf(history,"%d",CUST_DATA.history);
				strcat(query,history);
				strcat(query,"','0');");
				break;
			case 2:
				RENT RENT_DATA;
				RENT_DATA = *(RENT*)vp;

				strcpy(query,"INSERT INTO Rent (number, phone, start, end, use_mileage, destination) VALUES ('");

				strcat(query,RENT_DATA.number);
				strcat(query,"','");

				strcat(query,RENT_DATA.phone);
				strcat(query,"',");
	
				strcat(query,RENT_DATA.start);
				strcat(query,",");
	
				strcat(query,RENT_DATA.end);
				strcat(query,",'");

				sprintf(use_mileage,"%d",RENT_DATA.use_mileage);
				strcat(query,use_mileage);
				strcat(query,"','");

				strcat(query,RENT_DATA.destination);
				strcat(query,"');");
				printf("\n%s\n",query);
				break;
			default:
				break;
		}

		if(mysql_query(conn,query) != 0){
			print_error(conn,"mysql_query() 실패\n");
			res = 1;
		}
		// 연결정보해제
		mysql_close(conn);
	}
	return res;
}

/*-------------------------------------------------
 void DB_Select(char* 테이블 이름, char* 조건):
 행단위로 데이터 가져오기 
-------------------------------------------------*/
void DB_Select(char* Table_Name, char* conditions){
	MYSQL* conn; 
	MYSQL_RES* res_set;
	char query[200] = "";
	
	strcpy(query,"select * from ");
	strcat(query,Table_Name);
	strcat(query," ");
	strcat(query,conditions);
	strcat(query,";");


	conn = DB_connect();
	if(conn != NULL){
		if(mysql_query(conn,query) == 0){
			res_set = mysql_store_result(conn);

			if(res_set != NULL){
				MYSQL_ROW row;
				unsigned int i;

				while((row = mysql_fetch_row(res_set)) != NULL){
					for(i=0;i<mysql_num_fields(res_set);i++){
						printf("|%-15s",row[i] != NULL ? row[i] : "NULL");
					}
					printf("|\n");
				}

				if(mysql_errno(conn) != 0){
					print_error(conn,"mysql_fetch_row() 실패");
				}
				else{
					printf("행 개수 반환수: %lu\n",(unsigned long) mysql_num_rows(res_set));
				}
				mysql_free_result(res_set);
			}
			else{
				print_error(conn,"mysql_store_result() 실패\n");
			}
		}
		else{
			print_error(conn,"mysql_query() 실패\n");
		}
	}
	mysql_close(conn);
}

/*-------------------------------------------------
 int DB_Rows_Num(char* 테이블 이름, char* 조건):
 조건에 맞는 테이블 행수 반환  
 -return -1: 실패
-------------------------------------------------*/
int DB_Rows_Num(char* Table_Name, char* conditions){
	MYSQL* conn;
	MYSQL_RES* res_set;
	char query[200] = "";
	int num = -1;
	
	strcpy(query,"select * from ");
	strcat(query,Table_Name);
	strcat(query," ");
	strcat(query,conditions);
	strcat(query,";");

	conn = DB_connect();
	if(conn != NULL){
		if(mysql_query(conn,query) == 0){
			res_set = mysql_store_result(conn);

			if(res_set != NULL){
				num = mysql_num_rows(res_set);
			}	
			else{
				print_error(conn,"mysql_store_result() 실패\n");			
			}
			mysql_free_result(res_set);
		}
		else{
			print_error(conn,"mysql_query() 실패\n");
		}
	}
	mysql_close(conn);
	return num;
}

/*-------------------------------------------------
 void print_error(MYSQL* 연결정보, char* 출력 메세지):
 에러 정보 출력  
-------------------------------------------------*/
void print_error(MYSQL* conn, char* message){
	fprintf(stderr, "%s\n", message);
	if(conn != NULL){
		fprintf(stderr,"Error %u (%s): %s\n", mysql_errno(conn), mysql_sqlstate(conn), mysql_error(conn));
	}
}
