#include <stdio.h>
#include <stdlib.h>

void tambah_pesanan();
void tambah_menu();
void edit_menu();
void delete_menu();
void lihat_riwayat();
void kelola_menu();

int main() {
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
    printf("\n============================================\n");
    printf("               Kelola Menu\n");
    printf("============================================\n");
    printf("1. Tambah Menu\n");
    printf("2. Edit Menu\n");
    printf("3. Delete Menu\n");
    printf("4. Back\n");
    printf("============================================\n");
    printf("Pilih opsi (1-4): ");
    scanf("%d", &pilihan);

    switch (pilihan) {
        case 1:
            tambah_menu();
            break;
        case 2:
            edit_menu();
            break;
        case 3:
            delete_menu();
            break;
        case 4:
            printf("============================================\n");
            printf("Tekan Enter untuk kembali ke menu utama...\n");
            getchar();
            getchar();
            break;
        default:
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
    }
}

// ! Harus Diimplementasikan
// ! Lalu Hapus
void edit_menu() {}
void delete_menu() {}
