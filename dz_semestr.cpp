#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// ---------------- КОНСТАНТЫ ----------------
const double g = 9.81;
const double S = 201.0;
const double m0 = 98000.0;
const double Cp = 0.6;

const double P_nom = 315000.0;
const double P_max = P_nom;

const double H0 = 500.0;
const double Hk = 8000.0;

const double V0 = 330.0 / 3.6;
const double Vk_max = 900.0 / 3.6;

const double Cx0 = 0.02;
const double K = 0.08; // увеличим сопротивление
const double Cy_a = 5.0;
const double Cy_max = 1.2;

const double phi_p = 0.0;

// ---------------- АТМОСФЕРА ----------------
double rho(double H) { return 1.225 * exp(-H / 8200.0); }

// ---------------- АЭРОДИНАМИКА ----------------
double Cy(double alpha) {
    double c = Cy_a * alpha;
    return (c > Cy_max) ? Cy_max : c;
}
double Cx(double alpha) {
    double cy = Cy(alpha);
    return Cx0 + K * cy * cy;
}

// ---------------- СОСТОЯНИЕ ----------------
struct State { double V, H, Theta, m, L; };

// ---------------- ПРОИЗВОДНЫЕ ----------------
State derivatives(const State& s, double alpha, double throttle) {
    State d;
    double r = rho(s.H);
    double q = 0.5 * r * s.V * s.V;
    double X = q * S * Cx(alpha);
    double Y = q * S * Cy(alpha);
    double P = throttle * P_max;

    d.V = (P * cos(alpha + phi_p) - X - s.m * g * sin(s.Theta)) / s.m;
    d.Theta = (P * sin(alpha + phi_p) + Y - s.m * g * cos(s.Theta)) / (s.m * s.V);
    d.H = s.V * sin(s.Theta);
    d.L = s.V * cos(s.Theta);
    d.m = -P * Cp / 3600.0;
    return d;
}

// ---------------- RK4 с ограничением dTheta ----------------
State rk4_limitedTheta(const State& s, double alpha, double throttle, double dt) {
    State k1 = derivatives(s, alpha, throttle);

    State s2;
    s2.V = s.V + 0.5*dt*k1.V; s2.H = s.H + 0.5*dt*k1.H;
    s2.Theta = s.Theta + 0.5*dt*k1.Theta; s2.m = s.m + 0.5*dt*k1.m;
    s2.L = s.L + 0.5*dt*k1.L;
    State k2 = derivatives(s2, alpha, throttle);

    State s3;
    s3.V = s.V + 0.5*dt*k2.V; s3.H = s.H + 0.5*dt*k2.H;
    s3.Theta = s.Theta + 0.5*dt*k2.Theta; s3.m = s.m + 0.5*dt*k2.m;
    s3.L = s.L + 0.5*dt*k2.L;
    State k3 = derivatives(s3, alpha, throttle);

    State s4;
    s4.V = s.V + dt*k3.V; s4.H = s.H + dt*k3.H;
    s4.Theta = s.Theta + dt*k3.Theta; s4.m = s.m + dt*k3.m;
    s4.L = s.L + dt*k3.L;
    State k4 = derivatives(s4, alpha, throttle);

    State sn;
    sn.V = s.V + dt/6*(k1.V + 2*k2.V + 2*k3.V + k4.V);
    sn.H = s.H + dt/6*(k1.H + 2*k2.H + 2*k3.H + k4.H);
    sn.Theta = s.Theta + dt/6*(k1.Theta + 2*k2.Theta + 2*k3.Theta + k4.Theta);
    sn.m = s.m + dt/6*(k1.m + 2*k2.m + 2*k3.m + k4.m);
    sn.L = s.L + dt/6*(k1.L + 2*k2.L + 2*k3.L + k4.L);

    // Ограничение угла θ
    if (sn.Theta > 15*M_PI/180.0) sn.Theta = 15*M_PI/180.0;
    if (sn.Theta < 0) sn.Theta = 0;

    double max_dTheta = 0.002;
    double dTheta = sn.Theta - s.Theta;
    if (dTheta > max_dTheta) sn.Theta = s.Theta + max_dTheta;
    if (dTheta < -max_dTheta) sn.Theta = s.Theta - max_dTheta;

    // Ограничение скорости
    if (sn.V > Vk_max) sn.V = Vk_max;

    return sn;
}

// ---------------- MAIN ----------------
int main() {
    ofstream traj_file("trajectory.dat");
    ofstream alpha_file("alpha.dat");

    traj_file << "# L_m H_m fuel_kg V_kmh\n";
    alpha_file << "# t_sec alpha_deg\n";

    State s; 
    s.V = V0; s.H = H0; s.Theta = 10*M_PI/180.0; s.m = m0; s.L = 0.0;

    double dt = 0.05;
    double t = 0.0;

    while (s.H < Hk && s.V < Vk_max) {
        double alpha = (2.0 + 4.0*(s.H-H0)/(Hk-H0)) * M_PI/180.0;
        if (alpha > 6.0*M_PI/180.0) alpha = 6.0*M_PI/180.0;

        double throttle = 0.7 + 0.3*(s.H-H0)/(Hk-H0);
        if (throttle > 1.0) throttle = 1.0;

        s = rk4_limitedTheta(s, alpha, throttle, dt);
        t += dt;

        traj_file << s.L << " " << s.H << " " << (m0 - s.m) << " " << s.V*3.6 << "\n";
        alpha_file << t << " " << alpha*180.0/M_PI << "\n";
    }

    traj_file.close();
    alpha_file.close();

    cout << "=== РЕЗУЛЬТАТ ===\n";
    cout << "Время: " << t/60 << " мин\n";
    cout << "Высота: " << s.H << " м\n";
    cout << "Скорость: " << s.V*3.6 << " км/ч\n";
    cout << "Расход топлива: " << m0 - s.m << " кг\n";

    return 0;
}
