#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../database.h"
#include "../multiplatform.h"
#if defined(unix)
int getch(void);
#endif

void waitForEnter() {
    printf("\n\nTekan enter untuk kembali: ");
    getchar();
    getchar();
}

void login();
void waitForEnter();
void insert();
void display();
void modify();
void deleted();

int main() {
    login();
    while (1) {
        int choice;
        char x;
        system(CLEAR);
        printf("\n\t\t\t\t\t-------------------------------\n");
        printf("\t\t\t\t\t>> EMPLOYEE MANAGEMENT SYSTEM <<\n");
        printf("\t\t\t\t\t-------------------------------\n");
        printf("\t\t\t\t\t 1. Tambah Karyawan\n");
        printf("\t\t\t\t\t 2. Edit Karyawan\n");
        printf("\t\t\t\t\t 3. Hapus Karyawan\n");
        printf("\t\t\t\t\t 4. Tampilkan Semua Karyawan\n");
        printf("\t\t\t\t\t 5. Keluar\n");
        printf("\t\t\t\t\t--------------------------------\n");
        printf(" Pilih Opsi: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                do {
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
                system(CLEAR);
                printf("\n\t\t\t>> EMPLOYEE MANAGEMENT SYSTEM <<\n\n");
                SLEEP(1000);
                exit(0);
            default:
                printf("\n\n\t\t\t Pilihan Tidak Valid... Silakan Coba Lagi...\n");
        }
        getch();
    }
    return 0;
}
