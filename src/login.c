#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

#include "database.h"
#include "multiplatform.h"

#if defined(unix)
int getch(void) {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}
#endif

int login() {
    static int trial = 0;
    char pass[20] = "";
    char name[30] = "";
    char ch;
    if (trial == 3) {
        printf("ANDA SUDAH GAGAL 3X");
        exit(0);
    }

    MYSQL *conn = mysql_init(NULL);
    connect_db(conn);

    system(CLEAR);
    printf("\n\t\t\t\t\t--------------------");
    printf("\n\t\t\t\t\t>> LOGIN KARYAWAN <<");
    printf("\n\t\t\t\t\t--------------------");
    printf("\n\n\t\t\t\t\tMasukkan Nama Anda: ");
    scanf("%[^\n]%*c", name);
    printf("\n\t\t\t\t\tMasukkan Password Anda: ");
    int i = 0;
    while ((ch = getch()) != ENTER && i < 19) {
        pass[i++] = ch;
        printf("*");
    }
    pass[i] = '\0';

    char query[256];
    snprintf(query, sizeof(query), "SELECT name, password FROM employees WHERE name='%s' AND password='%s'", name, pass);
    MYSQL_RES *res = fetch_query(conn, query);

    if (mysql_num_rows(res) > 0) {
        printf("\n\n\n\t\t\t\t\t| Verifikasi KARYAWAN |\n\t\t\t\t\t");
        for (int a = 0; a < 24; a++) {
            SLEEP(50);
            printf(".");
        }
        printf("\n\nAkses Diberikan..\n\n");
        mysql_free_result(res);
        disconnect_db(conn);
        return 0;
    }

    printf("\n\n\n\t\t\t\t\t| Verifikasi KARYAWAN |\n\t\t\t\t\t");
    for (int a = 0; a < 24; a++) {
        SLEEP(50);
        printf(".");
    }
    printf("\n\nAkses Ditolak...\n\n");

    mysql_free_result(res);
    disconnect_db(conn);
    trial++;
    return login();
}
