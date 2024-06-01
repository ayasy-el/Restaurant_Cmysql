#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "database.h"

void tambah_pelanggan() {
    MYSQL *conn = mysql_init(NULL);
    connect_db(conn);

    char nama[100];
    printf("============================================\n");
    printf("               Tambah Pelanggan\n");
    printf("============================================\n");
    printf("Masukkan nama pelanggan: ");
    scanf("%s", nama);

    char query[256];
    sprintf(query, "INSERT INTO Pelanggan (Nama) VALUES ('%s')", nama);
    execute_query(conn, query);

    printf("Pelanggan berhasil ditambahkan!\n");
    printf("============================================\n");
    printf("Tekan Enter untuk kembali ke menu utama...\n");
    getchar(); getchar(); // Untuk menangkap Enter

    disconnect_db(conn);
}
