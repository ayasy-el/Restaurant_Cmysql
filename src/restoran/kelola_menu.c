#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../database.h"
#include "../multiplatform.h"
extern char namaKaryawan[30];
void logo();

void tambah_menu()
{
    MYSQL *conn = mysql_init(NULL);
    connect_db(conn);

    int hargaMenu;
    char namaMenu[120];

    system(CLEAR);
    logo();
    printf("\t\t\t\t\tLogin Sebagai : %s\n", namaKaryawan);
    printf("\t\t\t\t\t========================================\n");
    printf("\t\t\t\t\t               Tambah Menu              \n");
    printf("\t\t\t\t\t========================================\n");

    while (1)
    {
        printf("\t\t\t\t\tMasukkan Nama menu: ");
        while (getchar() != '\n')
            ;
        scanf("%[^\n]%*c", namaMenu);
        if (strcmp(namaMenu, "") != 0)
            break;
        printf("\t\t\t\t\tNama menu tidak boleh kosong\n\n");
    }

    while (1)
    {
        printf("\t\t\t\t\tMasukkan Harga menu: ");
        scanf("%d", &hargaMenu);
        if (hargaMenu > 0)
            break;
        printf("\t\t\t\t\tHarga harus lebih dari 0\n\n");
    }

    char query[256];
    sprintf(query, "INSERT INTO Menu (NamaMenu, HargaMenu) VALUES ('%s', %d)", namaMenu, hargaMenu);
    execute_query(conn, query);

    printf("\t\t\t\t\tMenu berhasil ditambahkan!\n");
    printf("\t\t\t\t\t========================================\n");
    printf("\t\t\t\t\tTekan Enter untuk kembali...\n");
    getchar();
    while (getchar() != '\n')
        ;

    disconnect_db(conn);
}

void edit_menu()
{
    MYSQL *conn = mysql_init(NULL);
    connect_db(conn);

    int hargaMenu = -1;
    char namaMenu[120] = "";
    system(CLEAR);
    logo();
    printf("\t\t\t\t\tLogin Sebagai : %s\n", namaKaryawan);
    printf("\t\t\t\t\t========================================\n");
    printf("\t\t\t\t\t                Edit Menu               \n");
    printf("\t\t\t\t\t========================================\n");

    printf("\t\t\t\t\tDaftar Menu:\n");
    MYSQL_RES *result = fetch_query(conn, "SELECT MenuID, NamaMenu, HargaMenu FROM Menu");
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        printf("\t\t\t\t\t[%s] %s : %s\n", row[0], row[1], row[2]);
    }
    mysql_free_result(result);
    printf("\t\t\t\t\t========================================\n");

    int menuID;
    printf("\t\t\t\t\tPilih nomor menu yang akan diedit: ");
    scanf("%d", &menuID);

    printf("\n\t\t\t\t\tKosongi jika tidak ingin mengubahnya\n");
    printf("\t\t\t\t\tMasukkan Nama Menu Baru: ");
    getchar();
    scanf("%[^\n]%*c", namaMenu);

    char harga[10];
    printf("\t\t\t\t\tMasukkan Harga menu: ");
    getchar();
    scanf("%[^\n]%*c", harga);
    hargaMenu = atoi(harga);

    char query[256], setQuery[125] = "";
    if (namaMenu[0] != '\0')
        sprintf(setQuery + strlen(setQuery), "NamaMenu='%s'", namaMenu);
    if (namaMenu[0] != '\0' && hargaMenu > 0)
        sprintf(setQuery + strlen(setQuery), ", ");
    if (hargaMenu > 0)
        sprintf(setQuery + strlen(setQuery), "HargaMenu=%d", hargaMenu);

    if (namaMenu[0] != '\0' || hargaMenu > 0)
    {
        sprintf(query, "UPDATE Menu SET %s WHERE MenuID=%d;", setQuery, menuID);
        execute_query(conn, query);

        printf("\n\t\t\t\t\tMenu berhasil diubah!\n");
    }
    else
        printf("\n\t\t\t\t\tTidak ada entry yang berubah\n");
    printf("\t\t\t\t\t========================================\n");
    printf("\t\t\t\t\tTekan Enter untuk kembali...\n");
    getchar();
    while (getchar() != '\n')
        ;

    disconnect_db(conn);
}

void lihat_menu()
{
    MYSQL *conn = mysql_init(NULL);
    connect_db(conn);

    system(CLEAR);
    logo();
    printf("\t\t\t\t\tLogin Sebagai : %s\n", namaKaryawan);
    printf("\t\t\t\t\t========================================\n");
    printf("\t\t\t\t\t                Lihat Menu              \n");
    printf("\t\t\t\t\t========================================\n");

    printf("\t\t\t\t\tDaftar Menu:\n");
    MYSQL_RES *result = fetch_query(conn, "SELECT MenuID, NamaMenu, HargaMenu FROM Menu");
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        printf("\t\t\t\t\t[%s] %s : %s\n", row[0], row[1], row[2]);
    }
    mysql_free_result(result);
    printf("\t\t\t\t\t========================================\n");
    printf("\t\t\t\t\tTekan Enter untuk kembali...\n");
    getchar();
    while (getchar() != '\n')
        ;

    disconnect_db(conn);
}

void delete_menu()
{
    MYSQL *conn = mysql_init(NULL);
    connect_db(conn);

    system(CLEAR);
    logo();
    printf("\t\t\t\t\t========================================\n");
    printf("\t\t\t\t\t              Delete Menu               \n");
    printf("\t\t\t\t\t========================================\n");

    printf("\t\t\t\t\tDaftar Menu:\n");
    MYSQL_RES *result = fetch_query(conn, "SELECT MenuID, NamaMenu, HargaMenu FROM Menu");
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        printf("\t\t\t\t\t[%s] %s : %s\n", row[0], row[1], row[2]);
    }
    mysql_free_result(result);
    printf("\t\t\t\t\t========================================\n");

    int menuID;
    printf("\t\t\t\t\tPilih nomor menu yang akan delete: ");
    scanf("%d", &menuID);

    char query[256];
    sprintf(query, "Delete from Menu WHERE MenuID=%d;", menuID);
    execute_query(conn, query);

    printf("\t\t\t\t\t========================================\n");
    printf("\t\t\t\t\tTekan Enter untuk kembali...\n");
    getchar();
    while (getchar() != '\n')
        ;

    disconnect_db(conn);
}