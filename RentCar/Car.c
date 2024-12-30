#include "Car.h"

typedef enum { INSERT = 1, DELETE, UPDATE, SELECT, EXIT} Car_menu;

/*-------------------------------------------------
Car_Main(): 고객 메인 
-------------------------------------------------*/
void Car_Main(){
	Car_menu num;
	while((num = car_menu()) != EXIT){
		switch(num){
			case INSERT:
				Car_Insert();
				break;
			case DELETE:
				break;
			case UPDATE:
				break;
			case SELECT:
				break;
			default:
				break;
		}
	}
}

/*-------------------------------------------------
car_menu(): 고객 메뉴 
-------------------------------------------------*/
int car_menu(){
	int num;

	printf("\t<<차량메뉴>>\n\n");
	printf("1.차량등록\t2.차량삭제\n");
	printf("3.차량수정\t4.차량조회\n");
	printf("5.뒤로가기\n");
	scanf("%d",&num);

	return num;
}

/*-------------------------------------------------
void Car_Insert():
차량 정보 입력
-------------------------------------------------*/
void Car_Insert(){
	CAR CAR_DATA;

	printf("차량번호: ");
	scanf("%s",CAR_DATA.number);
	__fpurge(stdin);

	printf("차종: ");
	scanf("%s",CAR_DATA.kind);
	__fpurge(stdin);

	printf("연식: ");
	scanf("%s",CAR_DATA.year);
	__fpurge(stdin);

	printf("연료: ");
	scanf("%s",CAR_DATA.fuel);
	__fpurge(stdin);

	printf("탑승가능인원: ");
	scanf("%d",&CAR_DATA.peopleNum);

	printf("주행거리: ");
	scanf("%d",&CAR_DATA.mileage);

	printf("연료량: ");
	scanf("%d",&CAR_DATA.fuelamount);

	printf("연비: ");
	scanf("%d",&CAR_DATA.fuelefficiency);
		
	if(DB_Insert(&CAR_DATA,0) == 0){
		printf("차량이 등록되었습니다!!\n");
	}
}

/*-------------------------------------------------
Car_Delete(MYSQL* 연결정보, char* 쿼리):  
고객 정보 삭제
-------------------------------------------------*/
void Car_Delete(MYSQL* conn,char* str){

}

/*-------------------------------------------------
Car_Update(MYSQL* 연결정보, char* 쿼리):  
고객 정보 수정
-------------------------------------------------*/
void Car_Update(MYSQL* conn,char* str){

}

/*-------------------------------------------------
Car_Select(MYSQL* 연결정보, char* 쿼리):  
고객 정보 조회
-------------------------------------------------*/
void Car_Select(MYSQL* conn,char* str){

}
