#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "database.h"

void tambah_pesanan() {
    MYSQL *conn = mysql_init(NULL);
    connect_db(conn);

    int pelangganID;
    int jumlahItem;
    char metodePembayaran[20];
    int totalHarga;
    
    printf("============================================\n");
    printf("               Tambah Pesanan\n");
    printf("============================================\n");
    
    // Menampilkan daftar pelanggan
    printf("Daftar Pelanggan:\n");
    execute_query(conn, "SELECT PelangganID, Nama FROM Pelanggan");
    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        printf("%s. %s\n", row[0], row[1]);
    }
    mysql_free_result(result);

    printf("Pilih pelanggan: ");
    scanf("%d", &pelangganID);
    printf("Masukkan jumlah item yang dipesan: ");
    scanf("%d", &jumlahItem);

    int i;
    char menu[50];
    int jumlah;
    int hargaSatuan;
    char query[1024] = "";
    char queryDetail[1024], queryPesanan[1024];

    for (i = 0; i < jumlahItem; i++) {
        printf("Item %d:\n", i + 1);
        printf("  Nama menu: ");
        scanf("%s", menu);
        printf("  Jumlah: ");
        scanf("%d", &jumlah);
        printf("  Harga satuan: ");
        scanf("%d", &hargaSatuan);
        sprintf(queryDetail, "INSERT INTO Detail_Pesanan (PesananID, Menu, Jumlah, HargaSatuan) VALUES (LAST_INSERT_ID(), '%s', %d, %d);", menu, jumlah, hargaSatuan);
        strcpy(queryPesanan, queryDetail);
    }

    printf("Masukkan total harga: ");
    scanf("%d", &totalHarga);
    printf("Pilih metode pembayaran (Kartu Kredit/Tunai/Gopay/DANA/OVO): ");
    scanf("%s", metodePembayaran);

    sprintf(queryDetail, "INSERT INTO Pesanan (Timestamp, PelangganID, TotalHarga, MetodePembayaran, Status) VALUES (NOW(), %d, %d, '%s', 'Selesai');", pelangganID, totalHarga, metodePembayaran);
    strcat(query, queryDetail);
    strcat(query, queryPesanan);
    execute_query(conn, query);

    printf("Pesanan berhasil ditambahkan!\n");
    printf("============================================\n");
    printf("Tekan Enter untuk kembali ke menu utama...\n");
    getchar(); getchar(); // Untuk menangkap Enter

    disconnect_db(conn);
}
