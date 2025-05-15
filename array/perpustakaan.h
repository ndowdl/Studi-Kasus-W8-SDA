#ifndef PERPUSTAKAAN_H
#define PERPUSTAKAAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct antrean {
  int level;
  char identitas[50];
  struct antrean *berikut;
} pengunjung;

typedef struct koleksi {
  char nama[50];
  int jumlah;
  struct antrean *awal;
} rakbuku;

typedef struct daftar {
  char identitas[50];
  char bacaan[50];
  struct daftar *berikut;
} peminjam;

rakbuku *setbuku(int jumlahtersedia, char *namabuku);
pengunjung *pengunjungbaru(int tingkatan, char *identitasbaru);

void tampilkanantrian(rakbuku *koleksi);
void tampilkanpeminjam(peminjam *listpeminjam);

void hapuspertama(rakbuku **koleksi);
void tambahkanurut(rakbuku **koleksi, char *identitasbaru, int tingkatan);
void tambahpeminjam(peminjam **listpeminjam, char *identitasbaru, char *namabuku);
void pinjamkan(rakbuku **koleksi, peminjam **listpeminjam);
void kembalikan(peminjam **listpeminjam, rakbuku **kumpulanbuku, int posisi);
void batalkanpermintaan(rakbuku **koleksi, char *identitas);

#endif
