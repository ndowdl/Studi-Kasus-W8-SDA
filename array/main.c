#include "perpus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// buat display
void tampilkanHeader() {
  printf("\n==========================================\n");
  printf("      SISTEM MANAJEMEN PERPUSTAKAAN      ");
  printf("\n==========================================\n");
}

void tampilkanGaris() {
  printf("\n------------------------------------------\n");
}

int main() {
  rakbuku *rak[2];
  peminjam *daftarpeminjam = NULL;
  rak[0] = NULL;
  rak[1] = NULL;

  rak[0] = setbuku(1, "buku1");
  if (rak[0] == NULL) {
    printf("Gagal membuat buku pertama\n");
    return 1;
  }

  rak[1] = setbuku(1, "buku2");
  if (rak[1] == NULL) {
    printf("Gagal membuat buku kedua\n");
    free(rak[0]);
    return 1;
  }

  printf("\n[INFO] KATALOG BUKU TERSEDIA:");
  printf("\n* Buku 1: %s (Stok: %d)", rak[0]->nama, rak[0]->jumlah);
  printf("\n* Buku 2: %s (Stok: %d)", rak[1]->nama, rak[1]->jumlah);

  tampilkanGaris();
  printf("\n[ANTRIAN] MENGELOLA BUKU: %s", rak[0]->nama);
  tambahkanurut(&rak[0], "Anggota1", 2);
  printf("\n[+] ditambahkan ke antrian (level 2)");
  tampilkanantrian(rak[0]);

  tambahkanurut(&rak[0], "Dosen1", 1);
  printf("\n[+] ditambahkan ke antrian (level 1)");
  tampilkanantrian(rak[0]);

  tambahkanurut(&rak[0], "Umum1", 3);
  printf("\n[+] ditambahkan ke antrian (level 3)");
  tampilkanantrian(rak[0]);

  tampilkanGaris();
  printf("\n[ANTRIAN] MENGELOLA BUKU: %s", rak[1]->nama);
  tambahkanurut(&rak[1], "Umum1", 3);
  printf("\n[+] ditambahkan ke antrian (level 3)");
  tampilkanantrian(rak[1]);
  
  printf("\n[OPERASI] MEMBATALKAN PERMINTAAN");
  batalkanpermintaan(&rak[1], "Umum1");
  tampilkanantrian(rak[1]);

  tampilkanGaris();
  printf("\n[PROSES] PEMINJAMAN BUKU:");
  printf("\n[INFO] Memproses peminjaman untuk prioritas tertinggi...");
  pinjamkan(&rak[0], &daftarpeminjam);
  tampilkanantrian(rak[0]);
  
  printf("\n[INFO] Memproses peminjaman berikutnya...");
  pinjamkan(&rak[0], &daftarpeminjam);
  
  tampilkanGaris();
  printf("\n[DAFTAR] PEMINJAM AKTIF:");
  tampilkanpeminjam(daftarpeminjam);

  tampilkanGaris();
  printf("\n[PROSES] PENGUJIAN PENGEMBALIAN BUKU:");
  kembalikan(&daftarpeminjam, rak, 1);
  
  printf("\n[DAFTAR] PEMINJAM AKTIF SETELAH PENGEMBALIAN:");
  tampilkanpeminjam(daftarpeminjam);

  tampilkanGaris();
  printf("\n[INFO] Membersihkan memori...");
  free(rak[0]);
  free(rak[1]);

  return 0;
}