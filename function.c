#include "header.h"

// (Alokasi Variabel Global & Inisialisasi)
PriorityStack parkir;
TempStack sementara;
Kendaraan *head = NULL;

void initStack() {
    parkir.top = -1;
    sementara.top = -1;
}
