#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

#include "../database.h"
#include "../multiplatform.h"

char name[30];
char id[5];
char password[20];
char phone[15];

void waitForEnter();

void insert() {
    system(CLEAR);
    MYSQL *conn = mysql_init(NULL);
    connect_db(conn);

    printf("\n-------------------------------------------------------------------------------------------------------\n");
    printf("------------------------------------- Tambah Data Karyawan --------------------------------------------\n");
    printf("\n Masukkan Nama Karyawan: ");
    scanf("%[^\n]%*c", name);
    char ch;
    printf("\n Masukkan Password: ");
    int i = 0;
    while ((ch = getch()) != ENTER && i < 19) {
        password[i++] = ch;
        printf("*");
    }
    password[i] = '\0';
    printf("\n Masukkan No. Telp: ");
    scanf("%s", phone);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO employees (name, password, phone) VALUES ('%s', '%s', '%s')", name, password, phone);
    execute_query(conn, query);

    printf("\n\nBerhasil Menambah Data Karyawan\n");

    disconnect_db(conn);
}

void display() {
    system(CLEAR);
    MYSQL *conn = mysql_init(NULL);
    connect_db(conn);

    MYSQL_RES *res = fetch_query(conn, "SELECT id, name, phone FROM employees");
    MYSQL_ROW row;

    int total = 1;
    printf("\n-------------------------------------------------------------------------------------------------------\n");
    printf("------------------------------------- Data Karyawan ---------------------------------------------------\n");
    printf("\n ------------------------------------------------------------------------------------------\n");
    printf("||    ID    ||    NAMA    ||    NO. TELP    ||\n");
    printf(" ------------------------------------------------------------------------------------------\n");

    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("\n%d. \t%s\t  %s\t\t  %s\n", total++, row[0], row[1], row[2]);
    }

    mysql_free_result(res);
    disconnect_db(conn);
    waitForEnter();
}

void modify() {
    system(CLEAR);
    char checkId[5];
    int found = 0;

    MYSQL *conn = mysql_init(NULL);
    connect_db(conn);

    printf("\n-------------------------------------------------------------------------------------------------------\n");
    printf("------------------------------------- Edit Data Karyawan ----------------------------------------------\n");
    printf("\nMasukkan ID Karyawan: ");
    scanf("%s", checkId);

    char query[256];
    snprintf(query, sizeof(query), "SELECT id FROM employees WHERE id='%s'", checkId);
    MYSQL_RES *res = fetch_query(conn, query);

    if (mysql_num_rows(res) > 0) {
        found = 1;
        printf("\n Masukkan Nama Karyawan: ");
        scanf("%[^\n]%*c", name);
        char ch;
        printf("\n Masukkan Password: ");
        int i = 0;
        getch();
        while ((ch = getch()) != ENTER && i < 19) {
            password[i++] = ch;
            printf("*");
        }
        password[i] = '\0';
        printf("\n Masukkan No. Telp: ");
        scanf("%s", phone);

        snprintf(query, sizeof(query), "UPDATE employees SET name='%s', password='%s', phone='%s' WHERE id='%s'", name, password, phone, checkId);
        execute_query(conn, query);
        printf("\n\nBerhasil Mengubah Data Karyawan\n");
    }

    if (!found) {
        printf("\n\n\tID Karyawan Tidak Ditemukan.. Silakan Coba Lagi\n");
    }

    mysql_free_result(res);
    disconnect_db(conn);
    waitForEnter();
}

void deleted() {
    system(CLEAR);
    char checkId[5];
    int found = 0;

    MYSQL *conn = mysql_init(NULL);
    connect_db(conn);

    printf("\n-------------------------------------------------------------------------------------------------------\n");
    printf("------------------------------------- Hapus Data Karyawan ----------------------------------------------\n");
    printf("\nMasukkan ID Karyawan Untuk Menghapus Data: ");
    scanf("%s", checkId);

    char query[256];
    snprintf(query, sizeof(query), "SELECT id FROM employees WHERE id='%s'", checkId);
    MYSQL_RES *res = fetch_query(conn, query);

    if (mysql_num_rows(res) > 0) {
        found = 1;
        snprintf(query, sizeof(query), "DELETE FROM employees WHERE id='%s'", checkId);
        execute_query(conn, query);
        printf("\n\nBerhasil Menghapus Data Karyawan\n");
    }

    if (!found) {
        printf("\n\n\tID Karyawan Tidak Ditemukan.. Silakan Coba Lagi\n");
    }

    mysql_free_result(res);
    disconnect_db(conn);
    waitForEnter();
}
