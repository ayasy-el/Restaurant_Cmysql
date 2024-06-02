#include <stdio.h>
#include <stdlib.h>

#include "../multiplatform.h"

void tambah_pesanan();
void lihat_menu();
void tambah_menu();
void edit_menu();
void delete_menu();
void lihat_riwayat();
void kelola_menu();
void login();

int main() {
    system(CLEAR);
    login();
    int pilihan;

    while (1) {
        printf("\n============================================\n");
        printf("   Selamat Datang di Sistem Pemesanan Restoran\n");
        printf("============================================\n");
        printf("1. Tambah Pesanan\n");
        printf("2. Kelola Menu\n");
        printf("3. Lihat Riwayat Pemesanan\n");
        printf("4. Keluar\n");
        printf("============================================\n");
        printf("Pilih opsi (1-4): ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tambah_pesanan();
                break;
            case 2:
                kelola_menu();
                break;
            case 3:
                lihat_riwayat();
                break;
            case 4:
                printf("============================================\n");
                printf("      Terima Kasih telah menggunakan\n");
                printf("          Sistem Pemesanan Restoran\n");
                printf("============================================\n");
                exit(0);
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
                while (getchar() != '\n');
                break;
        }
    }

    return 0;
}

void kelola_menu() {
    int pilihan;
    while (1) {
        printf("\n============================================\n");
        printf("               Kelola Menu\n");
        printf("============================================\n");
        printf("1. Lihat Menu\n");
        printf("2. Tambah Menu\n");
        printf("3. Edit Menu\n");
        printf("4. Delete Menu\n");
        printf("5. Back\n");
        printf("============================================\n");
        printf("Pilih opsi (1-4): ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                lihat_menu();
                break;
            case 2:
                tambah_menu();
                break;
            case 3:
                edit_menu();
                break;
            case 4:
                delete_menu();
                break;
            case 5:
                printf("============================================\n\n");
                return;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    }
}