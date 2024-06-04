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
void logo();
char namaKaryawan[30];

int main()
{
    login(namaKaryawan);
    int pilihan;

    while (1)
    {
        system(CLEAR);
        logo();
        printf("\t\t\t\t\t=========================\n");
        printf("\t\t\t\t\tSelamat Datang %s !\n", namaKaryawan);
        printf("\t\t\t\t\t=========================\n");
        printf("\t\t\t\t\t1. Tambah Pesanan\n");
        printf("\t\t\t\t\t2. Kelola Menu\n");
        printf("\t\t\t\t\t3. Riwayat Pemesanan\n");
        printf("\t\t\t\t\t4. Keluar\n");
        printf("\t\t\t\t\t=========================\n");
        printf("\t\t\t\t\tPilih opsi (1-4): ");
        scanf("%d", &pilihan);

        switch (pilihan)
        {
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
            printf("\t\t\t\t\t=========================\n");
            printf("\t\t\t\t\t  Selamat Tinggal %s \n", namaKaryawan);
            printf("\t\t\t\t\tKeluar dari Aplikasi POS.\n");
            printf("\t\t\t\t\t=========================\n");
            exit(0);
        default:
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
            while (getchar() != '\n')
                ;
            break;
        }
    }

    return 0;
}

void kelola_menu()
{
    int pilihan;
    while (1)
    {
        system(CLEAR);
        logo();
        printf("\t\t\t\t\t=========================\n");
        printf("\t\t\t\t\t       Kelola Menu       \n");
        printf("\t\t\t\t\t=========================\n");
        printf("\t\t\t\t\t1. Lihat Menu\n");
        printf("\t\t\t\t\t2. Tambah Menu\n");
        printf("\t\t\t\t\t3. Edit Menu\n");
        printf("\t\t\t\t\t4. Delete Menu\n");
        printf("\t\t\t\t\t5. Back\n");
        printf("\t\t\t\t\t=========================\n");
        printf("\t\t\t\t\tPilih opsi (1-4): ");
        scanf("%d", &pilihan);

        switch (pilihan)
        {
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
            printf("\t\t\t\t\t=========================\n");
            return;
        default:
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    }
}
void logo()
{
    printf("\n");
    printf("\t\t\t\t\t██████╗  ██████╗ ███████╗\n");
    printf("\t\t\t\t\t██╔══██╗██╔═══██╗██╔════╝\n");
    printf("\t\t\t\t\t██████╔╝██║   ██║███████╗\n");
    printf("\t\t\t\t\t██╔═══╝ ██║   ██║╚════██║\n");
    printf("\t\t\t\t\t██║     ╚██████╔╝███████║\n");
    printf("\t\t\t\t\t╚═╝      ╚═════╝ ╚══════╝\n");
    printf("\t\t\t\t\t Point of Sales Terminal \n");
    printf("\t\t\t\t\t      v.1.2 ©Tribone     \n");
    printf("\n");
}