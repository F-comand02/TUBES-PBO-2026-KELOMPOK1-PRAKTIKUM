#ifndef UTILS_H
#define UTILS_H


#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <limits>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;


#define RESET    "\033[0m"
#define BOLD     "\033[1m"
#define RED      "\033[31m"
#define GREEN    "\033[32m"
#define YELLOW   "\033[33m"
#define CYAN     "\033[36m"
#define WHITE    "\033[37m"
#define BG_BLUE  "\033[44m"
#define BG_GREEN "\033[42m"
#define BG_RED   "\033[41m"


inline void enableAnsi() {
#ifdef _WIN32
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(h, &mode);
    SetConsoleMode(h, mode | 0x0004);
    SetConsoleOutputCP(CP_UTF8);
#endif
}

inline void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

inline string getTime() {
    time_t now = time(0);
    tm* t = localtime(&now);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", t);
    return string(buf);
}

inline string rupiah(double n) {
    ostringstream oss;
    oss << fixed << setprecision(0) << n;
    string s = oss.str(), r;
    int c = 0;
    for (int i = (int)s.size() - 1; i >= 0; i--) {
        if (c > 0 && c % 3 == 0) r = "." + r;
        r = s[i] + r;
        c++;
    }
    return "Rp " + r;
}

inline void garis() {
    cout << CYAN << string(52, '=') << RESET << "\n";
}

inline void ok(const string& m) {
    cout << BG_GREEN << WHITE << BOLD << " OK  " << RESET << " " << m << "\n";
}

inline void err(const string& m) {
    cout << BG_RED << WHITE << BOLD << " ERR " << RESET << " " << m << "\n";
}

inline void enter() {
    cout << YELLOW << "\n  Tekan ENTER untuk lanjut..." << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}


inline void animasiKartu() {
    clearScreen();
    string kartu[] = {
        "  +------------------------------------+",
        "  |  BANK ASLI GANTENG                 |",
        "  |  **** **** **** ****               |",
        "  |  Masukkan Kartu ATM...             |",
        "  +------------------------------------+"
    };
    for (int frame = 0; frame < 4; frame++) {
        clearScreen();
        cout << "\n\n";
        for (int s = 0; s < 3 - frame; s++) cout << "\n";
        cout << CYAN << BOLD;
        for (auto& baris : kartu) cout << baris << "\n";
        cout << RESET;
#ifdef _WIN32
        Sleep(350);
#else
        usleep(350000);
#endif
    }
    cout << "\n" << GREEN << BOLD << "  Kartu terdeteksi!" << RESET << "\n";
#ifdef _WIN32
    Sleep(700);
#else
    usleep(700000);
#endif
}

#endif 
