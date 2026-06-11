#ifndef KARTU_H
#define KARTU_H



#include <iostream>
#include <string>
#include <stdexcept>
#include "utils.h"
using namespace std;

class KartuATM {
    string noKartu, pin, tipe;
    bool terblokir;
    int gagal;

public:
   
    KartuATM(const string& no, const string& p, const string& tp = "SILVER")
        : noKartu(no), pin(p), tipe(tp), terblokir(false), gagal(0) {}

   
    bool cekPIN(const string& input) {
        if (terblokir) throw runtime_error("Kartu diblokir! Hubungi CS.");
        if (input == pin) { gagal = 0; return true; }
        if (++gagal >= 3) {
            terblokir = true;
            throw runtime_error("3x PIN salah! Kartu terblokir.");
        }
        return false;
    }

    void gantiPIN(const string& lama, const string& baru) {
        if (lama != pin)      throw runtime_error("PIN lama salah!");
        if (baru.size() != 6) throw runtime_error("PIN harus 6 digit!");
        for (char c : baru)
            if (!isdigit(c)) throw runtime_error("PIN hanya boleh angka!");
        pin = baru;
    }

   
    friend ostream& operator<<(ostream& os, const KartuATM& k) {
        os << CYAN  << "+------------------------------------+\n";
        os << "  |  " << YELLOW << BOLD << "BANK ASLI GANTENG" << RESET << CYAN << "                 |\n";
        os << "  |  " << WHITE  << k.noKartu.substr(0, 4) << " **** **** "
           << k.noKartu.substr(12, 4) << "         " << CYAN << "|\n";
        os << "  |  " << WHITE  << "Jenis : " << k.tipe
           << "                      " << CYAN << "|\n";
        os << "  +------------------------------------+\n" << RESET;
        return os;
    }

   
    string getNoKartu() const { return noKartu; }
    string getTipe() const    { return tipe; }
    bool isBlocked() const    { return terblokir; }
};

#endif 
