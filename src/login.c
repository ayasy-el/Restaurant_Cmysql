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

void showLoading() {
    const char loadingChars[] = {'/', '-', '\\', '|'};
    int i;

    printf("\n\t\t\t\t\t\tLoading... ");

    for (i = 0; i < 30; i++) {
        printf("%c", loadingChars[i % 4]);
        fflush(stdout);
        SLEEP(100000);
        printf("\b");
    }
    printf("\n");
}

int login(char *login_name) {
    SET_CONSOLE();
    static int trial = 0;
    char pass[20] = "";
    char name[30] = "";
    char ch;

    system(CLEAR);
    MYSQL *conn = mysql_init(NULL);
    connect_db(conn);
    printf("\n");
    printf("\t\t\t\t\t███████╗███╗   ███╗███████╗\n");
    printf("\t\t\t\t\t██╔════╝████╗ ████║██╔════╝\n");
    printf("\t\t\t\t\t█████╗  ██╔████╔██║███████╗\n");
    printf("\t\t\t\t\t██╔══╝  ██║╚██╔╝██║╚════██║\n");
    printf("\t\t\t\t\t███████╗██║ ╚═╝ ██║███████║\n");
    printf("\t\t\t\t\t╚══════╝╚═╝     ╚═╝╚══════╝\n");
    printf("\t\t\t\t\tEmployee Management Systems\n");
    printf("\t\t\t\t\t       v.1.2 ©Tribone      \n");

    if (trial >= 1 && trial <= 2) {
        /* code */
        printf("\n\n\t\t\t Nama atau password salah. Kesempatan Login hanya %d kali", 3 - trial);
    } else if (trial == 3) {
        printf("\n\t\t\t Aplikasi terblokir. Silahkan menghubungi Administrator.\n\n");
        exit(0);
    }
    printf("\n");
    printf("\n\t\t\t\t\t+-------------------------+");
    printf("\n\t\t\t\t\t| Masukkan Nama Anda:     |");
    printf("\n\t\t\t\t\t+-------------------------+");
    printf("\n\t\t\t\t\t  > ");
    scanf("%[^\n]%*c", name);

    printf("\n\t\t\t\t\t+-------------------------+");
    printf("\n\t\t\t\t\t| Masukkan Password Anda: |");
    printf("\n\t\t\t\t\t+-------------------------+");
    printf("\n\t\t\t\t\t  > ");
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
        printf("\n\n\n\t\t\t\t\t|   Verifikasi Pengguna   |\n\t\t\t\t\t");
        showLoading();
        printf("\n\t\t\t\t\t|   Memasuki Aplikasi..   |\n\n");
        SLEEP(1000000);
        MYSQL_ROW row = mysql_fetch_row(res);
        strcpy(login_name, row[0]);
        mysql_free_result(res);
        disconnect_db(conn);
        return 0;
    }

    printf("\n\n\n\t\t\t\t\t|   Verifikasi Pengguna   |\n\t\t\t\t\t");
    showLoading();
    printf("\n\t\t\t\t\t|       Login Gagal!      |\n\n");
    SLEEP(1000000);
    mysql_free_result(res);
    disconnect_db(conn);
    trial++;
    return login(login_name);
}
