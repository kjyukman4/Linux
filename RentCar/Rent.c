#include "Rent.h"
/*-------------------------------------------------
Rent_Car(): 대여
-------------------------------------------------*/
void Rent_Car(){
	char conditions[30],phone[20],number[20];
	int rnum;
	RENT RENT_DATA;
	rnum = DB_Rows_Num("Customer","");

	if(rnum > 0){
		rnum = DB_Rows_Num("Car","");
		if(rnum > 0){
			printf("<회원 목록>\n|%-15s|%-15s|%-15s|%-15s|%-15s|\n","phone","name","age","history","score");
			DB_Select("Customer","");
			printf("\n<차량 목록>\n|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|\n"
			,"number","kind","year","fuel","peopleNum","mileage","fuelamount","fuelefficiency","state");
			DB_Select("Car","");
			
			// 차량 대여(핸드폰번호 입력)
			printf("대여하실 분의 핸드폰 번호를 입력해주세요: ");
			scanf("%s",phone);
			
			strcpy(conditions,"where phone = ");
			strcat(conditions,phone);

			if(DB_Rows_Num("Customer",conditions)){
				// 차량 대여(차량번호 입력)
				printf("대여하실 차량번호를 입력해주세요: ");
				scanf("%s",number);

				strcpy(conditions,"where number = ");
				strcat(conditions,number);
				if(DB_Rows_Num("Car",conditions)){
					strcpy(RENT_DATA.number,number);
					strcpy(RENT_DATA.phone,phone);
					//차량 대여시간
					strcpy(RENT_DATA.start,"now()");	
					//차량 반납시간
					strcpy(RENT_DATA.end,"now()");
					//주행거리
					RENT_DATA.use_mileage = 0;
					//목적지
					strcpy(RENT_DATA.destination,"0");

					if(DB_Insert(&RENT_DATA,2) == 0){
						printf("차량을 대여하였습니다.\n\n");
					}
				}
				else{
					printf("**존재하지 않는 차량**\n\n");
				}
			}
			else{
				printf("**존재하지 않는 회원**\n\n");
			}
		}	
		else if(rnum == 0){
			printf("등록된 차량이 없습니다.\n");	
		}
	}
	else if(rnum == 0){
		printf("등록된 회원이 없습니다.\n");
	}
}
