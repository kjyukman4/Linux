#include "DBselect.h"

static char *opt_host_name = "localhost";      /* 서버 주소(기본 값=localhost) */
static char *opt_user_name = "root";      /* 로그인 이름(기본 값=login name) */
static char *opt_password = "990101";       /* 비밀번호(기본 값=none) */
static unsigned int opt_port_num = 3306;   /* 포트 번호(자체 기본 값 사용) */
static char *opt_socket_name = NULL;    /* 소켓 이름(자체 기본 값 사용) */
static char *opt_db_name = "mysql";        /* 데이터베이스 이름(기본 값=none) */
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

    /* 서버 연결 해지, 클라이언트 라이브러리 종료 */
    mysql_close(conn);
    mysql_library_end();
    return 0; 
}
