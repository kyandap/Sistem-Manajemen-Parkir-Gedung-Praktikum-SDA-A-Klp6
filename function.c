#include "header.h"

// (Alokasi Variabel Global & Inisialisasi)
PriorityStack parkir;
TempStack sementara;
Kendaraan *head = NULL;

void initStack() {
    parkir.top = -1;
    sementara.top = -1;
}

// Konversi Menit
int konversiMenit(char waktu[]) {
    int jam, menit;
    sscanf(waktu, "%d:%d", &jam, &menit);
    return (jam * 60) + menit;
}

int hitungDurasi(char masuk[], char keluar[]) {
    int totalMasuk = konversiMenit(masuk);
    int totalKeluar = konversiMenit(keluar);
    return totalKeluar - totalMasuk;
}

void tampilDurasi(int totalMenit) {
    int jam = totalMenit / 60;
    int menit = totalMenit % 60;
    if (jam > 0) {
        printf("%d jam %d menit", jam, menit);
    } else {
        printf("%d menit", menit);
    }
}

// Push Priority Stack
// 1 = kendaraan baru masuk
// 2 = kembali dari temp stack
void pushPriority(Kendaraan k, int mode) {
    if (parkir.top == MAX - 1) {
        printf("Parkiran penuh!\n");
        return;
    }
    int i = parkir.top;
    while (i >= 0 && parkir.data[i].prioritas > k.prioritas) {
        parkir.data[i + 1] = parkir.data[i];
        i--;
    }
    parkir.data[i + 1] = k;
    parkir.top++;

    if (mode == 1) {
        printf("Kendaraan %s masuk ke Priority Stack\n", k.plat);
    } else if (mode == 2) {
        printf("Kendaraan %s dikembalikan ke Priority Stack\n", k.plat);
    }
}

// Pop Priority Stack
Kendaraan popPriority() {
    return parkir.data[parkir.top--];
}
