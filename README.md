# Simulasi Rangkaian RC-Dioda dengan Metode Runge-Kutta Orde 4

## Informasi Pengguna
* **Nama Lengkap:** Arsinta Kirana Nisa
* **NPM:** 2306215980

## Deskripsi Program

Program ini adalah sebuah simulator rangkaian listrik yang ditulis dalam bahasa C. Secara spesifik, program ini bertujuan untuk menganalisis **respon transien** dari sebuah **rangkaian RC dengan dioda paralel** ketika diberikan masukan berupa tegangan step DC.

Tujuan utamanya adalah untuk memodelkan dan mengamati fenomena *voltage clamping*, di mana tegangan pada kapasitor dibatasi oleh tegangan maju dioda.

### Rangkaian yang Disimulasikan

Rangkaian terdiri dari sumber tegangan ($V_{in}$) yang terhubung seri dengan sebuah resistor (R). Bebannya adalah sebuah kapasitor (C) yang terhubung paralel dengan sebuah dioda (D).

```
      +----[ Resistor R ]----+---- Vc (Tegangan Kapasitor & Dioda)
      |                      |
Vin (+ o----)                +----[ Kapasitor C ]----+
      |                      |                      |
      (-)                    +-----[ Dioda D ]----->|
      |                      |                      |
      +----------------------+----------------------+---- Ground
```

### Metodologi

1.  **Pemodelan Matematis**: Perilaku rangkaian dimodelkan sebagai Persamaan Diferensial Biasa (PDB) orde satu. Persamaan ini diturunkan menggunakan **Hukum Arus Kirchhoff (KCL)** pada simpul $V_c$. Karakteristik non-linear dari dioda dimodelkan menggunakan **Persamaan Shockley**.
2.  **Solusi Numerik**: Karena PDB yang dihasilkan bersifat non-linear dan sulit diselesaikan secara analitis, program ini menggunakan metode numerik **Runge-Kutta Orde 4 (RK4)** untuk mencari solusi aproksimasinya. Metode RK4 dipilih karena memiliki akurasi yang tinggi dan stabil.

### Output Program

Program akan menghasilkan sebuah file bernama `diode_circuit_corrected_v2.csv`. File ini berisi data time-series dari simulasi dengan kolom sebagai berikut:
* `t (s)`: Waktu simulasi dalam detik.
* `Vc (V)`: Tegangan pada kapasitor dalam Volt.
* `I_total (A)`: Arus total yang mengalir dari sumber dalam Ampere.
* `I_diode (A)`: Arus yang mengalir melalui dioda dalam Ampere.

Data ini dapat langsung dianalisis dan divisualisasikan menggunakan perangkat lunak seperti Microsoft Excel, Python (dengan library Pandas dan Matplotlib), atau Gnuplot.

## Cara Menggunakan

### 1. Kompilasi
Untuk mengompilasi program, diperlukan C compiler seperti **GCC**. Buka terminal atau command prompt, navigasi ke direktori tempat file ini disimpan, dan jalankan perintah berikut:

```bash
gcc nama_file_sumber.c -o simulator -lm
```
* Ganti `nama_file_sumber.c` dengan nama file kode.
* `-o simulator` akan menghasilkan file eksekusi bernama `simulator`.
* `-lm` diperlukan untuk me-link library matematika karena program menggunakan fungsi `exp()` dari `math.h`.

### 2. Eksekusi
Setelah kompilasi berhasil, jalankan program dengan perintah:

```bash
./simulator
```

### 3. Lihat Hasil
Setelah program selesai berjalan, sebuah file bernama `diode_circuit_corrected_v2.csv` akan dibuat di direktori yang sama. 
