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

//Fungsi untuk memasukkan kendaraan ke tumpukan evakuasi/sementara
void pushTemp(Kendaraan k) {
    sementara.data[++sementara.top] = k;
    printf("Kendaraan %s dipindahkan ke Temporary Stack\n", k.plat);
}

//Fungsi untuk mengambil kembali kendaraan dari tumpukan sementara
Kendaraan popTemp() {
    return sementara.data[sementara.top--];
}

//Fungsi untuk menyimpan data kendaraan ke riwayat database dinamis
void tambahLinkedList(Kendaraan k) {
    Kendaraan *baru = (Kendaraan*) malloc(sizeof(Kendaraan));
    *baru = k;
    baru->next = NULL;

    if (head == NULL) {
        head = baru;
    } else {
        Kendaraan *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = baru;
    }
}

//Fungsi utama untuk menginput data kendaraan baru yang masuk parkir
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
