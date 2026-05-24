SISTEM MANAJEMEN PARKIR GEDUNG FMIPA

Project Ujian Akhir Semester (UAS)  
Mata Kuliah: Praktikum Struktur Data dan Algoritma A  
Kelompok: 6  

Anggota Kelompok & Jobdesk

1. Fathul Hakim (Koordinator) – Membuat struct kendaraan, rancangan awal priority & temporary stack, deklarasi variabel global, dan fungsi inisialisasi stack.
2. Kyandaru Annisa Putri – Membuat fungsi utilitas waktu (konversi jam ke menit, hitung durasi, format durasi), serta fungsi push dan pop untuk priority stack.
3. Muhammad Reza Aryandi – Membuat fungsi operasi temporary stack (push & pop temp), fungsi tambah node ke linked list, dan logika alur saat kendaraan masuk.
4. As-Sajadah Khaira – Membuat fungsi alur saat kendaraan keluar (bongkar stack), fungsi menampilkan data, fungsi pencarian nomor plat (linear search), serta fungsi swap dan partition untuk quick sort.
5. Najla Putri Syahnuza – Membuat fungsi inti algoritma quick sort, fungsi sorting khusus durasi parkir, struktur tampilan menu, dan fungsi utama di main.c.


DESKRIPSI PROGRAM:

Sistem Manajemen Parkir Gedung FMIPA adalah program berbasis Console (CLI) yang kami buat untuk mengelola aktivitas kendaraan masuk dan keluar secara terstruktur. Di sini, kami menggabungkan manajemen fisik lapangan memakai alokasi memori statis (array) dengan basis data riwayat memakai alokasi memori dinamis (linked list).

Program ini kami rancang menggunakan pendekatan Modular Programming. Jadi, logika kodingannya sengaja dipecah ke beberapa file terpisah (header.h, function.c, dan main.c) supaya proses pengolahan data lebih efisien, kodenya rapi, dan tidak ada risiko kebocoran memori (memory leak).


STUDI KASUS:

Aktivitas kendaraan mahasiswa, dosen, dan staf di Gedung FMIPA sangat padat, apalagi pas jam sibuk perkuliahan pagi dan sore. Karena kapasitas parkir terbatas, sering muncul masalah di lapangan seperti susahnya memantau slot yang kosong, mobil terhalang oleh mobil lain saat mau keluar, dan tidak adanya catatan riwayat yang jelas karena semua masih dicatat manual pakai kertas.

Sistem ini kami buat untuk menyelesaikan masalah tersebut lewat simulasi tumpukan fisik berbasis prioritas (dosen atau staf dapat posisi paling atas/akses utama) serta pencatatan riwayat kendaraan secara digital biar mempermudah evaluasi operasional parkir gedung.


STRUKTUR DATA YANG DIGUNAKAN:

Ada tiga jenis struktur data utama yang kami pakai di sistem ini:

1. Priority Stack (Tumpukan Prioritas)
   - Konsep: Pengembangan dari stack biasa yang menggabungkan prinsip LIFO (Last In First Out) dengan mekanisme prioritas. Elemen yang prioritasnya lebih tinggi bakal ditaruh di posisi paling atas supaya bisa diproses duluan.
   - Implementasi: Digunakan untuk mengatur kendaraan yang sedang parkir di dalam gedung. Kendaraan dosen atau operasional kampus diberi nilai prioritas lebih tinggi biar menempati posisi tumpukan yang gampang diakses kalau mau keluar.

2. Temporary Stack (Tumpukan Sementara)
   - Konsep: Stack tambahan yang fungsinya buat tempat penampungan sementara waktu pas kita bongkar-pasang tumpukan utama, dan tetap mengikuti aturan LIFO.
   - Implementasi: Dipakai sebagai jalur evakuasi saat kendaraan yang di posisi bawah mau keluar. Jadi, kendaraan yang menghalangi di atasnya bakal dipindahin dulu ke Temporary Stack, baru dikembalikan lagi ke Priority Stack utama setelah kendaraan target berhasil keluar. Urutan tumpukan awal tidak akan berubah.

3. Singly Linked List
   - Konsep: Struktur data dinamis yang elemennya saling terhubung lewat pointer, sehingga penambahan data sifatnya itu fleksibel dan tidak dibatasi dengan ukuran tetap.
   - Implementasi: Berperan sebagai pusat database riwayat parkir gedung. Semua data kendaraan (nomor plat, jenis, prioritas, waktu masuk, dan status parkir) disimpan di sini. Datanya tetap aman tersimpan secara permanen walaupun kendaraannya udah keluar dari parkiran fisik.


ALGORITMA YANG DIGUNAKAN:

1. Quick Sort
   - Menggunakan metode Divide and Conquer dengan kompleksitas rata-rata O(n log n). Kami pakai algoritma ini untuk mengurutkan data kendaraan yang sudah keluar berdasarkan durasi parkirnya (dari yang tercepat sampai terlama) buat keperluan analisis data pengelola gedung.

2. Linear Search
   - Algoritma pencarian dengan kompleksitas waktu O(n). Kami pakai ini untuk mencari data spesifik kendaraan di dalam Linked List berdasarkan input nomor plat, lalu menampilkan info waktu masuk, status, dan durasi parkirnya.

3. Linked List Traversal
   - Proses menelusuri setiap node di dalam Linked List secara berurutan dari awal sampai akhir. Fungsinya untuk membaca semua data riwayat, menampilkan daftar kendaraan yang masih parkir, dan menghitung total kendaraan di dalam gedung.


ALUR KERJA SISTEM:

1. Tahap Input: Petugas memasukkan data kendaraan baru (nomor plat, jenis, prioritas, dan waktu masuk).
2. Tahap Penyimpanan: Data tersebut otomatis masuk ke PriorityStack sesuai tingkat prioritasnya, dan di waktu yang sama langsung dicatat ke database LinkedList dengan status aktif (nilai 1 / masih parkir).
3. Tahap Keluar: Kalau kendaraan yang mau keluar posisinya terhalang, kendaraan di atasnya bakal diungsikan dulu ke TempStack. Setelah kendaraan target keluar, sisa kendaraan dikembalikan lagi ke tumpukan utama. Status kendaraan tadi di LinkedList langsung berubah jadi keluar (nilai 0) dan waktu keluarnya dicatat.
4. Tahap Analisis: Sistem melakukan penelusuran (Traversal) dan pengurutan (Quick Sort) untuk menampilkan statistik durasi parkir beserta riwayat kendaraan secara rapi.


MODULAR FILE PROJECT:

- header.h : Tempat menyimpan definisi makro, deklarasi struct, variabel global extern, dan semua prototipe fungsi program.
- function.c : implementasi lengkap dari seluruh logika fungsi kelompok yang sudah dibagi per anggota.
- main.c : Berisi fungsi utama (main) untuk mengontrol jalannya menu utama menggunakan switch-case.
- README.md : Menjelaskan isi project secara lengkap dan terstruktur.