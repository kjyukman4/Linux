#include "DBfunction.h"
#include "Customer.h"
#include "Car.h"
#include "Rent.h"

typedef enum {CUSTOMER_M = 1, CAR_M, RENT_M, RETURN, QUIT} M_menu;
int m_menu();

int main(int argc, char *argv[]){
	M_menu num;
	char* V;
	// 클라이언트 라이브러리 초기화
	if(mysql_library_init(0,NULL,NULL)){
		fprintf(stderr,"mysql_library_init() 실패\n");
		return 0;
	}

	while((num = m_menu())!=QUIT){
		switch(num){
			case CUSTOMER_M:
				C_Main();
				break;
			case CAR_M:
				Car_Main();
				break;
			case RENT_M:
				Rent_Car();
				break;
			case RETURN:
				Return_Car();
				break;
			default:
				printf("잘못입력\n");
				break;
		}
	}

	/* 클라이언트 라이브러리 종료 */
	mysql_library_end();
	return 0;
}

int m_menu(){
	int num;

	printf("\t<<메인메뉴>>\n\n");
	printf("1.고객관리\t2.차량관리\n");
	printf("3.차량대여\t4.차량반납\n");
	printf("5.종료\n");
	scanf("%d",&num);

	return num;
}
