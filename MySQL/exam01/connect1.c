#include <mysql.h>
#include <stdio.h>
#include <string.h>

static char *opt_host_name = "localhost";      /* 서버 주소(기본 값=localhost) */
static char *opt_user_name = "myuser";      /* 로그인 이름(기본 값=login name) */
static char *opt_password = "mySecret";       /* 비밀번호(기본 값=none) */
static unsigned int opt_port_num = 3306;   /* 포트 번호(자체 기본 값 사용) */
static char *opt_socket_name = NULL;    /* 소켓 이름(자체 기본 값 사용) */
static char *opt_db_name = "myDB";        /* 데이터베이스 이름(기본 값=none) */
static unsigned int opt_flags = 0;      /* 연결 옵션 (none) */

static MYSQL *conn;                     /* 연결 핸들러 포인터 */

int main(int argc, char *argv[]){
    mysql_init(argv[0]);
    /* 클라이언트 라이브러리 초기화 */
    if(mysql_library_init(0,NULL,NULL)){
        fprintf(stderr,"mysql_library_init() failed\n");
        return 1; 
    }
    /* 연결 핸들러 초기화 */
    conn = mysql_init(NULL);

    if(conn==NULL){
        fprintf(stderr,"myql_init() failed (probably out of memory)\n");
        return 1; 
    }

    if(mysql_real_connect (conn,opt_host_name,opt_user_name,opt_password,opt_db_name,opt_port_num,opt_socket_name,opt_flags)==NULL){
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return 1;
    }
    else{
		// select
        MYSQL_RES *res_set;
        char query[800], name[10], phone[20], relation[10];
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
        // insert
        /*
        while(1){
            strcpy(name,"");
            strcpy(phone,"");
            strcpy(relation,"");

            printf("이름: ");
            scanf("%s",name);

            if(strcmp(name,"끝")==0) break;

            printf("\n번호: ");
            scanf("%s",phone);
            printf("\n관계: ");
            scanf("%s",relation);
            
            strcpy(query,"INSERT INTO phoneBook (name,phone,relation) VALUES ('");
            strcat(query,name);
            strcat(query,"','");
            strcat(query,phone);
            strcat(query,"','");
            strcat(query,relation);
            strcat(query,"')");

            if(mysql_query(conn,query) == 0){
                fprintf(stderr,"success");
            }
        }
        */
    }

    /* 서버 연결 해지, 클라이언트 라이브러리 종료 */
    mysql_close(conn);
    mysql_library_end();
    return 0; 
}
