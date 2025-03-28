#include "Rent.h"
/*-------------------------------------------------
Rent_Car(): 대여
-------------------------------------------------*/
void Rent_Car(){
	char ID[20],conditions[50],phone[14],number[20];
	int rnum,num;
	RENT RENT_DATA;
	rnum = DB_Rows_Num("Customer","");

	if(rnum > 0){
		rnum = DB_Rows_Num("Car","");
		if(rnum > 0){
			printf("<회원 목록>\n|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|\n","ID","phone","name","age","history","score");
			DB_Select("Customer","");

			// 차량 대여
			printf("대여하실 분의 ID를 입력해주세요: ");
			scanf("%s",ID);
			
			strcpy(conditions,"where ID = '");
			strcat(conditions,ID);
			strcat(conditions,"'");

			if(DB_Rows_Num("Customer",conditions)){
				// 차종선택
				while(1){
					printf("차종을 선택하세요\n");
					printf("1.승용\n2.SUV\n3.승합\n");
					scanf("%d",&num);
					if(0 < num && num < 4){
						switch(num){
						case 1:
							strcpy(conditions,"where kind = '승용' and state = 0");
							break;
						case 2:
							strcpy(conditions,"where kind = 'SUV' and state = 0");
							break;
						case 3:
							strcpy(conditions,"where kind = '승합' and state = 0");
							break;
						default:
							printf("잘못입력");
							break;
						}
						break;
					} 
					printf("\n잘못입력\n");
				}
				// 차량 조회
				if(DB_Rows_Num("Car",conditions)){
					printf("\n<차량 목록>\n|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|\n"
					,"number","kind","year","fuel","peopleNum","mileage","fuelamount","fuelefficiency","state","price");
				
					DB_Select("Car",conditions);
					
					// 차량 대여(차량번호 입력)
					printf("대여하실 차량번호를 입력해주세요: ");
					scanf("%s",number);

					strcat(conditions," and number = '");
					strcat(conditions,number);
					strcat(conditions,"'");

					if(DB_Rows_Num("Car",conditions)){
						strcpy(RENT_DATA.ID,ID);
						strcpy(RENT_DATA.number,number);
						
						strcpy(conditions,"where ID = '");
						strcat(conditions,ID);
						strcat(conditions,"'");

						DB_Get_Value(phone,"phone","Customer",conditions);

						strcpy(RENT_DATA.phone,phone);
						//차량 대여시간
						strcpy(RENT_DATA.start,"now()");	
						//차량 반납시간
						strcpy(RENT_DATA.end,"NULL");
						//주행거리
						RENT_DATA.use_mileage = 0;
						//목적지
						strcpy(RENT_DATA.destination,"-");
						//비용
						RENT_DATA.price = 0;
						
						if(DB_Insert(&RENT_DATA,2) == 0){
							// Car 테이블의 state값을 수정해야됌
							strcpy(conditions,"where number = '");
							strcat(conditions,RENT_DATA.number);
							strcat(conditions,"'");
							
							DB_Modify(0 ,"state = 1 ", conditions);
							printf("차량을 대여하였습니다.\n\n");
						}
					}
					else{
						printf("**존재하지 않는 차량**\n\n");
					}
				}
				else{
					printf("**대여할수 있는 차량이 없습니다**\n\n");
				}
			}
			else{
				printf("**존재하지 않는 회원**\n\n");
			}
		}	
		else if(rnum == 0){
			printf("**등록된 차량이 없습니다**\n\n");	
		}
	}
	else if(rnum == 0){
		printf("**등록된 회원이 없습니다**\n\n");
	}
}

/*-------------------------------------------------
Return_Car():반납 
-------------------------------------------------*/
void Return_Car(){
	int rnum,F,Fa,M,Mi,Pr;
	float Sc;
	char ID[20],number[2],conditions1[50],conditions2[100],conditions3[50],mileage[30],fuelamount[30],
	destination[30],Value1[200],Value2[200],Value3[200],add_mile[20],Fuel[20],Mile[30],Score[30],Price[30];
	rnum = DB_Rows_Num("Car","where state = 1");

	if(rnum > 0){
		printf("\n<차량 목록>\n|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|%-15s|\n"
		,"number","kind","year","fuel","peopleNum","mileage","fuelamount","fuelefficiency","state");

		strcpy(conditions1,"where state = 1");
		DB_Select("Car",conditions1);

		// 차량 대여(차량번호 입력)
		printf("반납하실 차량번호를 입력해주세요: ");
		scanf("%s",number);
		
		strcat(conditions1," and number = '");
		strcat(conditions1,number);
		strcat(conditions1,"'");

		if(DB_Rows_Num("Car",conditions1)){
			// 운행거리 입력
			printf("운행한 거리를 입력해주세요:");
			scanf("%s",mileage);
				
			// 기존 잔여 연료 가져오기
			DB_Get_Value(Fuel,"fuelamount","Car",conditions1);
			F = atoi(Fuel);

			// 기존 운행거리 가져오기
			DB_Get_Value(Mile,"mileage","Car",conditions1);
			M = atoi(Mile);
			Mi = atoi(mileage);

			// 고객 포인트 가져오기
			strcpy(conditions2,"where number = '");
			strcat(conditions2,number);
			strcat(conditions2,"' and ");
			strcat(conditions2,"use_mileage = 0 and ");
			strcat(conditions2,"destination = '-'");

			DB_Get_Value(ID,"ID","Rent",conditions2);

			strcpy(conditions3,"where ID = '");
			strcat(conditions3,ID);
			strcat(conditions3,"'");

			DB_Get_Value(Score,"score","Customer",conditions3);
			Sc = atof(Score);

			// 차량 가격 가져오기
			DB_Get_Value(Price,"price","Car",conditions1);
			Pr = atoi(Price);
			
			// 얻게되는 포인트 계산
			Sc = Sc + Pr/10;
			sprintf(Score,"%lf",Sc);

			sprintf(add_mile,"%d",M + Mi);
			// 반납시 연료(기존보다 같거나 많아야됌)
			while(1){
				printf("반납시 연료를 입력해주세요:");
				scanf("%d",&Fa);
				if(F<=Fa) break;
				printf("**반납시 연료는 기존보다 같거나 많아야합니다**\n\n");
			}
			sprintf(fuelamount,"%d",Fa);	

			// 목적지(경유지)	
			printf("다녀온 곳을 입력해주세요:");
			scanf("%s",destination);

			strcpy(Value2,"end = now(),");
			strcat(Value2,"use_mileage = ");
			strcat(Value2,mileage);
			strcat(Value2,",destination = '");
			strcat(Value2,destination);
			strcat(Value2,"' ,price = ");
			strcat(Value2,Price);
			strcat(Value2," ");

			strcpy(Value1,"state = 0,");
			strcat(Value1,"mileage = ");
			strcat(Value1,add_mile);
			strcat(Value1,",fuelamount = ");
			strcat(Value1,fuelamount);
			strcat(Value1," ");

			strcpy(Value3,"score = ");
			strcat(Value3,Score);
			
			if(DB_Modify(2,Value2,conditions2) == 0){
				DB_Modify(0,Value1,conditions1);
				DB_Modify(1,Value3,conditions3);
				printf("** 차량을 반납하였습니다**\n\n");
			}
		}
		else{
			printf("**존재하지않는 차량입니다**\n\n");
		}
	}
	else{
		printf("**대여한 차량이 없습니다**\n\n");	
	}
}
