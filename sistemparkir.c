#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// =====================================
// STRUCT KENDARAAN
// =====================================
typedef struct Kendaraan {
    char plat[20];
    char jenis[20];

    int prioritas;

    char waktuMasuk[10];
    char waktuKeluar[10];

    int status; // 1 = parkir, 0 = keluar

    struct Kendaraan *next;
} Kendaraan;

// =====================================
// PRIORITY STACK
// =====================================
typedef struct {
    Kendaraan data[MAX];
    int top;
} PriorityStack;

// =====================================
// TEMPORARY STACK
// =====================================
typedef struct {
    Kendaraan data[MAX];
    int top;
} TempStack;

// =====================================
// GLOBAL
// =====================================
PriorityStack parkir;
TempStack sementara;

Kendaraan *head = NULL;

// =====================================
// INISIALISASI STACK
// =====================================
void initStack() {
    parkir.top = -1;
    sementara.top = -1;
}

// =====================================
// KONVERSI JAM -> MENIT
// =====================================
int konversiMenit(char waktu[]) {
    int jam, menit;
    sscanf(waktu, "%d:%d", &jam, &menit);
    return (jam * 60) + menit;
}

// =====================================
// HITUNG DURASI
// =====================================
int hitungDurasi(char masuk[], char keluar[]) {
    int totalMasuk = konversiMenit(masuk);
    int totalKeluar = konversiMenit(keluar);
    return totalKeluar - totalMasuk;
}

// =====================================
// FORMAT DURASI
// =====================================
void tampilDurasi(int totalMenit) {
    int jam = totalMenit / 60;
    int menit = totalMenit % 60;

    if (jam > 0) {
        printf("%d jam %d menit", jam, menit);
    }
    else {
        printf("%d menit", menit);
    }
}

// =====================================
// PUSH PRIORITY STACK
// mode:
// 1 = kendaraan baru masuk
// 2 = kembali dari temp stack
// =====================================
void pushPriority(Kendaraan k, int mode) {
    if (parkir.top == MAX - 1) {
        printf("Parkiran penuh!\n");
        return;
    }

    int i = parkir.top;

    // PRIORITAS BESAR DI TOP STACK
    while (i >= 0 &&
           parkir.data[i].prioritas > k.prioritas) {

        parkir.data[i + 1] = parkir.data[i];
        i--;
    }

    parkir.data[i + 1] = k;
    parkir.top++;

    if (mode == 1) {
        printf("Kendaraan %s masuk ke Priority Stack\n",
               k.plat);
    }
    else if (mode == 2) {
        printf("Kendaraan %s dikembalikan ke Priority Stack\n",
               k.plat);
    }
}

// =====================================
// POP PRIORITY STACK
// =====================================
Kendaraan popPriority() {
    return parkir.data[parkir.top--];
}

// =====================================
// PUSH TEMP STACK
// =====================================
void pushTemp(Kendaraan k) {
    sementara.data[++sementara.top] = k;
    printf("Kendaraan %s dipindahkan ke Temporary Stack\n", k.plat);
}

// =====================================
// POP TEMP STACK
// =====================================
Kendaraan popTemp() {
    return sementara.data[sementara.top--];
}

// =====================================
// TAMBAH LINKED LIST
// =====================================
void tambahLinkedList(Kendaraan k) {

    Kendaraan *baru =
        (Kendaraan*) malloc(sizeof(Kendaraan));

    *baru = k;
    baru->next = NULL;

    if (head == NULL) {
        head = baru;
    }
    else {
        Kendaraan *temp = head;

        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = baru;
    }
}

// =====================================
// KENDARAAN MASUK
// =====================================
void kendaraanMasuk() {
    Kendaraan k;

    printf("\n=== INPUT KENDARAAN ===\n");

    printf("Nomor Plat         : ");
    scanf(" %19s", k.plat);

    printf("Jenis Kendaraan    : ");
    scanf(" %19s", k.jenis);

    printf("Prioritas (1-10)   : ");
    scanf(" %d", &k.prioritas);

    printf("Waktu Masuk (HH:MM): ");
    scanf(" %9s", k.waktuMasuk);

    strcpy(k.waktuKeluar, "-");

    k.status = 1;

    pushPriority(k, 1);

    tambahLinkedList(k);
}

// =====================================
// KENDARAAN KELUAR
// =====================================
void kendaraanKeluar() {
    char target[20];
    int ditemukan = 0;

    if (parkir.top == -1) {
        printf("Parkiran kosong.\n");
        return;
    }

    printf("\nMasukkan plat kendaraan keluar : ");
    scanf(" %19s", target);

    while (parkir.top != -1) {
        Kendaraan k = popPriority();

        if (strcmp(k.plat, target) == 0) {
            ditemukan = 1;

            printf("Waktu Keluar (HH:MM): ");
            scanf(" %9s", k.waktuKeluar);

            k.status = 0;

            // UPDATE LINKED LIST
            Kendaraan *curr = head;

            while (curr != NULL) {
                if (strcmp(curr->plat, target) == 0
                    && curr->status == 1) {

                    curr->status = 0;

                    strcpy(curr->waktuKeluar,
                           k.waktuKeluar);

                    break;
                }
                curr = curr->next;
            }

            printf("\nKendaraan %s berhasil keluar\n",
                   k.plat);

            break;
        }
        else {

            pushTemp(k);
        }
    }

    // KEMBALIKAN KE STACK UTAMA
    while (sementara.top != -1) {
        pushPriority(popTemp(), 2);
    }

    if (!ditemukan) {
        printf("Kendaraan tidak ditemukan.\n");
    }
}

// =====================================
// TAMPILKAN DATA
// =====================================
void tampilData() {
    Kendaraan *curr = head;

    if (curr == NULL) {
        printf("Data kosong.\n");
        return;
    }

    printf("\n=== DATA KENDARAAN ===\n");
    while (curr != NULL) {

        printf("--------------------------------\n");

        printf("Plat            : %s\n",
               curr->plat);

        printf("Jenis           : %s\n",
               curr->jenis);

        printf("Prioritas       : %d\n",
               curr->prioritas);

        printf("Waktu Masuk     : %s\n",
               curr->waktuMasuk);

        if (curr->status == 0) {

            int durasi =
                hitungDurasi(
                    curr->waktuMasuk,
                    curr->waktuKeluar
                );

            printf("Waktu Keluar    : %s\n",
                   curr->waktuKeluar);

            printf("Durasi Parkir   : ");

            tampilDurasi(durasi);
            printf("\n");

            printf("Status          : Keluar\n");
        }
        else {
            printf("Status          : Masih Parkir\n");
        }
        curr = curr->next;
    }
}

// =====================================
// LINEAR SEARCH
// =====================================
void cariKendaraan() {
    char target[20];
    int ditemukan = 0;

    printf("\nMasukkan plat kendaraan : ");
    scanf(" %19s", target);

    Kendaraan *curr = head;

    while (curr != NULL) {
        if (strcmp(curr->plat, target) == 0) {
            ditemukan = 1;

            printf("\n=== DATA DITEMUKAN ===\n");

            printf("Plat            : %s\n",
                   curr->plat);

            printf("Jenis           : %s\n",
                   curr->jenis);

            printf("Prioritas       : %d\n",
                   curr->prioritas);

            printf("Waktu Masuk     : %s\n",
                   curr->waktuMasuk);

            if (curr->status == 0) {
                int durasi =
                    hitungDurasi(
                        curr->waktuMasuk,
                        curr->waktuKeluar
                    );

                printf("Waktu Keluar    : %s\n",
                       curr->waktuKeluar);

                printf("Durasi Parkir   : ");

                tampilDurasi(durasi);
                printf("\n");
            }
            else {
                printf("Status          : Masih Parkir\n");
            }
            break;
        }
        curr = curr->next;
    }

    if (!ditemukan) {
        printf("Data tidak ditemukan.\n");
    }
}

// =====================================
// SWAP QUICK SORT
// =====================================
void swap(Kendaraan *a, Kendaraan *b) {
    Kendaraan temp = *a;
    *a = *b;
    *b = temp;
}

// =====================================
// PARTITION QUICK SORT
// =====================================
int partition(Kendaraan arr[],
              int low,
              int high) {

    int pivot =
        hitungDurasi(
            arr[high].waktuMasuk,
            arr[high].waktuKeluar
        );

    int i = low - 1;

    for (int j = low; j < high; j++) {
        int durasi =
            hitungDurasi(
                arr[j].waktuMasuk,
                arr[j].waktuKeluar
            );

        if (durasi < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// =====================================
// QUICK SORT
// =====================================
void quickSort(Kendaraan arr[],
               int low,
               int high) {

    if (low < high) {
        int pi =
            partition(arr, low, high);

        quickSort(arr, low, pi - 1);

        quickSort(arr, pi + 1, high);
    }
}

// =====================================
// SORTING DURASI
// =====================================
void urutDurasi() {
    Kendaraan arr[MAX];
    int n = 0;
    Kendaraan *curr = head;

    while (curr != NULL) {
        if (curr->status == 0) {
            arr[n++] = *curr;
        }
        curr = curr->next;
    }

    if (n == 0) {
        printf("Belum ada kendaraan keluar.\n");
        return;
    }
    
    quickSort(arr, 0, n - 1);
    printf("\n=== DATA TERURUT BERDASARKAN DURASI ===\n");

    for (int i = 0; i < n; i++) {
        int durasi =
            hitungDurasi(
                arr[i].waktuMasuk,
                arr[i].waktuKeluar
            );

        printf("%s - ",
               arr[i].plat);

        tampilDurasi(durasi);
        printf("\n");
    }
}

// =====================================
// MENU
// =====================================
void menu() {
    printf("\n");
    printf("====================================\n");
    printf(" SISTEM MANAJEMEN PARKIR FMIPA\n");
    printf("====================================\n");

    printf("1. Kendaraan Masuk\n");
    printf("2. Kendaraan Keluar\n");
    printf("3. Tampilkan Data\n");
    printf("4. Cari Kendaraan\n");
    printf("5. Urutkan Durasi Parkir\n");
    printf("0. Keluar\n");

    printf("====================================\n");

    printf("Pilih menu : ");
}

// =====================================
// MAIN
// =====================================
int main() {
    initStack();
    int pilihan;

    do {
        menu();
        scanf(" %d", &pilihan);

        switch (pilihan) {
            case 1:
                kendaraanMasuk();
                break;

            case 2:
                kendaraanKeluar();
                break;

            case 3:
                tampilData();
                break;

            case 4:
                cariKendaraan();
                break;

            case 5:
                urutDurasi();
                break;

            case 0:
                printf("Program selesai.\n");
                break;

            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 0);
    return 0;
}
