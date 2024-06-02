#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../database.h"
#include "../multiplatform.h"

void tambah_menu() {
    MYSQL *conn = mysql_init(NULL);
    connect_db(conn);

    int hargaMenu;
    char namaMenu[120];

    system(CLEAR);
    printf("\n============================================\n");
    printf("               Tambah Menu\n");
    printf("============================================\n");

    printf("Masukkan Nama menu: ");
    while (getchar() != '\n');
    scanf("%[^\n]%*c", namaMenu);

    while (1) {
        printf("Masukkan Harga menu: ");
        scanf("%d", &hargaMenu);
        if (hargaMenu > 0) break;
        printf("Harga harus lebih dari 0\n\n");
    }

    char query[256];
    sprintf(query, "INSERT INTO Menu (NamaMenu, HargaMenu) VALUES ('%s', %d)", namaMenu, hargaMenu);
    execute_query(conn, query);

    printf("Menu berhasil ditambahkan!\n");
    printf("============================================\n");
    printf("Tekan Enter untuk kembali...\n");
    fflush(stdin);
    while (getchar() != '\n');

    disconnect_db(conn);
}

void edit_menu() {
    MYSQL *conn = mysql_init(NULL);
    connect_db(conn);

    int hargaMenu = -1;
    char namaMenu[120] = "";

    system(CLEAR);
    printf("\n============================================\n");
    printf("               Edit Menu\n");
    printf("============================================\n");

    printf("  Daftar Menu:\n");
    MYSQL_RES *result = fetch_query(conn, "SELECT MenuID, NamaMenu, HargaMenu FROM Menu");
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        printf("   [%s] %s : %s\n", row[0], row[1], row[2]);
    }
    mysql_free_result(result);
    printf("--------------------------------------------\n\n");

    int menuID;
    printf("Pilih nomor menu yang akan diedit: ");
    scanf("%d", &menuID);

    printf("\nKosongi jika tidak ingin mengubahnya\n");
    printf("Masukkan Nama Menu Baru: ");
    fflush(stdin);
    scanf("%[^\n]%*c", namaMenu);

    char harga[10];
    printf("Masukkan Harga menu: ");
    fflush(stdin);
    scanf("%[^\n]%*c", harga);
    hargaMenu = atoi(harga);

    char query[256], setQuery[125] = "";
    if (namaMenu[0] != '\0')
        sprintf(setQuery + strlen(setQuery), "NamaMenu='%s'", namaMenu);
    if (namaMenu[0] != '\0' && hargaMenu > 0)
        sprintf(setQuery + strlen(setQuery), ", ");
    if (hargaMenu > 0)
        sprintf(setQuery + strlen(setQuery), "HargaMenu=%d", hargaMenu);

    if (namaMenu[0] != '\0' || hargaMenu > 0) {
        sprintf(query, "UPDATE Menu SET %s WHERE MenuID=%d;", setQuery, menuID);
        execute_query(conn, query);

        printf("\nMenu berhasil diubah!\n");
    } else
        printf("\nTidak ada entry yang berubah\n");
    printf("============================================\n");
    printf("Tekan Enter untuk kembali...\n");
    fflush(stdin);
    while (getchar() != '\n');

    disconnect_db(conn);
}

void lihat_menu() {
    MYSQL *conn = mysql_init(NULL);
    connect_db(conn);

    system(CLEAR);
    printf("\n============================================\n");
    printf("               Edit Menu\n");
    printf("============================================\n");

    printf("  Daftar Menu:\n");
    MYSQL_RES *result = fetch_query(conn, "SELECT MenuID, NamaMenu, HargaMenu FROM Menu");
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        printf("   [%s] %s : %s\n", row[0], row[1], row[2]);
    }
    mysql_free_result(result);
    printf("============================================\n");
    printf("Tekan Enter untuk kembali...\n");
    fflush(stdin);
    while (getchar() != '\n');

    disconnect_db(conn);
}

void delete_menu() {
    MYSQL *conn = mysql_init(NULL);
    connect_db(conn);

    system(CLEAR);
    printf("\n============================================\n");
    printf("               Delete Menu\n");
    printf("============================================\n");

    printf("  Daftar Menu:\n");
    MYSQL_RES *result = fetch_query(conn, "SELECT MenuID, NamaMenu, HargaMenu FROM Menu");
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        printf("   [%s] %s : %s\n", row[0], row[1], row[2]);
    }
    mysql_free_result(result);
    printf("--------------------------------------------\n\n");

    int menuID;
    printf("Pilih nomor menu yang akan delete: ");
    scanf("%d", &menuID);

    char query[256];
    sprintf(query, "Delete from Menu WHERE MenuID=%d;", menuID);
    execute_query(conn, query);

    printf("============================================\n");
    printf("Tekan Enter untuk kembali...\n");
    fflush(stdin);
    while (getchar() != '\n');

    disconnect_db(conn);
}