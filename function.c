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

/*Fungsi untuk menangani proses kendaraan yang akan keluar dari area parkir*/
void kendaraanKeluar() {
    char target[20];
    int ditemukan = 0;

/*Memeriksa Priority Stack kosong*/
    if (parkir.top == -1) {
        printf("Parkiran kosong.\n");
        return;
    }
    printf("\nMasukkan plat kendaraan keluar : ");
    scanf(" %19s", target);

while (parkir.top != -1) {
        Kendaraan k = popPriority();
        if (strcmp(k.plat, target) == 0) {
            /*Data kendaraan berhasil ditemukan*/
            ditemukan = 1;     
            printf("Waktu Keluar (HH:MM): ");
            scanf(" %9s", k.waktuKeluar);
            k.status = 0;

            Kendaraan *curr = head;
            while (curr != NULL) {
                if (strcmp(curr->plat, target) == 0 && curr->status == 1) {
                    curr->status = 0;
                    strcpy(curr->waktuKeluar, k.waktuKeluar);
                    break;
                }
            /*Memindahkan pointer ke node berikutnya, proses traversal dapat berlanjut*/
                curr = curr->next;  
            }
            printf("\nKendaraan %s berhasil keluar\n", k.plat);
            break;
        } else {
            pushTemp(k);
        }
    }

 while (sementara.top != -1) {
        pushPriority(popTemp(), 2);
    }

    if (!ditemukan) {
        printf("Kendaraan tidak ditemukan.\n");
    }
}

void tampilData() {
    Kendaraan *curr = head;
    if (curr == NULL) {
        printf("Data kosong.\n");
        return;
    }
    printf("\n=== DATA KENDARAAN ===\n");
    /*menelusuri seluruh node pada Linked List sampai node terakhir*/
    while (curr != NULL) {
        printf("--------------------------------\n");
        printf("Plat            : %s\n", curr->plat);
        printf("Jenis           : %s\n", curr->jenis);
        printf("Prioritas       : %d\n", curr->prioritas);
        printf("Waktu Masuk     : %s\n", curr->waktuMasuk);

        if (curr->status == 0) {
            int durasi = hitungDurasi(curr->waktuMasuk, curr->waktuKeluar);
            printf("Waktu Keluar    : %s\n", curr->waktuKeluar);
            printf("Durasi Parkir   : ");
            tampilDurasi(durasi);
            printf("\nStatus          : Keluar\n");
        } else {
            printf("Status          : Masih Parkir\n");
        }
        curr = curr->next;
    }
}

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
            printf("Plat            : %s\n", curr->plat);
            printf("Jenis           : %s\n", curr->jenis);
            printf("Prioritas       : %d\n", curr->prioritas);
            printf("Waktu Masuk     : %s\n", curr->waktuMasuk);

            if (curr->status == 0) {
                int durasi = hitungDurasi(curr->waktuMasuk, curr->waktuKeluar);
                printf("Waktu Keluar    : %s\n", curr->waktuKeluar);
                printf("Durasi Parkir   : ");
                tampilDurasi(durasi);
                printf("\n");
            } else {
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

void swap(Kendaraan *a, Kendaraan *b) {
    /*Data kendaraan pertama disimpan sementara agar tidak hilang saat proses pengurutan*/
    Kendaraan temp = *a;
    
    *a = *b;
    *b = temp;
}

int partition(Kendaraan arr[], int low, int high) {
    /*Pivot sebagai nilai pembanding dan diambil dari durasi kendaraan terakhir*/
    int pivot = hitungDurasi(arr[high].waktuMasuk, arr[high].waktuKeluar);
    
    int i = low - 1;
    for (int j = low; j < high; j++) {
        int durasi = hitungDurasi(arr[j].waktuMasuk, arr[j].waktuKeluar);
        if (durasi < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}
    
void quickSort(Kendaraan arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

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
        int durasi = hitungDurasi(arr[i].waktuMasuk, arr[i].waktuKeluar);
        printf("%s - ", arr[i].plat);
        tampilDurasi(durasi);
        printf("\n");
    }
}

void menu() {
    printf("\n====================================\n");
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
