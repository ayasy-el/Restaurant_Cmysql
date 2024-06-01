#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "database.h"

void lihat_riwayat() {
    MYSQL *conn = mysql_init(NULL);
    connect_db(conn);

    printf("============================================\n");
    printf("           Riwayat Pemesanan\n");
    printf("============================================\n");

    execute_query(conn, "SELECT Pesanan.PesananID, Pelanggan.Nama, Pesanan.Timestamp, Pesanan.MetodePembayaran, Pesanan.Status, Pesanan.TotalHarga FROM Pesanan JOIN Pelanggan ON Pesanan.PelangganID = Pelanggan.PelangganID");
    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        printf("%s. %s\n", row[0], row[1]);
        printf("   Tanggal/Waktu: %s\n", row[2]);
        printf("   Metode Pembayaran: %s\n", row[3]);
        printf("   Status: %s\n", row[4]);
        printf("   Total Harga: %s\n", row[5]);

        char query[256];
        sprintf(query, "SELECT Menu, Jumlah, HargaSatuan FROM Detail_Pesanan WHERE PesananID = %s", row[0]);
        execute_query(conn, query);
        MYSQL_RES *detail_result = mysql_store_result(conn);
        if (detail_result == NULL) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        MYSQL_ROW detail_row;
        while ((detail_row = mysql_fetch_row(detail_result))) {
            printf("     - %s, Jumlah: %s, Harga Satuan: %s\n", detail_row[0], detail_row[1], detail_row[2]);
        }
        mysql_free_result(detail_result);
    }
    mysql_free_result(result);

    printf("============================================\n");
    printf("Tekan Enter untuk kembali ke menu utama...\n");
    getchar(); getchar(); // Untuk menangkap Enter

    disconnect_db(conn);
}
