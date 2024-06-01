#include <stdio.h>
#include <stdlib.h>

void tambah_pesanan();
void tambah_menu();
void lihat_riwayat();

int main() {
    int pilihan;

    while (1) {
        printf("============================================\n");
        printf("   Selamat Datang di Sistem Pemesanan Restoran\n");
        printf("============================================\n");
        printf("1. Tambah Pesanan\n");
        printf("2. Tambah Menu\n");
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
                tambah_menu();
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
        }
    }

    return 0;
}
