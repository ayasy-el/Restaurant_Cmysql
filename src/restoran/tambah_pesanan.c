#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../database.h"
#include "../multiplatform.h"
int getHarga(MYSQL *, int);
void cetakNota();
void logo();

int jumlahItem;
char namaPelanggan[255], metodePembayaran[20];
int totalHarga = 0;
extern char namaKaryawan[30];

void tambah_pesanan()
{
    MYSQL *conn = mysql_init(NULL);
    connect_db(conn);

    system(CLEAR);
    logo();
    printf("\t\t\t\t\tLogin Sebagai : %s\n", namaKaryawan);
    printf("\t\t\t\t\t========================================\n");
    printf("\t\t\t\t\t             Tambah Pesanan             \n");
    printf("\t\t\t\t\t========================================\n");

    printf("\t\t\t\t\tDaftar Menu:\n");
    MYSQL_RES *result = fetch_query(conn, "SELECT MenuID, NamaMenu, HargaMenu FROM Menu");
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        printf("\t\t\t\t\t[%s] %s : %s\n", row[0], row[1], row[2]);
    }
    printf("\t\t\t\t\t========================================\n");
    if (mysql_num_rows(result) == 0)
    {
        printf("\t\t\t\t\t             Tambahkan Menu             \n");
        printf("\t\t\t\t\t             Terlebih dahulu            \n");
        printf("\t\t\t\t\t========================================\n");
        printf("\t\t\t\t\t       Tekan Enter untuk kembali        \n");
        printf("\t\t\t\t\t            ke menu utama...            \n");
        getchar();
        while (getchar() != '\n')
            ;

        disconnect_db(conn);
        return;
    }
    mysql_free_result(result);

    printf("\t\t\t\t\tMasukkan nama pelanggan: ");
    while (getchar() != '\n')
        ;
    scanf("%[^\n]%*c", namaPelanggan);
    printf("\t\t\t\t\t========================================\n");
    printf("\t\t\t\t\tMasukkan jumlah item yang dipesan: ");
    scanf("%d", &jumlahItem);

    int jumlah[50], menuID[50], hargaSatuan[50];
    char queryDetail[2048] = "";

    totalHarga = 0;
    for (int i = 0; i < jumlahItem;)
    {
        printf("\t\t\t\t\tItem %d:\n", i + 1);
        printf("\t\t\t\t\tMasukkan ID Menu: ");
        scanf("%d", &menuID[i]);
        hargaSatuan[i] = getHarga(conn, menuID[i]);
        if (hargaSatuan[i] == -1)
        { // tidak dapat id
            printf("\n\t\t\t\t\tMenu tidak ditemukan!\n\n");
            continue;
        }

        printf("\t\t\t\t\tJumlah: ");
        scanf("%d", &jumlah[i]);
        printf("\t\t\t\t\tHarga: %d\n", hargaSatuan[i] * jumlah[i]);
        totalHarga += hargaSatuan[i] * jumlah[i];

        printf("\n");
        i++;
    }

    printf("\t\t\t\t\tTotal harga: Rp. %d\n", totalHarga);
    printf("\t\t\t\t\tPilih metode pembayaran (Kartu Kredit/Tunai/Gopay/DANA/OVO): ");
    scanf("%s", metodePembayaran);

    sprintf(queryDetail, "INSERT INTO Pesanan (Timestamp, NamaPelanggan, TotalHarga, MetodePembayaran, Status) VALUES (NOW(), '%s', %d, '%s', 'Selesai');", namaPelanggan, totalHarga, metodePembayaran);
    execute_query(conn, queryDetail);

    int pesananID;
    MYSQL_RES *resultID = fetch_query(conn, "SELECT PesananID, Timestamp FROM Pesanan WHERE PesananID=(SELECT MAX(PesananID) FROM Pesanan);"); // Mengambil ID terakhir & Timestamp
    MYSQL_ROW rowID = mysql_fetch_row(resultID);
    if (rowID == NULL)
        pesananID = 0;
    else
        pesananID = atoi(rowID[0]);
    mysql_free_result(resultID);

    for (int i = 0; i < jumlahItem; i++)
    {
        sprintf(queryDetail, "SELECT NamaMenu FROM Menu where MenuID=%d", menuID[i]);
        MYSQL_RES *resultMenu = fetch_query(conn, queryDetail); // Mengambil ID terakhir & Timestamp
        MYSQL_ROW rowMenu = mysql_fetch_row(resultMenu);

        sprintf(queryDetail, "INSERT INTO Detail_Pesanan (PesananID, NamaMenu, Jumlah, HargaMenu ) VALUES (%d, '%s', %d, %d);", pesananID, rowMenu[0], jumlah[i], hargaSatuan[i]);
        execute_query(conn, queryDetail);

        mysql_free_result(resultMenu);
    }
    printf("\n");
    printf("\t\t\t\t\t========================================\n");
    printf("\t\t\t\t\t     Pesanan berhasil ditambahkan!      \n");
    printf("\t\t\t\t\t========================================\n");
    cetakNota();
    printf("\t\t\t\t\t========================================\n");
    printf("\t\t\t\t\tTekan Enter untuk kembali ke menu utama \n");
    getchar();
    while (getchar() != '\n')
        ;

    disconnect_db(conn);
}

int getHarga(MYSQL *conn, int menuID)
{
    int harga;
    char query[1024] = "";
    sprintf(query, "SELECT HargaMenu FROM Menu where MenuID=%d", menuID);
    execute_query(conn, query);

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row)
        harga = atoi(row[0]);
    else
        harga = -1; // Menu tidak ditemukan

    mysql_free_result(result);
    return harga;
}

void cetakNota()
{
    MYSQL *conn = mysql_init(NULL);
    connect_db(conn);
    char query[1024] = "";

    execute_query(conn, "SELECT PesananID, Timestamp FROM Pesanan WHERE PesananID = (SELECT MAX(PesananID) FROM Pesanan);"); // Mengambil ID terakhir & Timestamp
    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL)
    {
        fprintf(stderr, "No orders found\n");
        mysql_free_result(result);
        return;
    }
    int id = atoi(row[0]);
    system(CLEAR);
    printf("\n\t\t\t\t================================================\n");
    printf("\t\t\t\t              NOTA PEMBELIAN            \n");
    printf("\t\t\t\t================================================\n");
    printf("\t\t\t\t  Pembeli\t\t: %s\n", namaPelanggan);
    printf("\t\t\t\t  Tanggal/Waktu\t\t: %s\n", row[1]);
    printf("\t\t\t\t  Metode Pembayaran\t: %s\n", metodePembayaran);
    printf("\t\t\t\t  Status\t\t: %s\n", "Terbayar");
    printf("\t\t\t\t------------------------------------------------\n");
    printf("\t\t\t\t  Detail Pesanan :           \n\n");
    printf("\t\t\t\t Nama Item    Jumlah\tHarga Satuan\tTotal\n");
    printf("\t\t\t\t------------------------------------------------\n");

    mysql_free_result(result); // Membebaskan hasil setelah digunakan
    sprintf(query, "SELECT NamaMenu, Jumlah, HargaMenu FROM Detail_Pesanan WHERE PesananID=%d", id);
    MYSQL_RES *detail_result = fetch_query(conn, query);
    MYSQL_ROW detail_row;
    while ((detail_row = mysql_fetch_row(detail_result)))
    {
        printf("\t\t\t\t %s \t %s\t   %s\t%d\n", detail_row[0], detail_row[2], detail_row[1], atoi(detail_row[2]) * atoi(detail_row[1]));
    }
    printf("\t\t\t\t------------------------------------------------\n");
    printf("\n\t\t\t\t\t  Total Harga: Rp. %d\n", totalHarga);
    printf("\t\t\t\t================================================\n");
    printf("\t\t\t\t    Terima Kasih atas Kunjungan Anda    \n");
    printf("\t\t\t\t================================================\n");
    mysql_free_result(detail_result);
}