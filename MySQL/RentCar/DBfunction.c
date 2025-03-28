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
	char query[200], U_query[200];
	char age[4],history[4],peopleNum[2],mileage[10],fuelamount[10],fuelefficiency[10],use_mileage[30],price[20];
	unsigned long length;

	conn = DB_connect();
	if(mysql_real_query(conn,"start transaction;",strlen("start transaction;")) != 0){
		print_error(conn,"mysql_query()-start transaction 실패\n");
		return 1;
	}

	if(conn != NULL){ 	
		switch(state){
			case 0:
				// CAR
				CAR CAR_DATA;
				CAR_DATA = *(CAR*)vp;

				strcpy(query,"INSERT INTO Car (number, kind, year, fuel, peopleNum, mileage, fuelamount, fuelefficiency, price, state) VALUES ('");

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
				strcat(query,"','");

				sprintf(price,"%d",CAR_DATA.price);
				strcat(query,price);
				strcat(query,"','0');");
				break;
			case 1:
				// Customer
				CUST CUST_DATA;
				CUST_DATA = *(CUST*)vp;

				strcpy(query,"INSERT INTO Customer (ID, phone, name, age, history, score) VALUES ('");

				strcat(query,CUST_DATA.ID);
				strcat(query,"','");
				
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
				// Rent
				RENT RENT_DATA;
				RENT_DATA = *(RENT*)vp;
				
				//Car 테이블 업데이트
				strcpy(U_query,"UPDATE Car SET state = 1 where number = '");
				strcat(U_query,RENT_DATA.number);
				strcat(U_query,"';");

				if(mysql_query(conn,U_query) != 0){
					print_error(conn,"mysql_query() Car Update 실패\n");
				}
				else{
					strcpy(query,"INSERT INTO Rent (ID, number, phone, start, end, use_mileage, destination, price) VALUES ('");

					strcat(query,RENT_DATA.ID);
					strcat(query,"','");

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
					strcat(query,"','");

					sprintf(price,"%d",RENT_DATA.price);
					strcat(query,price);
					strcat(query,"');");

				}
				break;
			default:
				break;
		}
		
		length = strlen(query);
		
		if(mysql_real_query(conn,query,length) != 0){
			print_error(conn,"mysql_query() 실패 \n");
			if(mysql_real_query(conn,"ROLLBACK",strlen("ROLLBACK")) != 0){
				print_error(conn,"ROLLBACK 실패\n");
			}
			res = 1;
		}
		else{
			if(mysql_real_query(conn,"COMMIT",strlen("COMMIT")) != 0){
				print_error(conn,"COMMIT 실패\n");
			}
		}
		// 연결정보해제
		mysql_close(conn);
	}
	return res;
}

/*-------------------------------------------------
 int DB_Modify(int 상태값, char* 바꿀열/값, char* 조건):
 Car,Customer,Rent 테이블 삽입

 -return 0: 성공 -return 1: 실패
-------------------------------------------------*/
int DB_Modify(int state, char* value, char* conditions){
	MYSQL* conn;
	int res = 0;
	char query[200];
	unsigned long length;

	conn = DB_connect();
	if(conn != NULL){ 	
		switch(state){
			case 0:
				// CAR
				// 변경사항(차번 / 운행거리,연료량,대여상태)
				strcpy(query,"UPDATE Car SET ");

				strcat(query,value);

				strcat(query,conditions);
				strcat(query,";");
				puts(query);
				break;
			case 1:
				// Customer
				// 변경사항(번호,이름,나이,운전경력/포인트)
				strcpy(query,"UPDATE Customer SET ");

				strcat(query,value);

				strcat(query,conditions);
				strcat(query,";");

				break;
			case 2:
				// Rent
				// 변경사항(반납시간,사용간 운행거리,목적지)
				strcpy(query,"UPDATE Rent SET ");

				strcat(query,value);

				strcat(query,conditions);
				strcat(query,";");
				break;
			default:
				break;
		}

		
		length = strlen(query);
		printf("%s",query);
		if(mysql_real_query(conn,query,length) != 0){
			print_error(conn,"mysql_query() 실패\n");
			if(mysql_real_query(conn,"ROLLBACK",strlen("ROLLBACK")) != 0){
				print_error(conn,"mysql_query() - ROLLBACK 실패\n");
			}
			res = 1;
		}
		else{
			if(mysql_real_query(conn,"COMMIT",strlen("COMMIT")) != 0){
				print_error(conn,"mysql_query() - COMMIT 실패\n");
			}
		}
		// 연결정보해제
		mysql_close(conn);
	}
	return res;
}

/*-------------------------------------------------
 int DB_Delete(int 상태값, char* 조건):
 Car,Customer,Rent 테이블 삽입

 -return 0: 성공 -return 1: 실패
-------------------------------------------------*/
int DB_Delete(int state, char* conditions){
	MYSQL* conn;
	int res = 0;
	char query[200];
	unsigned int length;
	conn = DB_connect();
	if(conn != NULL){ 	
		switch(state){
			case 0:
				// CAR
				// 변경사항(차번 / 운행거리,연료량,대여상태)
				strcpy(query,"DELETE FROM Car ");

				strcat(query,conditions);
				strcat(query,";");
				break;
			case 1:
				// Customer
				// 변경사항(번호,이름,나이,운전경력/포인트)
				strcpy(query,"DELETE FROM Customer ");

				strcat(query,conditions);
				strcat(query,";");
				break;
			case 2:
				// Rent
				// 변경사항(반납시간,사용간 운행거리,목적지)
				strcpy(query,"DELETE FROM Rent ");

				strcat(query,conditions);
				strcat(query,";");
				break;
			default:
				break;
		}

		length = strlen(query);
		printf("%s",query);
		if(mysql_real_query(conn,query,length) != 0){
			print_error(conn,"mysql_query() 실패\n");
			if(mysql_real_query(conn,"ROLLBACK",strlen("ROLLBACK")) != 0){
				print_error(conn,"mysql_query() - ROLLBACK 실패\n");
			}
			res = 1;
		}
		else{
			if(mysql_real_query(conn,"COMMIT",strlen("COMMIT")) != 0){
				print_error(conn,"mysql_query() - COMMIT 실패\n");
			}
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
	unsigned long length;

	strcpy(query,"select * from ");
	strcat(query,Table_Name);
	strcat(query," ");
	strcat(query,conditions);
	strcat(query,";");


	conn = DB_connect();
	if(conn != NULL){
		length = strlen(query);
		if(mysql_real_query(conn,query,length) == 0){
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
			print_error(conn,"mysql_query() 실패 \n");
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
	unsigned long length;

	strcpy(query,"select * from ");
	strcat(query,Table_Name);
	strcat(query," ");
	strcat(query,conditions);
	strcat(query,";");

	conn = DB_connect();
	if(conn != NULL){
		length = strlen(query);
		if(mysql_real_query(conn,query,length) == 0){
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

/*-------------------------------------------------
 char* DB_Get_Value(char* 값 char* 컬럼 
 char* 테이블 이름 char* 조건):
 조건에 해당하는 데이터 가져오기 
-------------------------------------------------*/
void DB_Get_Value(char* Value,char* column ,char* table, char* conditions){
	MYSQL* conn;
	MYSQL_RES* res_set;
	char query[200] = "select ";
	unsigned long length;
	
	conn = DB_connect();

	if(conn != NULL){
		strcat(query,column);
		strcat(query," from ");

		strcat(query,table);
		strcat(query," ");

		strcat(query,conditions);
		strcat(query,";");
		
		length = strlen(query);

		if(mysql_real_query(conn,query,length) == 0){
			res_set = mysql_store_result(conn);
			if(res_set != NULL){
				MYSQL_ROW row;
				unsigned int i;

				row = mysql_fetch_row(res_set);
				Value[0] = '\0';

				if(row){
					strcpy(Value,row[0]);
				}

				if(mysql_errno(conn) != 0){
					print_error(conn,"mysql_fetch_row() 실패");
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
