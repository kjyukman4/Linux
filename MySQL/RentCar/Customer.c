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
				Customer_Delete();
				break;
			case UPDATE:
				Customer_Update();
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
	char conditions[200];

	__fpurge(stdin);
	while(1){
		__fpurge(stdin);
		printf("주민등록번호: ");
		scanf("%s",CUST_DATA.ID);
		__fpurge(stdin);
		strcpy(conditions," where ID = '");
		strcat(conditions,CUST_DATA.ID);
		strcat(conditions,"'");
		if(DB_Rows_Num("Customer",conditions) == 0) break;
		printf("이미 존재하는 회원입니다\n\n");

	}	
	__fpurge(stdin);
	while(1){
		printf("전화번호: ");
		scanf("%s",CUST_DATA.phone);
		__fpurge(stdin);
		strcpy(conditions," where phone = '");
		strcat(conditions,CUST_DATA.phone);
		strcat(conditions,"'");
		if(DB_Rows_Num("Customer",conditions) == 0) break;
		printf("이미 존재하는 전화 번호입니다\n\n");
	}
	printf("이름: ");
	scanf("%s",CUST_DATA.name);
	__fpurge(stdin);

	printf("연령: ");
	scanf("%d",&CUST_DATA.age);

	printf("운전경력: ");
	scanf("%d",&CUST_DATA.history);
	if(DB_Insert(&CUST_DATA,1) == 0){
		printf("**고객이 등록되었습니다**\n");
		printf("##ID는 주민등록번호 입니다##\n");
	}
}

/*-------------------------------------------------
 void Customer_Delete():  
 고객 정보 삭제
-------------------------------------------------*/
void Customer_Delete(){
	char ID[20],conditions1[50],conditions2[100],YN;

	printf("ID를 입력해주세요: ");
	scanf("%s",ID);
	__fpurge(stdin);

	strcpy(conditions1,"where ID = '");
	strcat(conditions1,ID);
	strcat(conditions1,"'");

	if(DB_Rows_Num("Customer",conditions1)){
		strcpy(conditions2,conditions1);
		strcat(conditions2," AND end is NULL");
		if(DB_Rows_Num("Rent",conditions2) == 0){
			printf("삭제하시겠습니까?(Y/N):");
			scanf("%c",&YN);

			if(YN == 'Y'){
				DB_Delete(1,conditions1);
				printf("**삭제하였습니다**\n\n");
			}
			else{
				printf("**취소하였습니다**\n\n");
			}
		}
		else{
			printf("**차량을 반납해주세요**\n\n");
		}
	}
	else{
		printf("**존재하지않는 회원입니다**\n\n");
	}
}

/*-------------------------------------------------
 void Customer_Update():  
 고객 정보 수정
-------------------------------------------------*/
void Customer_Update(){
	int age,history;
	char ID[20],conditions[50],N_phone[14],name[11],Value1[200],Value2[200],Age[4],History[30];

	printf("ID를 입력하세요:");
	scanf("%s",ID);

	strcpy(conditions,"where ");
	strcat(conditions,"ID = '");
	strcat(conditions,ID);
	strcat(conditions,"'");

	if(DB_Rows_Num("Customer",conditions)){
		// 여기에 전화번호 중복 확인해야됌
		printf("변경할 전화번호를 입력하세요: ");
		scanf("%s",N_phone);
		
		strcpy(conditions,"where ");
		strcat(conditions,"phone = '");
		strcat(conditions,N_phone);
		strcat(conditions,"'");
		
		if(DB_Rows_Num("Customer",conditions) == 0){
			DB_Get_Value(Value1,"phone","Customer",conditions);

			if(!strlen(Value1)){
				//중복없음
				printf("수정할 이름을 입력하세요:");
				scanf("%s",name);

				printf("수정할 나이를 입력하세요:");
				scanf("%d",&age);

				printf("수정할 운전경력을 입력하세요:");
				scanf("%d",&history);

				sprintf(Age,"%d",age);
				sprintf(History,"%d",history);

				strcpy(Value1,"phone = '");
				strcat(Value1,N_phone);
				strcat(Value1,"', name = '");
				strcat(Value1,name);
				strcat(Value1,"', age = '");
				strcat(Value1,Age);
				strcat(Value1,"', history = '");
				strcat(Value1,History);
				strcat(Value1,"' ");
					
				strcpy(Value2,"phone = '");
				strcat(Value2,N_phone);
				strcat(Value2,"'");

				strcpy(conditions,"where ID = '");
				strcat(conditions,ID);
				strcat(conditions,"'");
				
				DB_Modify(1,Value1,conditions);
				DB_Modify(2,Value2,conditions);
				printf("**수정이 완료되었습니다**");	
			}
			else{
				//중복있음
				printf("**중복되는 번호입니다**\n\n");
			}
		}
		else{
			printf("**중복되는 번호입니다**\n\n");
		}

	}
	else{
		printf("**존재하지않는 고객입니다**\n\n");
	}

}

/*-------------------------------------------------
 int Customer_Select():  
 고객 정보 및 대여차량 조회
 -return 1: 회원이 없는경우
-------------------------------------------------*/
int Customer_Select(){
	int c_cnt, r_cnt;
	char conditions[30] = "", ID[20] = "";

	printf("ID를 입력하세요: ");
	scanf("%s",ID); 

	strcat(conditions,"where ID LIKE '");
	strcat(conditions,ID);
	strcat(conditions,"'");

	c_cnt = DB_Rows_Num("Customer",conditions);
	r_cnt = DB_Rows_Num("Rent",conditions);

	if(c_cnt == 0){
		printf("존재하지 않는 회원입니다. 회원등록 메뉴로 이동합니다...\n\n");	
		return 1;
	}
	else if(c_cnt > 0){
		printf("|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|\n","ID","pnum","name","age","history","score");
		DB_Select("Customer",conditions);
		if(r_cnt == 0){
			printf("**차량을 대여한 기록이 없습니다**\n\n");
		}
		else if(r_cnt > 0){
			printf("|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|\n","NO","ID","phone","start","end","kind","number","destination","use_mileage");
			DB_Select("Rent",conditions);
		}
	}

	return 0;
}
