#include "parkir.h"

int main() {
    initStack();
    int pilihan;

    do {
        menu();
        scanf(" %d", &pilihan);

        switch (pilihan) {
            case 1: kendaraanMasuk(); break;
            case 2: kendaraanKeluar(); break;
            case 3: tampilData(); break;
            case 4: cariKendaraan(); break;
            case 5: urutDurasi(); break;
            case 0: printf("Program selesai.\n"); break;
            default: printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 0);
    
    return 0;
}
