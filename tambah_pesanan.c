#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "database.h"
int getHarga(MYSQL *, int);

void tambah_pesanan() {
    MYSQL *conn = mysql_init(NULL);
    connect_db(conn);

    int jumlahItem;
    char namaPelanggan[255], metodePembayaran[20];
    int totalHarga = 0;

    printf("\n============================================\n");
    printf("               Tambah Pesanan\n");
    printf("============================================\n");

    printf("  Daftar Menu:\n");
    execute_query(conn, "SELECT MenuID, NamaMenu, HargaMenu FROM Menu");
    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        printf("   [%s] %s : %s\n", row[0], row[1], row[2]);
    }
    mysql_free_result(result);
    printf("--------------------------------------------\n\n");

    printf("Masukkan nama pelanggan: ");
    while (getchar() != '\n');
    scanf("%[^\n]%*c", namaPelanggan);
    printf("Masukkan jumlah item yang dipesan: ");
    scanf("%d", &jumlahItem);

    int i;
    int menuID;
    int jumlah;
    int hargaSatuan;
    char query[1024] = "";
    char queryDetail[1024] = "", queryPesanan[1024];

    for (i = 0; i < jumlahItem;) {
        printf("Item %d:\n", i + 1);
        printf("  Masukkan ID Menu: ");
        scanf("%d", &menuID);
        hargaSatuan = getHarga(conn, menuID);
        if (hargaSatuan == -1) {
            printf("Menu tidak ditemukan\n\n");
            continue;
        }

        printf("  Jumlah: ");
        scanf("%d", &jumlah);
        printf("  Harga: %d\n", hargaSatuan * jumlah);
        totalHarga += hargaSatuan * jumlah;

        sprintf(queryDetail, "INSERT INTO Detail_Pesanan (PesananID, MenuID, Jumlah) VALUES (LAST_INSERT_ID(), %d, %d);", menuID, jumlah);
        strcat(queryPesanan, queryDetail);
        printf("\n");
        i++;
    }

    printf("Total harga: %d\n", totalHarga);
    printf("Pilih metode pembayaran (Kartu Kredit/Tunai/Gopay/DANA/OVO): ");
    scanf("%s", metodePembayaran);

    sprintf(queryDetail, "INSERT INTO Pesanan (Timestamp, NamaPelanggan, TotalHarga, MetodePembayaran, Status) VALUES (NOW(), '%s', %d, '%s', 'Selesai');", namaPelanggan, totalHarga, metodePembayaran);
    strcat(query, queryDetail);
    strcat(query, queryPesanan);
    execute_query(conn, query);

    printf("Pesanan berhasil ditambahkan!\n");
    printf("============================================\n");
    printf("Tekan Enter untuk kembali ke menu utama...\n");
    getchar();
    getchar();  // Untuk menangkap Enter

    disconnect_db(conn);
}

int getHarga(MYSQL *conn, int menuID) {
    int harga;
    char query[1024] = "";
    sprintf(query, "SELECT HargaMenu FROM Menu where MenuID=%d", menuID);
    execute_query(conn, query);

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row)
        harga = atoi(row[0]);
    else
        harga = -1;  // Menu tidak ditemukan

    mysql_free_result(result);
    return harga;
}
