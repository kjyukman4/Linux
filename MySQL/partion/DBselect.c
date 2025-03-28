#include "DBselect.h"

void DB_select(MYSQL* conn){
	MYSQL_RES *res_set;
	if(mysql_query(conn,"select * from phoneBook;") == 0){
		res_set = mysql_store_result(conn); // 결과 세트 생성
		if(res_set != NULL){
			// 결과 세트 처리 후 메모리 해제
			MYSQL_ROW row;
			unsigned int i;
			while((row = mysql_fetch_row(res_set)) != NULL){
				for(i=0;i<mysql_num_fields(res_set);i++){
					if(i>0){
						fputc('\t',stdout);
					}
						printf("%s",row[i] != NULL ? row[i] : "NULL");
                   }
                   fputc('\n',stdout);
               }
               if(mysql_errno(conn) == 0){
                   printf("Number of rows returned: %lu\n",(unsigned long)mysql_num_rows(res_set));
               }
               else{
                   fprintf(stderr,"mysql_fetch_row() failed");
               }
           }
           else{
               fprintf(stderr,"mysql_store_result() failed"); 
           }
        }
        else{
            fprintf(stderr,"mysql_query() faild");
        }
        mysql_free_result(res_set);
}
