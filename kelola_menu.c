#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "database.h"

void tambah_menu() {
    MYSQL *conn = mysql_init(NULL);
    connect_db(conn);

    int hargaMenu;
    char namaMenu[120];

    printf("\n============================================\n");
    printf("               Tambah Menu\n");
    printf("============================================\n");

    printf("Masukkan Nama menu: ");
    while (getchar() != '\n');
    scanf("%[^\n]%*c", namaMenu);

    printf("Masukkan Harga menu: ");
    scanf("%d", &hargaMenu);

    char query[256];
    sprintf(query, "INSERT INTO Menu (NamaMenu, HargaMenu) VALUES ('%s', %d)", namaMenu, hargaMenu);
    execute_query(conn, query);

    printf("Pelanggan berhasil ditambahkan!\n");
    printf("============================================\n");
    printf("Tekan Enter untuk kembali ke menu utama...\n");
    getchar();
    getchar();  // Untuk menangkap Enter

    disconnect_db(conn);
}