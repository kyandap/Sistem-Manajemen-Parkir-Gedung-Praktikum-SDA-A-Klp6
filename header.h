#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// STRUCT KENDARAAN
typedef struct Kendaraan {
    char plat[20];
    char jenis[20];
    int prioritas;
    char waktuMasuk[10];
    char waktuKeluar[10];
    int status; // 1 = parkir, 0 = keluar
    struct Kendaraan *next;
} Kendaraan;