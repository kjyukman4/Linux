#include "Customer.h"

typedef enum { INSERT = 1, DELETE, UPDATE, SELECT, EXIT} C_menu;

/*-------------------------------------------------
C_Main(): 고객 메인 
-------------------------------------------------*/
void C_Main(){
	C_menu num;
	while((num = c_menu()) != EXIT){
		switch(num){
			case INSERT:
				Customer_Insert();
				break;
			case DELETE:
				break;
			case UPDATE:
				break;
			case SELECT:
				if(Customer_Select() != 0){
					Customer_Insert();
				}
				break;
			default:
				break;
		}
	}
}

/*-------------------------------------------------
c_menu(): 고객 메뉴 
-------------------------------------------------*/
int c_menu(){
	int num;

	printf("\t<<고객메뉴>>\n\n");
	printf("1.고객등록\t2.고객삭제\n");
	printf("3.고객수정\t4.고객조회\n");
	printf("5.뒤로가기\n");
	scanf("%d",&num);

	return num;
}

/*-------------------------------------------------
void Customer_Insert():
고객 정보 입력
-------------------------------------------------*/
void Customer_Insert(){
	CUST CUST_DATA;

	__fpurge(stdin);
	printf("전화번호: ");
	scanf("%s",CUST_DATA.phone);
	__fpurge(stdin);

	printf("이름: ");
	scanf("%s",CUST_DATA.name);
	__fpurge(stdin);

	printf("연령: ");
	scanf("%d",&CUST_DATA.age);

	printf("운전경력: ");
	scanf("%d",&CUST_DATA.history);

	if(DB_Insert(&CUST_DATA,1) == 0){
		printf("고객이 등록되었습니다!!\n");
	}
}

/*-------------------------------------------------
Customer_Delete():  
고객 정보 삭제
-------------------------------------------------*/
void Customer_Delete(MYSQL* conn){

}

/*-------------------------------------------------
Customer_Update():  
고객 정보 수정
-------------------------------------------------*/
void Customer_Update(){

}

/*-------------------------------------------------
 int Customer_Select():  
 고객 정보 및 대여차량 조회
 -return 1: 회원이 없는경우
-------------------------------------------------*/
int Customer_Select(){
	/*
	typedef struct rent{
	char number[20];
	char phone[13];
	char start[20];
	char end[20];
	int use_mileage;
	char destination[30];
}RENT;
*/

	int c_cnt, r_cnt;
	char conditions[30] = "",pnum[13] = "";
	printf("핸드폰 번호를 입력하세요: ");
	scanf("%s",pnum); 
	
	strcat(conditions,"where phone = ");
	strcat(conditions,pnum);

	c_cnt = DB_Rows_Num("Customer",conditions);
	r_cnt = DB_Rows_Num("Rent",conditions);

	if(c_cnt == 0){
		printf("존재하지 않는 회원입니다. 회원등록 메뉴로 이동합니다...\n\n");	
		return 1;
	}
	else if(c_cnt > 0){
		printf("|%-15s|%-15s|%-15s|%-15s|%-15s|\n","pnum","name","age","history","score");
		DB_Select("Customer",conditions);
		if(r_cnt == 0){
			printf("**차량을 대여한 기록이 없습니다**\n\n");
		}
		else if(r_cnt > 0){
			printf("|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|\n","start","end","kind","number","destination","use_mileage");
			//DB_Select(query);
		}
	}

	return 0;
}
