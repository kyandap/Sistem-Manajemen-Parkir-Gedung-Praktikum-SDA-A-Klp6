#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

/*Struct Kendaraan*/
typedef struct Kendaraan {
    char plat[20];
    char jenis[20];
    int prioritas;
    char waktuMasuk[10];
    char waktuKeluar[10];
    int status; // 1 = parkir, 0 = keluar
    struct Kendaraan *next;
} Kendaraan;

/*Priority Stack dan Temp Stack*/
typedef struct {
    Kendaraan data[MAX];
    int top;
} PriorityStack;

typedef struct {
    Kendaraan data[MAX];
    int top;
} TempStack;

extern PriorityStack parkir;
extern TempStack sementara;
extern Kendaraan *head;

/*Deklarasi Semua Fungsi Kelompok*/
void initStack();
int konversiMenit(char waktu[]);
int hitungDurasi(char masuk[], char keluar[]);
void tampilDurasi(int totalMenit);
void pushPriority(Kendaraan k, int mode);
Kendaraan popPriority();
void pushTemp(Kendaraan k);
Kendaraan popTemp();
void tambahLinkedList(Kendaraan k);
void kendaraanMasuk();
void kendaraanKeluar();
void tampilData();
void cariKendaraan();
void swap(Kendaraan *a, Kendaraan *b);
int partition(Kendaraan arr[], int low, int high);
void quickSort(Kendaraan arr[], int low, int high);
void urutDurasi();
void menu();

#endif
