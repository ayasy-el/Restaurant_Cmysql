#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../database.h"
#include "../multiplatform.h"
#if defined(unix)
int getch(void);
#endif

void waitForEnter()
{
    printf("\n\nTekan enter untuk kembali: ");
    getchar();
}

void login();
void waitForEnter();
void insert();
void display();
void modify();
void deleted();
char namaKaryawan[30];

int main()
{
    login(namaKaryawan);
    while (1)
    {
        int choice;
        char x;
        system(CLEAR);
        printf("\n");
        printf("\t\t\t\t\t███████╗███╗   ███╗███████╗\n");
        printf("\t\t\t\t\t██╔════╝████╗ ████║██╔════╝\n");
        printf("\t\t\t\t\t█████╗  ██╔████╔██║███████╗\n");
        printf("\t\t\t\t\t██╔══╝  ██║╚██╔╝██║╚════██║\n");
        printf("\t\t\t\t\t███████╗██║ ╚═╝ ██║███████║\n");
        printf("\t\t\t\t\t╚══════╝╚═╝     ╚═╝╚══════╝\n");
        printf("\t\t\t\t\tEmployee Management Systems\n");
        printf("\t\t\t\t\t       v.1.2 ©Tribone      \n");
        printf("\n");
        printf("\t\t\t\t\t---------------------------\n");
        printf("\t\t\t\t\t Selamat Datang %s !\n", namaKaryawan);
        printf("\t\t\t\t\t---------------------------\n");
        printf("\t\t\t\t\t 1. Tambah Karyawan\n");
        printf("\t\t\t\t\t 2. Edit Karyawan\n");
        printf("\t\t\t\t\t 3. Hapus Karyawan\n");
        printf("\t\t\t\t\t 4. Tampilkan Karyawan\n");
        printf("\t\t\t\t\t 5. Keluar\n");
        printf("\t\t\t\t\t---------------------------\n");
        printf("\t\t\t\t\t Pilih Opsi: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            do
            {
                insert();
                printf("\n\n\t\t\t Tambah Karyawan Lagi? (Y/N): ");
                scanf(" %c", &x);
            } while (x == 'y' || x == 'Y');
            waitForEnter();
            break;
        case 2:
            modify();
            break;
        case 3:
            deleted();
            break;
        case 4:
            display();
            break;
        case 5:
            printf("\t\t\t\t\t---------------------------\n");
            printf("\t\t\t\t\t Keluar dari Aplikasi EMS  \n");
            printf("\t\t\t\t\t---------------------------\n");
            SLEEP(1000);
            exit(0);
        default:
            printf("\n\n\t\t\t Pilihan Tidak Valid... Silakan Coba Lagi...\n");
        }
        getch();
    }
    return 0;
}
