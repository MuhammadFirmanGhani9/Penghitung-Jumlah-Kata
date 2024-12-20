/* Nama File          : PJBL.c
   Programmer         : Muhammad Firman Ghani / 24343061
   Tanggal Pengkodean : Jumat, 29 November 2024
   Deskripsi          : Program ini menghitung jumlah kata dalam teks
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_BUFFER 1024

// Fungsi untuk menghitung jumlah kata dalam teks
int hitungKata(const char *teks) {
    int count = 0, i = 0;
    int panjang = strlen(teks);

    while (i < panjang) {
        // Mengabaikan spasi di awal
        while (i < panjang && isspace(teks[i])) {
            i++;
        }

        // Jika ditemukan kata (hanya huruf saja yang dihitung sebagai kata)
        if (i < panjang && isalpha(teks[i])) {
            count++;
            while (i < panjang && isalpha(teks[i])) {
                i++;
            }
        } else {
            i++;
        }
    }

    return count;
}

// Fungsi untuk membaca teks dari file dan menghitung kata
int hitungKataDariFile(const char *namaFile) {
    FILE *file = fopen(namaFile, "r");
    if (file == NULL) {
        printf("Gagal membuka file: %s\n", namaFile);
        return -1;
    }

    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Gagal membuka file output.txt\n");
        fclose(file);
        return -1;
    }

    char kalimat[MAX_BUFFER];
    int totalKata = 0;

    // Membaca setiap baris dari file input dan memproses operasinya
    while (fgets(kalimat, sizeof(kalimat), file)) {
        int kataPerBaris = hitungKata(kalimat);

        // Output format sesuai permintaan
        fprintf(outputFile, "Kalimat: %sJumlah kata: %d\n\n", kalimat, kataPerBaris);

        totalKata += kataPerBaris;
    }

    fclose(file);
    fclose(outputFile);
    return totalKata;
}

// Fungsi utama
int main() {
    int pilihan;
    char ulang;

    printf("________________________________________________________________________________________________________________________\n");
    printf("\t\t\t\t Nama                : Muhammad Firman Ghani\n");
    printf("\t\t\t\t NIM                 : 24343061\n");
    printf("\t\t\t\t Prodi               : Informatika\n");
    printf("\t\t\t\t Tugas               : PJBL\n");
    printf("\t\t\t\t Mata Kuliah         : Fundamental Pemograman\n");
    printf("\t\t\t\t Deskripsi           : Program Penghitung Jumlah Kata\n");
    printf("________________________________________________________________________________________________________________________\n\n");

    do {
        printf("\n\nSilakan pilih menu berikut:\n\n");
        printf("1. Hitung kata dari teks\n");
        printf("2. Hitung kata dari file\n");
        printf("3. Keluar\n\n");
        printf("Pilih menu (1/2/3): ");
        scanf("%d", &pilihan);

        getchar(); // Membersihkan newline dari buffer input

        if (pilihan == 1) {
            char teks[MAX_BUFFER];
            printf("Masukkan teks: ");
            fgets(teks, MAX_BUFFER, stdin);

            clock_t start = clock();
            int jumlahKata = hitungKata(teks);
            clock_t end = clock();

            double waktuProses = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Jumlah kata: %d\n", jumlahKata);
            printf("Waktu proses: %.6f detik\n", waktuProses);

        } else if (pilihan == 2) {
            char namaFile[MAX_BUFFER];
            printf("Masukkan nama file: ");
            fgets(namaFile, MAX_BUFFER, stdin);

            // Menghapus newline di akhir nama file
            namaFile[strcspn(namaFile, "\n")] = 0;

            clock_t start = clock();
            int jumlahKata = hitungKataDariFile(namaFile);
            clock_t end = clock();

            if (jumlahKata != -1) {
                printf("Jumlah kata dalam file berhasil dihitung dan disimpan di output.txt\n");
            }

            double waktuProses = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Waktu proses: %.6f detik\n", waktuProses);

        } else if (pilihan == 3) {
            printf("Keluar dari program.\n");
            break; // Keluar dari loop
        } else {
            printf("Pilihan tidak valid.\n");
        }

        // Tanya apakah ingin mengulang, termasuk setelah pilihan tidak valid
        printf("Apakah Anda ingin kembali ke menu utama? (Y/N): ");
        scanf(" %c", &ulang);
        getchar(); // Membersihkan newline dari buffer input
    } while (ulang == 'Y' || ulang == 'y');

    printf("Program selesai. Terima kasih telah menggunakan!\n");
    return 0;
}

