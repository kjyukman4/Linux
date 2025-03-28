#include "Car.h"

typedef enum { INSERT = 1, DELETE, UPDATE, SELECT, EXIT} Car_menu;

/*-------------------------------------------------
 Car_Main(): 차량 메인 
-------------------------------------------------*/
void Car_Main(){
	Car_menu num;
	while((num = car_menu()) != EXIT){
		switch(num){
			case INSERT:
				Car_Insert();
				break;
			case DELETE:
				Car_Delete();
				break;
			case UPDATE:
				Car_Update();
				break;
			case SELECT:
				Car_Select();
				break;
			default:
				break;
		}
	}
}

/*-------------------------------------------------
 car_menu(): 차량 메뉴 
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
 void Car_Insert(): 차량 정보 입력
-------------------------------------------------*/
void Car_Insert(){
	int num = 0;
	CAR CAR_DATA;

	printf("차량번호: ");
	scanf("%s",CAR_DATA.number);
	__fpurge(stdin);

	// 승용, SUV, 승합
	while(1){
		printf("차종을 선택해 주세요.\n");
		printf("1.승용\n2.SUV\n3.승합\n: ");
		scanf("%d",&num);

		switch(num){
			case 1:
				strcpy(CAR_DATA.kind,"승용");
				break;
			case 2:
				strcpy(CAR_DATA.kind,"SUV");
				break;
			case 3:
				strcpy(CAR_DATA.kind,"승합");
				break;
			default:
				printf("\n잘못입력\n");
				break;
		}
		if(0 < num && num < 4) break;
	}
	
	printf("연식: ");
	scanf("%s",CAR_DATA.year);
	__fpurge(stdin);

	// 휘발유 경유 LPG 전기 
	while(1){
		printf("연료를 선택해 주세요.\n");
		printf("1.휘발유\n2.경유\n3.LPG\n4.전기\n: ");
		scanf("%d",&num);

		switch(num){
			case 1:
				strcpy(CAR_DATA.fuel,"휘발유");
				break;
			case 2:
				strcpy(CAR_DATA.fuel,"경유");
				break;
			case 3:
				strcpy(CAR_DATA.fuel,"LPG");
				break;
			case 4:
				strcpy(CAR_DATA.kind,"전기");
				break;
			default:
				printf("\n잘못입력\n");
				break;
		}
		if(0 < num && num < 5) break;
	}

	// 승용 무조건 5 중형 5~7 승합 7~11
	while(1){
		printf("탑승 인원을 선택해 주세요.\n");

		if(strcmp(CAR_DATA.kind,"승용") == 0){
			printf("1.5인승\n: ");
			scanf("%d",&num);

			switch(num){
			case 1:
				CAR_DATA.peopleNum = 5;
				break;
			default:
				printf("\n잘못입력\n");
				break;
			}
			if(0 < num && num < 2) break;	
		}
		else if(strcmp(CAR_DATA.kind,"SUV") == 0){
			printf("1.5인승\n2.6인승\n3.7인승\n: ");
			scanf("%d",&num);

			switch(num){
			case 1:
				CAR_DATA.peopleNum = 5;
				break;
			case 2:
				CAR_DATA.peopleNum = 6;
				break;
			case 3:
				CAR_DATA.peopleNum = 7;
				break;
			default:
				printf("\n잘못입력\n");
				break;
			}
			if(0 < num && num < 4) break;
		}
		else{
			printf("1.7인승\n2.8인승\n3.9인승\n4.10인승\n5.11인승\n: ");
			scanf("%d",&num);

			switch(num){
			case 1:
				CAR_DATA.peopleNum = 7;
				break;
			case 2:
				CAR_DATA.peopleNum = 8;
				break;
			case 3:
				CAR_DATA.peopleNum = 9;
				break;
			case 4:
				CAR_DATA.peopleNum = 10;
				break;
			case 5:
				CAR_DATA.peopleNum = 11;
				break;
			default:
				printf("\n잘못입력\n");
				break;
			}
			if(0 < num && num < 6) break;
		}
		
	}

	printf("주행거리: ");
	scanf("%d",&CAR_DATA.mileage);

	printf("연료량: ");
	scanf("%d",&CAR_DATA.fuelamount);

	printf("연비: ");
	scanf("%d",&CAR_DATA.fuelefficiency);
		
	printf("가격: ");
	scanf("%d",&CAR_DATA.price);

	if(DB_Insert(&CAR_DATA,0) == 0){
		printf("차량이 등록되었습니다!!\n");
	}
}

/*-------------------------------------------------
 Car_Delete(MYSQL* 연결정보, char* 쿼리):  
 차량 정보 삭제
-------------------------------------------------*/
void Car_Delete(){
	char Car_N[20],conditions[200];

	printf("차량번호를 입력하세요: ");
	scanf("%s",Car_N);
	
	strcpy(conditions,"where number = '");		
	strcat(conditions,Car_N);
	strcat(conditions,"'");

	if(DB_Rows_Num("Car",conditions)){
		strcat(conditions," AND state = '0'");

		if(DB_Rows_Num("Car",conditions)){
			DB_Delete(0,conditions);
			printf("**차량이 삭제되었습니다**\n\n");	
		}
		else{
			printf("**현재 대여중인 차량입니다**\n\n");
		}
	}
	else{
		printf("**존재하지않은 차량입니다**\n\n");
	}
}

/*-------------------------------------------------
 Car_Update(MYSQL* 연결정보, char* 쿼리):  
 차량 정보 수정
-------------------------------------------------*/
void Car_Update(){
	char Car_Ex[20],Car_N[20],conditions[200],value[30],price[20];

	printf("차량번호를 입력하세요: ");
	scanf("%s",Car_N);
	
	strcpy(conditions,"where number = '");		
	strcat(conditions,Car_N);
	strcat(conditions,"'");

	if(DB_Rows_Num("Car",conditions)){
		strcat(conditions," AND state = '0'");
		strcpy(Car_Ex,Car_N);

		if(DB_Rows_Num("Car",conditions)){
			printf("변경할 차량번호를 입력하세요: ");
			scanf("%s",Car_N);

			strcpy(conditions,"where number = '");
			strcat(conditions,Car_N);
			strcat(conditions,"'");	

			if(DB_Rows_Num("Car",conditions) == 0){
				printf("변경할 차량가격을 입력하세요: ");
				scanf("%s",price);
				
				strcpy(value,"number = '");
				strcat(value,Car_N);
				strcat(value,"', price = '");
				strcat(value,price);
				strcat(value,"'");

				strcpy(conditions,"where number = '");
				strcat(conditions,Car_Ex);
				strcat(conditions,"'");

				DB_Modify(0,value,conditions);
				
				printf("**차량 정보수정 완료**\n\n");	
			}
			else{
				printf("**중복되는 차량번호 입니다**\n\n");
			}
		}
		else{
			printf("**현재 대여중인 차량입니다**\n\n");
		}
	}
	else{
		printf("**존재하지않은 차량입니다**\n\n");
	}
}

/*-------------------------------------------------
 Car_Select(MYSQL* 연결정보, char* 쿼리):  
 고객 정보 조회
-------------------------------------------------*/
void Car_Select(){
	DB_Select("Car","");
}
