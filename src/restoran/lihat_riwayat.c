#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

#include "../database.h"
#include "../multiplatform.h"

// TODO: Riwayat masih terpengaruh update edit menu
// * tambahkan harga menu di Detail_Pesanan
void lihat_riwayat() {
    MYSQL *conn = mysql_init(NULL);
    connect_db(conn);

    system(CLEAR);
    printf("\n============================================\n");
    printf("           Riwayat Pemesanan\n");
    printf("============================================\n");

    MYSQL_RES *result = fetch_query(conn, "SELECT PesananID, NamaPelanggan, Timestamp, MetodePembayaran, Status, TotalHarga FROM Pesanan");
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        printf("%s. %s\n", row[0], row[1]);
        printf("   Tanggal/Waktu: %s\n", row[2]);
        printf("   Metode Pembayaran: %s\n", row[3]);
        printf("   Status: %s\n", row[4]);
        printf("   Total Harga: %s\n", row[5]);

        char query[256];
        sprintf(query, "SELECT COALESCE(m.NamaMenu, rm.NamaMenu) AS NamaMenu, dp.Jumlah, COALESCE(m.HargaMenu, rm.HargaMenu) AS HargaMenu FROM Detail_Pesanan dp LEFT JOIN Menu m ON dp.MenuID = m.MenuID LEFT JOIN Removed_Menu rm ON dp.MenuID = rm.MenuID WHERE dp.PesananID=%s", row[0]);

        MYSQL_RES *detail_result = fetch_query(conn, query);
        MYSQL_ROW detail_row;
        while ((detail_row = mysql_fetch_row(detail_result))) {
            printf("     - %s, Jumlah: %s, Harga Satuan: %s\n", detail_row[0], detail_row[1], detail_row[2]);
        }
        mysql_free_result(detail_result);
    }
    mysql_free_result(result);

    printf("============================================\n");
    printf("Tekan Enter untuk kembali ke menu utama...\n");
    fflush(stdin);
    while (getchar() != '\n');

    disconnect_db(conn);
}
