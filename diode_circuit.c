#include <stdio.h>
#include <math.h>

#define R 1000.0       // Resistansi (ohm)
#define C 1e-6         // Kapasitansi (farad)
#define Is 1e-12       // Arus saturasi dioda (A)
#define n 1.0          // Koefisien emisi
#define Vt 0.025       // Tegangan termal (V)
#define V0 5.0         // Tegangan input (V)
#define t_start 0.0    // Waktu awal (s)
#define t_end 0.01     // Waktu akhir (s)
#define h 1e-7         // Langkah waktu 0.1 µs

// Fungsi tegangan input step
double Vin(double t) {
    return (t >= 0) ? V0 : 0.0;
}

// Fungsi arus dioda (Persamaan Shockley)
double I_diode(double Vc) {
    double arg = Vc / (n * Vt);
    if (arg > 50.0) arg = 50.0; // Batasi argumen untuk mencegah overflow pada exp()
    return Is * (exp(arg) - 1.0);
}

// Fungsi turunan dVc/dt = Ic/C
double f(double t, double Vc) {
    double Vin_t = Vin(t);
    double I_total = (Vin_t - Vc) / R;
    double I_d = I_diode(Vc);
    double Ic = I_total - I_d;

    
    return Ic / C;
}

// Langkah tunggal metode Runge-Kutta orde 4
double rk4_step(double t, double Vc, double dt) {
    double k1 = f(t, Vc);
    double k2 = f(t + dt/2.0, Vc + k1*dt/2.0);
    double k3 = f(t + dt/2.0, Vc + k2*dt/2.0);
    double k4 = f(t + dt, Vc + k3*dt);

    return Vc + (dt/6.0) * (k1 + 2.0*k2 + 2.0*k3 + k4);
}

int main() {
    double t = t_start;
    double Vc = 0.0; // Kondisi awal Vc = 0

    FILE *fp = fopen("diode_circuit_corrected_v2.csv", "w");
    if (fp == NULL) {
        printf("Gagal membuka file.\n");
        return 1;
    }
    fprintf(fp, "t (s),Vc (V),I_total (A),I_diode (A)\n");

    while (t <= t_end) {
        // Hitung arus pada state saat ini untuk dicatat
        double I_total = (Vin(t) - Vc) / R;
        double I_d = I_diode(Vc);

        // Catat state saat ini sebelum melangkah ke state berikutnya
        fprintf(fp, "%.6f,%.6f,%.12f,%.12f\n", t, Vc, I_total, I_d);

        // Hitung Vc untuk langkah waktu berikutnya
        Vc = rk4_step(t, Vc, h);
        
        if (Vc < 0.0) Vc = 0.0;
        if (Vc > V0) Vc = V0;

        t += h;
    }

    fclose(fp);
    printf("Simulasi selesai! Hasil disimpan di diode_circuit_corrected_v2.csv\n");
    return 0;
}