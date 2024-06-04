#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

#include "../database.h"
#include "../multiplatform.h"
extern char namaKaryawan[30];

void lihat_riwayat()
{
    MYSQL *conn = mysql_init(NULL);
    connect_db(conn);

    system(CLEAR);
    logo();
    printf("\t\t\t\t\tLogin Sebagai : %s\n", namaKaryawan);
    printf("\t\t\t\t\t========================================\n");
    printf("\t\t\t\t\t            Riwayat Pemesanan           \n");
    printf("\t\t\t\t\t========================================\n");

    MYSQL_RES *result = fetch_query(conn, "SELECT PesananID, NamaPelanggan, Timestamp, MetodePembayaran, Status, TotalHarga FROM Pesanan");
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        printf("\t\t\t\t\t%s. %s\n", row[0], row[1]);
        printf("\t\t\t\t\t   Tanggal/Waktu: %s\n", row[2]);
        printf("\t\t\t\t\t   Metode Pembayaran: %s\n", row[3]);
        printf("\t\t\t\t\t   Status: %s\n", row[4]);
        printf("\t\t\t\t\t   Total Harga: %s\n", row[5]);

        char query[256];
        sprintf(query, "SELECT NamaMenu, Jumlah, HargaMenu FROM Detail_Pesanan WHERE PesananID=%s", row[0]);

        MYSQL_RES *detail_result = fetch_query(conn, query);
        MYSQL_ROW detail_row;
        while ((detail_row = mysql_fetch_row(detail_result)))
        {
            printf("\t\t\t\t\t   - %s, Jumlah: %s, Harga Satuan: %s\n", detail_row[0], detail_row[1], detail_row[2]);
        }
        mysql_free_result(detail_result);
    }
    mysql_free_result(result);

    printf("\t\t\t\t\t========================================\n");
    printf("\t\t\t\t\tTekan Enter untuk kembali ke menu utama...\n");
    getchar();
    while (getchar() != '\n')
        ;

    disconnect_db(conn);
}
