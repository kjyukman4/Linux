#include <stdio.h>
#include <mysql.h>
#include <my_getopt.h>

static char *opt_host_name = "localhost";      /* 서버 주소(기본 값=localhost) */
static char *opt_user_name = "sampadm";      /* 로그인 이름(기본 값=login name) */
static char *opt_password = "secret";       /* 비밀번호(기본 값=none) */
static unsigned int opt_port_num = 3306;   /* 포트 번호(자체 기본 값 사용) */
static char *opt_socket_name = NULL;    /* 소켓 이름(자체 기본 값 사용) */
static char *opt_db_name = "sampdb";        /* 데이터베이스 이름(기본 값=none) */
static unsigned int opt_flags = 0;      /* 연결 옵션 (none) */

static int ask_password = 0;

static MYSQL *conn;                     /* 연결 핸들러 포인터 */

static const char *client_groups[] = {"client", NULL};

static struct my_option my_opts[] = 
{
    {"help",'?',"Display this help and exit",NULL,NULL,NULL,GET_NO_ARG,NO_ARG,0,0,0,0,0,0},
    {"host",'h',"Host to connect to",(uchar**) &opt_host_name,NULL,NULL,GET_STR,REQUIRED_ARG,0,0,0,0,0,0,0},
    {"password",'p',"Password",(uchar**) &opt_password,NULL,NULL,GET_STR,OPT_ARG,0,0,0,0,0,0},
    {"port",'P',"Port number",(uchar**) &opt_port_num,NULL,NULL,GET_UINT,REQUIRED_ARG,0,0,0,0,0,0},
    {"socket",'S',"Socket path",(uchar**) &opt_socket_name,NULL,NULL,GET_STR,REQUIRED_ARG,0,0,0,0,0,0},
    {"user",'u',"User name",(uchar**) &opt_user_name,NULL,NULL,GET_STR,REQUIRED_AVG,0,0,0,0,0,0},
    {NULL,0,NULL,NULL,NULL,NULL,GET_NO_ARG,NO_ARG,0,0,0,0,0,0}
};

static void print_error(MYSQL *, char *);
static my_bool get_one_option(int ,const struct my_option *,char *);

int main(int argc, char *argv[]){
    int opt_err;

    mysql_init(argv[0]);
    load_defaults("my", client_groups, &argc, &argv);

    if((opt_err = handle_options (&arfc, &argv, my_opts, get_one,option))) return opt_err;

    /* 필요시 비밀번호 재요청 */
    if(ask_password) opt_password = get_tty_password(NULL);

    /* 필요시 커맨드라인에서 데이터베이스 이름 입력받음 */
    if(argc > 0){
        opt_db_name = argv[0];
        --argc;
        ++argv;
    }

    /* 클라이언트 라이브러리 초기화 */
    if(mysql_library_init(0,NULL,NULL)){
        fprintf(stderr,"mysql_library_init() failed\n");
        return 1; 
    }

    /* 연결 핸들러 초기화 */
    conn = mysql_init(NULL);

    if(conn==NULL){
        print_error(NULL,"myql_init() failed (probably out of memory)\n");
        return 1; 
    }
    
    /* 서버에 연결 */
    if(mysql_real_connect (conn,opt_host_name,opt_user_name,opt_password,opt_db_name,opt_port_num,opt_socket_name,opt_flags)==NULL){
        print_error(conn, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return 1;
    }

    /* 서버 연결 해지, 클라이언트 라이브러리 종료 */
    mysql_close(conn);
    mysql_library_end();
    return 0; 
}

static void print_error(MYSQL *conn, char *message){
    fprintf(stderr,"%s\n",message);
    if(conn!=NULL){
        fprintf(stderr,"Error %u (%s): %s\n", mysql_errno(conn),mysql_sqlstate(conn),mysql_error(conn));
    }
}

static my_bool get_one_option(int optid,const struct my_option *opt,char *argument){
    switch(optid){
        case '?':
            my_print_help(my_opts);     /* 도움말 출력 */
            return 0;
        case 'p':   /* 비밀번호 */
            if(!argument)   /* 값이 주어지지 않은 경우; 나중에 다시 요청 */
                ask_password = 1;
            else{    /* 비밀번호 값을 복사해 변수에 저장 */
                opt_password = strdup(argument);
                if(opt_password == NULL){
                    print_error(NULL,"could not allocate password buffer");
                    return 1;
                }
                while(*argument){
                    *argument++ = 'x';
                }
                ask_password = 0;
            }
            break;
    }
    return 0;
}


























