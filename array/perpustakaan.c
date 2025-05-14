#ifndef perpus_h
#define perpus_h

#include "perpus.h"
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

rakbuku *setbuku(int jumlahtersedia, char *namabuku) {
  if (jumlahtersedia < 0 || namabuku == NULL) {
    printf("[ERROR] Parameter tidak valid\n");
    return NULL;
  }

  rakbuku *baru = (rakbuku *)malloc(sizeof(rakbuku));
  if (baru == NULL) {
    printf("[ERROR] Gagal alokasi memori\n");
    return NULL;
  }

  baru->jumlah = jumlahtersedia;
  strncpy(baru->nama, namabuku, sizeof(baru->nama) - 1);
  baru->nama[sizeof(baru->nama) - 1] = '\0';
  baru->awal = NULL;
  return baru;
}

pengunjung *pengunjungbaru(int tingkatan, char *identitasbaru) {
  if (identitasbaru == NULL) {
    printf("[ERROR] Nama tidak valid\n");
    return NULL;
  }

  pengunjung *orang = (pengunjung *)malloc(sizeof(pengunjung));
  if (orang == NULL) {
    printf("[ERROR] Gagal alokasi memori\n");
    return NULL;
  }

  orang->level = tingkatan;
  strncpy(orang->identitas, identitasbaru, sizeof(orang->identitas) - 1);
  orang->identitas[sizeof(orang->identitas) - 1] = '\0';
  orang->berikut = NULL;
  return orang;
}

void tambahkanurut(rakbuku **koleksi, char *identitasbaru, int tingkatan) {
  if (koleksi == NULL || *koleksi == NULL || identitasbaru == NULL) {
    printf("[ERROR] Parameter tidak valid\n");
    return;
  }

  pengunjung *orang = pengunjungbaru(tingkatan, identitasbaru);
  if (orang == NULL) {
    return;
  }

  pengunjung *antrian = (*koleksi)->awal;
  pengunjung *sebelum = NULL;

  if (antrian == NULL) {
    (*koleksi)->awal = orang;
    return;
  }

  if (tingkatan < antrian->level) {
    orang->berikut = antrian;
    (*koleksi)->awal = orang;
    return;
  }

  while (antrian != NULL && antrian->level <= tingkatan) {
    sebelum = antrian;
    antrian = antrian->berikut;
  }

  sebelum->berikut = orang;
  orang->berikut = antrian;
}

void batalkanpermintaan(rakbuku **koleksi, char *identitas) {
  pengunjung *hapus = (*koleksi)->awal;
  
  if (hapus == NULL) {
    printf("[ERROR] Antrian Kosong!\n");
    return;
  }
  
  if (strcmp(hapus->identitas, identitas) == 0) {
    (*koleksi)->awal = hapus->berikut;
    free(hapus);
    printf("\n[SUCCESS] Berhasil menghapus %s dari antrian", identitas);
    return;
  }
  
  pengunjung *sebelum = hapus;
  hapus = hapus->berikut;
  
  while (hapus != NULL) {
    if (strcmp(hapus->identitas, identitas) == 0) {
      sebelum->berikut = hapus->berikut;
      free(hapus);
      printf("\n[SUCCESS] Berhasil menghapus %s dari antrian", identitas);
      return;
    }
    sebelum = hapus;
    hapus = hapus->berikut;
  }
  
  printf("\n[ERROR] Peminjam '%s' tidak ditemukan dalam antrian!", identitas);
}

void hapuspertama(rakbuku **koleksi) {
  if (koleksi == NULL || *koleksi == NULL) {
    printf("[ERROR] Objek koleksi tidak valid\n");
    return;
  }

  if ((*koleksi)->awal == NULL) {
    printf("[INFO] Antrian Kosong!\n");
    return;
  }

  pengunjung *hapus = (*koleksi)->awal;
  (*koleksi)->awal = (*koleksi)->awal->berikut;
  free(hapus);
  printf("\n[SUCCESS] Antrian berhasil diproses");
}

void tambahpeminjam(peminjam **listpeminjam, char *identitasbaru, char *namabuku) {
  peminjam *baru = (peminjam *)malloc(sizeof(peminjam));
  peminjam *saat = *listpeminjam;
  if (baru == NULL) {
    printf("[ERROR] Gagal alokasi memori!\n");
    return;
  }
  strncpy(baru->identitas, identitasbaru, sizeof(baru->identitas) - 1);
  baru->identitas[sizeof(baru->identitas) - 1] = '\0';
  strncpy(baru->bacaan, namabuku, sizeof(baru->bacaan) - 1);
  baru->bacaan[sizeof(baru->bacaan) - 1] = '\0';
  baru->berikut = NULL;

  if (saat == NULL) {
    *listpeminjam = baru;
  } else {
    while (saat->berikut != NULL) {
      saat = saat->berikut;
    }
    saat->berikut = baru;
  }
}

void pinjamkan(rakbuku **koleksi, peminjam **listpeminjam) {
  if ((*koleksi)->awal == NULL) {
    printf("[ERROR] Antrian Kosong!\n");
    return;
  }

  if ((*koleksi)->jumlah <= 0) {
    printf("[ERROR] Stok buku habis!\n");
    return;
  }

  pengunjung *peminjam = (*koleksi)->awal;
  (*koleksi)->jumlah--;

  tambahpeminjam(listpeminjam, peminjam->identitas, (*koleksi)->nama);

  printf("\n[SUCCESS] Buku '%s' berhasil dipinjam oleh '%s'", (*koleksi)->nama, peminjam->identitas);
  hapuspertama(koleksi);
}

void kembalikan(peminjam **listpeminjam, rakbuku **kumpulanbuku, int posisi) {
  if (listpeminjam == NULL || *listpeminjam == NULL) {
    printf("[ERROR] Tidak ada peminjam!\n");
    return;
  }
  
  if (kumpulanbuku == NULL) {
    printf("[ERROR] Koleksi buku tidak valid!\n");
    return;
  }
  
  if (posisi <= 0) {
    printf("[ERROR] Posisi tidak valid!\n");
    return;
  }
  
  int i = 0;
  int urutan = 1;
  peminjam *pengembali = *listpeminjam;
  peminjam *sebelum = NULL;
  
  while (pengembali != NULL && urutan < posisi) {
    sebelum = pengembali;
    pengembali = pengembali->berikut;
    ++urutan;
  }

  if (pengembali == NULL) {
    printf("[ERROR] Posisi peminjam tidak ditemukan!\n");
    return;
  }
  
  i = 0;
  rakbuku *tujuan = NULL;
  int ketemu = 0;
  
  while (kumpulanbuku[i] != NULL) {
    if (strcmp(pengembali->bacaan, kumpulanbuku[i]->nama) == 0) {
      tujuan = kumpulanbuku[i];
      ketemu = 1;
      break;
    }
    ++i;
  }
  
  if (!ketemu || tujuan == NULL) {
    printf("[ERROR] Buku tidak ditemukan di koleksi!\n");
    return;
  }
  
  ++tujuan->jumlah;
  printf("\n[SUCCESS] Buku '%s' berhasil dikembalikan oleh '%s'", 
         pengembali->bacaan, pengembali->identitas);
  
  if (sebelum == NULL) {
    *listpeminjam = pengembali->berikut;
  } else {
    sebelum->berikut = pengembali->berikut;
  }
  
  free(pengembali);
}

void tampilkanantrian(rakbuku *koleksi) {
  if (koleksi == NULL) {
    printf("\n[ERROR] koleksi tidak ada");
    return;
  }

  if (koleksi->awal == NULL) {
    printf("\n[INFO] Antrian Kosong");
    return;
  }

  printf("\n[DAFTAR] Antrian untuk %s:", koleksi->nama);
  pengunjung *tampil = koleksi->awal;
  int urutan = 1;
  while (tampil != NULL) {
    printf("\n  %d. %s (Level: %d)", urutan++, tampil->identitas, tampil->level);
    tampil = tampil->berikut;
  }
}

void tampilkanpeminjam(peminjam *listpeminjam) {
  peminjam *saat = listpeminjam;
  if (listpeminjam != NULL) {
    int urutan = 1;
    while (saat != NULL) {
      printf("\n  Peminjam #%d", urutan++);
      printf("\n    Nama  : %s", saat->identitas);
      printf("\n    Bacaan: %s", saat->bacaan);
      saat = saat->berikut;
    }
  } else {
    printf("\n[INFO] Belum ada peminjam terdaftar");
  }
}
#endif
