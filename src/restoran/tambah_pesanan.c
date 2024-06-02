#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../database.h"
#include "../multiplatform.h"
int getHarga(MYSQL *, int);
void cetakNota();

int jumlahItem;
char namaPelanggan[255], metodePembayaran[20];
int totalHarga = 0;

void tambah_pesanan() {
    MYSQL *conn = mysql_init(NULL);
    connect_db(conn);

    system(CLEAR);
    printf("\n============================================\n");
    printf("               Tambah Pesanan\n");
    printf("============================================\n");

    printf("  Daftar Menu:\n");
    MYSQL_RES *result = fetch_query(conn, "SELECT MenuID, NamaMenu, HargaMenu FROM Menu");
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        printf("   [%s] %s : %s\n", row[0], row[1], row[2]);
    }
    printf("--------------------------------------------\n\n");
    if (mysql_num_rows(result) == 0) {
        printf("Tambahkan Menu Terlebih dahulu\n");
        printf("============================================\n");
        printf("Tekan Enter untuk kembali ke menu utama...\n");
        fflush(stdin);
        while (getchar() != '\n');

        disconnect_db(conn);
        return;
    }
    mysql_free_result(result);

    printf("Masukkan nama pelanggan: ");
    while (getchar() != '\n');
    scanf("%[^\n]%*c", namaPelanggan);
    printf("Masukkan jumlah item yang dipesan: ");
    scanf("%d", &jumlahItem);

    int jumlah[50], menuID[50], hargaSatuan;
    char queryDetail[2048] = "";

    for (int i = 0; i < jumlahItem;) {
        printf("Item %d:\n", i + 1);
        printf("  Masukkan ID Menu: ");
        scanf("%d", &menuID[i]);
        hargaSatuan = getHarga(conn, menuID[i]);
        if (hargaSatuan == -1) {  // tidak dapat id
            printf("Menu tidak ditemukan\n\n");
            continue;
        }

        printf("  Jumlah: ");
        scanf("%d", &jumlah[i]);
        printf("  Harga: %d\n", hargaSatuan * jumlah[i]);
        totalHarga += hargaSatuan * jumlah[i];

        printf("\n");
        i++;
    }

    printf("Total harga: %d\n", totalHarga);
    printf("Pilih metode pembayaran (Kartu Kredit/Tunai/Gopay/DANA/OVO): ");
    scanf("%s", metodePembayaran);

    sprintf(queryDetail, "INSERT INTO Pesanan (Timestamp, NamaPelanggan, TotalHarga, MetodePembayaran, Status) VALUES (NOW(), '%s', %d, '%s', 'Selesai');", namaPelanggan, totalHarga, metodePembayaran);
    execute_query(conn, queryDetail);

    int pesananID;
    MYSQL_RES *resultID = fetch_query(conn, "SELECT MAX(PesananID) FROM Pesanan");  // Mengambil ID terakhir & Timestamp
    MYSQL_ROW rowID = mysql_fetch_row(resultID);
    if (rowID == NULL)
        pesananID = 0;
    else
        pesananID = atoi(rowID[0]);
    mysql_free_result(resultID);

    for (int i = 0; i < jumlahItem; i++) {
        sprintf(queryDetail, "INSERT INTO Detail_Pesanan (PesananID, MenuID, Jumlah) VALUES (%d, %d, %d);", pesananID, menuID[i], jumlah[i]);
        execute_query(conn, queryDetail);
    }

    printf("Pesanan berhasil ditambahkan!\n");
    printf("============================================\n");
    cetakNota();
    printf("============================================\n");
    printf("Tekan Enter untuk kembali ke menu utama...\n");
    fflush(stdin);
    while (getchar() != '\n');

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

void cetakNota() {
    MYSQL *conn = mysql_init(NULL);
    connect_db(conn);
    char query[1024] = "";

    execute_query(conn, "SELECT MAX(PesananID), Timestamp FROM Pesanan");  // Mengambil ID terakhir & Timestamp
    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL) {
        fprintf(stderr, "No orders found\n");
        mysql_free_result(result);
        return;
    }
    int id = atoi(row[0]);
    printf("%s. %s\n", row[0], namaPelanggan);
    printf("   Tanggal/Waktu: %s\n", row[1]);
    printf("   Metode Pembayaran: %s\n", metodePembayaran);
    printf("   Status: %s\n", "selesai");
    printf("   Total Harga: %d\n", totalHarga);

    mysql_free_result(result);  // Membebaskan hasil setelah digunakan
    sprintf(query, "SELECT b.NamaMenu, a.Jumlah, b.HargaMenu FROM Detail_Pesanan a JOIN Menu b ON a.MenuID=b.MenuID WHERE PesananID=%d", id);
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
    mysql_free_result(detail_result);  // Membebaskan hasil setelah digunakan
}